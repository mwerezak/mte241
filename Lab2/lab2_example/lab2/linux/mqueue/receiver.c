/**
 * @file:   os/lab/mqueue/receiver.c
 * @brief:  receive a message from POSIX queue. Typle Ctrl-C to quit 
 * @author: ece254/mte241 lab staff
 * @date:   2012/09/20
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <signal.h>
#include "common.h"
#include "point.h"

#define _XOPEN_SOURCE 600

bool g_continue = true;

void
sig_handler(int sig)
{
	g_continue = false;
}

int 
main(void)
{
	mqd_t qdes;
	char  qname[] = "/mailbox1";
	mode_t mode = S_IRUSR | S_IWUSR;
	struct mq_attr attr;

	attr.mq_maxmsg  = QUEUE_SIZE;
	attr.mq_msgsize = sizeof(struct point);
	attr.mq_flags   = 0;	// blocking queue 

	qdes  = mq_open(qname, O_RDONLY, mode, &attr);
	if (qdes == -1 ) {
		perror("mq_open()");
		exit(1);
	}

	signal(SIGINT, sig_handler);	// install Ctl-C signal handler

	srand(time(0));

	while (g_continue) {
		struct point pt;
		struct timespec ts = {time(0) + 5, 0};

		// only block for a limited time if queue is empty
		if (mq_timedreceive(qdes, (char *) &pt, \
		    sizeof(struct point), 0, &ts) == -1) {
			perror("mq_timedreceive() failed");
			printf("Type Ctrl-C and wait for 5 seconds to terminate.\n");
		} else {
			printf("Received a random point at (%d, %d)\n", \
		                get_x_coord(pt), get_y_coord(pt));
		}
	};


	if (mq_close(qdes) == -1) {
		perror("mq_close() failed");
		exit(2);
	}

	return 0;
}

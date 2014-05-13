/**
 * @file:   os/lab1/mqueue/sender.c
 * @brief:  send random points to a POSIX queue. Type 'q' to terminate. 
 * @author: ece254/mte241 lab staff 
 * @date:   2012/09/20
 * NOTES: 
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>
#include "common.h"
#include "point.h"

int 
main(void)
{
	mqd_t qdes;
	char  quit = '\0';
	char  qname[] = "/mailbox1";	//queue name must start with '/'. man mq_overview
	mode_t mode = S_IRUSR | S_IWUSR;
	struct mq_attr attr;

	attr.mq_maxmsg  = QUEUE_SIZE;
	attr.mq_msgsize = sizeof(struct point);
	attr.mq_flags   = 0;		// blocking queue 

	qdes  = mq_open(qname, O_RDWR | O_CREAT, mode, &attr);
	if (qdes == -1 ) {
		perror("mq_open() failed");
		exit(1);
	}

	srand(time(0));

	printf("Press a key to send a random point.\n");
	getchar();
	do {
		struct point pt;

		set_position(rand() % 80, rand() % 24, &pt); 
		if (mq_send(qdes, (char *)&pt, sizeof(struct point), 0) == -1) {
			perror("mq_send() failed");
		}
		printf("Sending a random point at (%d, %d)...\n", \
		       get_x_coord(pt), get_y_coord(pt));
		quit = getchar();
	} while (quit != 'q');


	if (mq_close(qdes) == -1) {
		perror("mq_close() failed");
		exit(2);
	}

	if (mq_unlink(qname) != 0) {
		perror("mq_unlink() failed");
		exit(3);
	}

	return 0;
}

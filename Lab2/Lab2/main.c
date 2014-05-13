#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "globals.h"
#include "producer.h"
#include "consumer.h"


int main (void) { //TODO
    printf("main: parse arguments and set globals");
    int cons_count, prod_count;
    mqd_t data_queue;
    char  data_queue_name[] = "/mailbox1_mwerezak";
    mode_t mode = S_IRUSR | S_IWUSR;
    struct mq_attr attr;
    
    //Timing
    
    //parse arguments and set globals
    printf("main: parse arguments and set globals");
    
    
    //TODO
    cons_count = 1;
    prod_count = 3;
    _data_queue_size = 6;
    _integer_count = 10;    
    
    //create the data queue
    printf("main: create the data queue");
    attr.mq_maxmsg  = _data_queue_size;
    attr.mq_msgsize = sizeof(int);
    attr.mq_flags   = 0;    // blocking queue 

    data_queue = mq_open(data_queue_name, O_RDWR | O_CREAT, mode, &attr);
    if (data_queue == -1 ) {
        perror("mq_open()");
        exit(1);
    }
    
    //create all the consumers
    printf("main: create all the consumers");
    fork_consumers(cons_count, data_queue_name);
    
    //create all the producers
    printf("main: create all the producers");
    fork_producers(prod_count, data_queue_name);
    
    //clean up.
    printf("main: clean up");
    if (mq_close(data_queue) == -1) {
        perror("mq_close() failed");
        exit(2);
    }

    if (mq_unlink(data_queue_name) != 0) {
        perror("mq_unlink() failed");
        exit(3);
    }
    
    return 0;
}

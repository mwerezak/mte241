#include "consumer.h"


void fork_consumers (int cons_count, char data_queue_name[]) {
    int cons_id;
    pid_t pid;
    
    //fork all of the producers
    for (cons_id = 0; cons_id < cons_count; cons_id++) {
        pid = fork();
        
        if (pid == 0) {
            start_consumer(cons_id, data_queue_name);
            _exit(0);
        }
    }
}


void start_consumer (int cons_id, char data_queue_name[])
{
    mqd_t data_queue;
    int data;
    double sroot;
    
    //open connection to queue
    printf("consumer %d: open connection to queue", cons_id);
    
    data_queue = mq_open(data_queue_name, O_RDONLY);
    if (data_queue == -1) {
        perror("mq_open() failed");
        exit(1);
    }
    
    do
    {
        //get data from queue
        printf("consumer %d: get data from queue", cons_id);
        
        if (mq_receive(data_queue, (char *) &data, sizeof(int), NULL) == -1) {
            perror("mq_receive() failed");
        } else {
            //check whether square root is integer
            sroot = sqrt(data);
            if ( sroot - floor(sroot) == 0.0 )
                printf("consumer %d: %d => %d", cons_id, data, (int) sroot);
        }
    
    } while (data != _integer_count - 1);
    
}

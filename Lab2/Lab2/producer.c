#include "producer.h"

//creates all producers and then blocks until they are finished.
void fork_producers(int prod_count, char data_queue_name[]) {
    int prod_id;
    pid_t pid_arr[prod_count];
    
    //fork all of the producers
    for (prod_id = 0; prod_id < prod_count; prod_id++) {
        pid_arr[prod_id] = fork();
        
        if (pid_arr[prod_id] == 0) {
            start_producer(prod_id, prod_count, data_queue_name);
            _exit(0);
        }
    }
    
    //wait until all producers are done
    for (prod_id = 0; prod_id < prod_count; prod_id++)
        waitpid(pid_arr[prod_id], NULL, 0);
}

void start_producer(
    int prod_id, 
    int prod_count, 
    char data_queue_name[]
) {
    mqd_t data_queue;
    int i;
    
    //open the message queue buffer
    printf("producer %d: open the message queue buffer", prod_id);
    
    data_queue = mq_open(data_queue_name, O_WRONLY);
    if (data_queue == -1) {
        perror("mq_open() failed");
        exit(1);
    }
    
    //write integers to it.
    i = prod_id;
    
    while (i < _integer_count) {
        //send integer
        printf("producer %d: send integer %d", prod_id, i);
        
        if (mq_send(data_queue, (char *) &i, sizeof(int), i) == -1) {
            perror("mq_send() failed");
        }
        
        //get the next integer
        i += prod_count;
    }
    
    //close our connection to the queue
    printf("producer %d: close our connection to the queue", prod_id);
    
    if (mq_close(data_queue) == -1) {
        perror("mq_close() failed");
        exit(2);
    }
}

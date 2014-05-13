#ifndef PRODUCER_H
#define PRODUCER_H

#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/wait.h>
#include "globals.h"


void start_producer(int prod_id, int prod_count, char data_queue_name[]);
void fork_producers(int prod_count, char data_queue_name[]);


#endif

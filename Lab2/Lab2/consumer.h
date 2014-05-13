#ifndef CONSUMER_H
#define CONSUMER_H

#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <math.h>
#include "globals.h"

void fork_consumers (int cons_count, char data_queue_name[]);
void start_consumer (int cons_id, char data_queue_name[]);

#endif

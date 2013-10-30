/**
* @file: main.c
* @brief: Post-lab deliverable for MTE 241 Lab0B
*/
#include <LPC17xx.h>
#include <stdio.h>
#include "../../RTX_CM3/INC/RTL.h"
#include "uart_polling.h"

//#define RAM
#define SIM

#ifdef RAM
#define TIMING_MULT 100
#endif

#ifdef SIM
#define TIMING_MULT 1
#endif


__task void task1()
{
	unsigned int i = 0;
	for(;; i++)
	{
		printf("Task1: %d\n", i);
		os_dly_wait(1*TIMING_MULT);
	}
}

__task void task2()
{
	while(1)
	{
		printf("Task2: HelloWorld!\n");
		os_dly_wait(3*TIMING_MULT);
	}
}

__task void task3() {
	printf("Task 3 started.\n");
	printf("Task 3: There are %d tasks right now.\n", os_tsk_count_get());
	
	while(1) os_dly_wait(1*TIMING_MULT);
}

__task void task4() {
	printf("Task 4 started.\n");
	
	while(1) os_dly_wait(1*TIMING_MULT);
}

__task void task5() {
	printf("Task 5 started.\n");
	printf("Task 5: There are %d tasks right now.\n", os_tsk_count_get());
	
	while(1) os_dly_wait(1*TIMING_MULT);
}


int print_task_info() {
		int task_id = 6;
		RL_TASK_INFO task_info;
		int foo;
	
		if (os_tsk_get(task_id, &task_info) == OS_R_OK) {			
			printf("\nTask %d State = %d\n", task_id, task_info.state);
			printf("Task %d Stack Usage = %d\n", task_id, task_info.stack_usage);
		} else {
			printf("\nTask %d is no more.\n\n", task_id);
		}
		
		
		//os_dly_wait(1*TIMING_MULT);
		
		//foo = print_task_info() + 1;
		
		
		return foo;

}

__task void printInfo() {
	
	/*
	int task_id;
	RL_TASK_INFO task_info;
	
	
	while(1) {
		for (task_id = 1; task_id <= os_maxtaskrun; task_id++) {
			if (rt_tsk_get(task_id, &task_info) == OS_R_OK) {			
				printf("\nTask %d State = %d\n", task_id, task_info.state);
				printf("Task %d Priority = %d\n", task_id, task_info.prio);
				printf("Task %d Task ID = %d\n", task_id, task_info.task_id);
				printf("Task %d Stack Usage = %d\n", task_id, task_info.stack_usage);
				printf("Task %d Entry Point = %d\n\n", task_id, task_info.ptask);
			} else {
				printf("\nTask %d is no more.\n\n", task_id);
			}
			
		}
		
		os_dly_wait(6*TIMING_MULT);
	}*/
	
	print_task_info();
	

}

__task void init(void)
{
	
	os_tsk_create(task1, 1); // task1 at priority 1
	os_dly_wait(1*TIMING_MULT);
	os_tsk_create(task2, 1); // task2 at priority 1
	os_dly_wait(1*TIMING_MULT);
	os_tsk_create(task3, 1); // task3 at priority 1
	os_dly_wait(1*TIMING_MULT);
	os_tsk_create(task4, 1); // task4 at priority 1
	//os_dly_wait(1*TIMING_MULT);
	//os_tsk_create(task5, 1); // task5 at priority 1
	
	os_dly_wait(1*TIMING_MULT);
	os_tsk_create(printInfo, 2); // printInfo at priority 1
	
	
	printf("init: There are %d tasks right now.\n", os_tsk_count_get());
	
	os_tsk_delete_self(); // must delete itself before exiting
}

int main ()
{
	printf("System Init");
	
	SystemInit();
	uart0_init();
	os_sys_init(init);
	
	
	
}

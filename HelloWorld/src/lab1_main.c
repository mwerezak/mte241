/**
 * @brief: ECE254 lab1 starter file that calls os_tsk_get()
 * @file: lab1_main.c
 * @author: Yiqing Huang
 * @date: 2013/05/28
 */

#include <LPC17xx.h>
#include "uart_polling.h"
#include "../../RTX_CM3/INC/RTL.h" /* modified RTL.h file. NOT the default one! */
#include <stdio.h>
#include <string.h>

//#define RAM
#define SIM

#ifdef RAM
#define TIMING_MULT 100
#endif

#ifdef SIM
#define TIMING_MULT 1
#endif

struct func_info {
  void (*p)();      /* function pointer */
  char name[16];    /* name of the function */
};

extern void os_idle_demon(void);
//__task void task1(void);
__task void task2(void);
__task void task3(void);
__task void task4(void);
__task void task5(void);
__task void init (void);
 
//create a memory pool

const U32 mem_pool_size = sizeof(U64);
const U32 mem_pool_cnt = 10;

_declare_box8 (mem_pool, mem_pool_size, mem_pool_cnt);

char *state2str(unsigned char state, char *str);
char *fp2name(void (*p)(), char *str);

OS_MUT g_mut_uart;
OS_TID g_tid = 255;

int  g_counter = 0;  // a global counter
char g_str[16];
char g_tsk_name[16];

struct func_info g_task_map[] = \
{
  /* os_idle_demon function ptr to be initialized in main */
  {NULL,  "os_idle_demon"}, \
  {task2, "status"},   \
  {task3, "ehp"},   \
  {task4, "elp"},   \
	{task5, "lhp"},   \
  {init,  "init" }
};


//early high priority task
__task void task3(void)
{
	int i;
	const int buf_size = 8;
	void* buffer[buf_size];
	
	printf("task3 allocating memory:\n");
	for (i = 0; i < buf_size; i++) {
		buffer[i] = os_mem_alloc(&mem_pool);
		printf("task3 allocated block %d\n", i);
	}
	
	printf("task3 waiting...\n");
	os_dly_wait(10*TIMING_MULT);
	
	printf("task3 freeing memory:\n");
	for (i = 0; i < buf_size; i++) {
		printf("task3 freeing block %d\n", i);
		os_mem_free(&mem_pool, buffer[i]);
	}
	
	printf("task3 exit\n");
	os_tsk_delete_self();
}

//early low priority task
__task void task4(void)
{
	int i;
	const int buf_size = 8;
	void* buffer[buf_size];
	
	printf("task4 allocating memory:\n");
	for (i = 0; i < buf_size; i++) {
		buffer[i] = os_mem_alloc(&mem_pool);
		printf("task4 allocated block %d\n", i);
	}
	
	printf("task4 waiting...\n");
	os_dly_wait(10*TIMING_MULT);
	
	printf("task4 freeing memory:\n");
	for (i = 0; i < buf_size; i++) {
		printf("task4 freeing block %d\n", i);
		os_mem_free(&mem_pool, buffer[i]);
	}
	
	printf("task4 exit\n");
	os_tsk_delete_self();
}

//late high priority task
__task void task5(void)
{
	int i;
	const int buf_size = 8;
	void* buffer[buf_size];
	
	printf("task5 allocating memory:\n");
	for (i = 0; i < buf_size; i++) {
		buffer[i] = os_mem_alloc(&mem_pool);
		printf("task5 allocated block %d\n", i);
	}
	
	printf("task5 waiting...\n");
	os_dly_wait(10*TIMING_MULT);
	
	printf("task5 freeing memory:\n");
	for (i = 0; i < buf_size; i++) {
		printf("task5 freeing block %d\n", i);
		os_mem_free(&mem_pool, buffer[i]);
	}
	
	printf("task5 exit\n");
	os_tsk_delete_self();
}



/*--------------------------- task2 -----------------------------------*/
/* checking states of all tasks in the system                          */
/*---------------------------------------------------------------------*/
__task void task2(void)
{
  U8 i=1;
  RL_TASK_INFO task_info;
	
  while (1) {
	
		os_mut_wait(g_mut_uart, 0xFFFF);
		printf("TID\tNAME\t\tPRIO\t\tSTATE   \t%%STACK\t\tENTRY\n");
		os_mut_release(g_mut_uart);
			
		for(i = 0; i < os_maxtaskrun; i++) { // this is a lazy way of doing loop.
			if (os_tsk_get(i+1, &task_info) == OS_R_OK) {
				os_mut_wait(g_mut_uart, 0xFFFF);  
			  printf("%d\t%s\t\t%d\t%s\t%d%%\t\t0x%X\n", \
						 task_info.task_id, \
						 fp2name(task_info.ptask, g_tsk_name), \
						 task_info.prio, \
						 state2str(task_info.state, g_str),  \
						 task_info.stack_usage,
						 task_info.ptask);
			  os_mut_release(g_mut_uart);
			} 
		}
			
		if (os_tsk_get(0xFF, &task_info) == OS_R_OK) {
			os_mut_wait(g_mut_uart, 0xFFFF);  
			printf("%d\t%s\t\t%d\t%s\t%d%%\t\t0x%X\n", \
						 task_info.task_id, \
						 fp2name(task_info.ptask, g_tsk_name), \
						 task_info.prio, \
						 state2str(task_info.state, g_str),  \
						 task_info.stack_usage,
						 task_info.ptask);
			os_mut_release(g_mut_uart);
		} 
    
		os_mut_wait(g_mut_uart, 0xFFFF);
		printf("\n");
		os_mut_release(g_mut_uart);
		
		os_dly_wait(5*TIMING_MULT);
	}
}

/*--------------------------- init ------------------------------------*/
/* initialize system resources and create other tasks                  */
/*---------------------------------------------------------------------*/
__task void init(void)
{
	int i;
	const int buf_size = 8;
	void* buffer[buf_size];
	
	_init_box8(&mem_pool, mem_pool_size*mem_pool_cnt, mem_pool_size);
	
  os_mut_init(&g_mut_uart);
	
	//grab all the memory
	printf("init allocating memory:\n");
	for (i = 0; i < buf_size; i++) {
		buffer[i] = os_mem_alloc(&mem_pool);
		printf("init allocated block %d\n", i);
	}	
  
  os_mut_wait(g_mut_uart, 0xFFFF);
  printf("init: TID = %d\n", os_tsk_self());
  os_mut_release(g_mut_uart);
    
  g_tid = os_tsk_create(task2, 100);  /* task 2 at priority 1 */
  os_mut_wait(g_mut_uart, 0xFFFF);
  printf("init: created task2 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);
	
  g_tid = os_tsk_create(task3, 10);  /* task 3 at priority 10 */
  os_mut_wait(g_mut_uart, 0xFFFF);
  printf("init: created task3 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);
	
  g_tid = os_tsk_create(task4, 2);  /* task 4 at priority 1 */
  os_mut_wait(g_mut_uart, 0xFFFF);
  printf("init: created task4 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);
	
  os_dly_wait(5*TIMING_MULT);
	
  g_tid = os_tsk_create(task5, 10);  /* task 5 at priority 10 */
  os_mut_wait(g_mut_uart, 0xFFFF);
  printf("init: created task5 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);
	
	printf("init waiting...\n");
	os_dly_wait(20*TIMING_MULT);
	
	printf("init freeing memory:\n");
	for (i = 0; i < buf_size; i++) {
		printf("init freeing block %d\n", i);
		os_mem_free(&mem_pool, buffer[i]);
	}
	
	printf("init exiting...\n");
  os_tsk_delete_self();     /* task MUST delete itself before exiting */
}

/**
 * @brief: convert state numerical value to string represenation      
 * @param: state numerical value (macro) of the task state
 * @param: str   buffer to save the string representation, 
 *               buffer to be allocated by the caller
 * @return:the string starting address
 */
char *state2str(unsigned char state, char *str)
{
  switch (state) {
	case INACTIVE:
    strcpy(str, "INACTIVE");
    break;
  case READY:
    strcpy(str, "READY   ");
    break;
  case RUNNING:
    strcpy(str, "RUNNING ");
    break;
  case WAIT_DLY:
    strcpy(str, "WAIT_DLY");
    break;
  case WAIT_ITV:
    strcpy(str, "WAIT_ITV");
    break;
  case WAIT_OR:
    strcpy(str, "WAIT_OR");
    break;
  case WAIT_AND:
    strcpy(str, "WAIT_AND");
    break;
  case WAIT_SEM:
    strcpy(str, "WAIT_SEM");
    break;
  case WAIT_MBX:
    strcpy(str, "WAIT_MBX");
    break;
  case WAIT_MUT:
    strcpy(str, "WAIT_MUT");
    break;
  case WAIT_MEM:
    strcpy(str, "WAIT_MEM");
    break;
  default:
    strcpy(str, "UNKNOWN");    
  }
  return str;
}

/** 
 * @brief: get function name by function pointer
 * @param: p the entry point of a function (i.e. function pointer)
 * @param: str the buffer to return the function name
 * @return: the function name string starting address
 */
char *fp2name(void (*p)(), char *str)
{
  int i;
  unsigned char is_found = 0;
  
  for ( i = 0; i < 7; i++) {
    if (g_task_map[i].p == p) {
      str = strcpy(str, g_task_map[i].name);  
      is_found = 1;
      break;
    }
  }
  if (is_found == 0) {
      strcpy(str, "ghost");
  }
  return str;
}

int main(void)
{
	SystemInit();         /* initialize the LPC17xx MCU */
  uart0_init();         /* initilize the first UART */
  
  
  /* fill the fname map with os_idle_demon entry point */
  g_task_map[0].p = os_idle_demon;
  
  printf("Calling os_sys_init()...\n");
	os_sys_init_prio(init,100+1);	  /* initilize the OS and start the first task */
}

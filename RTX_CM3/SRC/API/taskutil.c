/**
* @file: taskutil.c
* @brief: API functions for getting information about and manipulating tasks.
*/

#include "..\CM\rt_TypeDef.h"
#include "..\CM\RTX_Config.h"
#include "..\CM\rt_Task.h"

// Returns the number of active tasks in the system
int rt_tsk_count_get () {
		int i, active_count = 0;
	
		//look through os_active_TCB and check the status
		for (i = 0; i < os_maxtaskrun; i++) {		
				//check if the task exists (ptr is not null), if it does, check the state.
				if (os_active_TCB[i] != NULL && ((P_TCB)os_active_TCB[i])->state != INACTIVE)
						active_count ++;
		}
	
		return active_count;
}

/*
U8 rt_get_running_task_id (void) {
	P_TCB p_task;
	
	//look through os_active_TCB and check the status
	for (i = 0; i < os_maxtaskrun; i++) {		
			p_task = os_active_TCB[i];
			
			//return the FIRST running task found
			if (p_task != NULL && p_task->state == RUNNING)
					return p_task->task_id;
	}
}
*/

U32 rt_stack_size_get (P_TCB p_tcb) {
  U32 size = p_tcb->priv_stack >> 2;
  
  if (size == 0) {
    size = (U16)os_stackinfo >> 2;
  }
  
  return size;
}

// Returns the percentage usage of a task's stack
U8 rt_stack_usage_get (P_TCB p_tcb) {
  U32 *stack_start = &p_tcb->stack[0], 
      *stack_end = &p_tcb->stack[rt_stack_size_get(p_tcb)];
  U32 total_size, used_size;
	volatile U32 start_addr, end_addr, current_addr;
	
	start_addr = (U32) stack_start;
	end_addr = (U32) stack_end;
	total_size = end_addr - start_addr;
	current_addr = p_tcb->tsk_stack;
      
  //used_size = ((U32) stack_end) - ((U32) (p_tcb->tsk_stack));
  //total_size = ((U32) stack_end) - ((U32) stack_start);
	
	used_size = end_addr - current_addr;
	
  
  return (U8) (100*used_size)/total_size;
}

OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *buffer) {
  P_TCB p_tcb;
  
  if (task_id < 1 || task_id > os_maxtaskrun)
    return OS_R_NOK;
  
  p_tcb = os_active_TCB[task_id-1]; //get TCB for the task
  if (buffer == NULL || p_tcb == NULL)
    return OS_R_NOK;
  
  //assign task info values
  buffer->state = p_tcb->state;
  buffer->prio = p_tcb->prio;
  buffer->task_id = p_tcb->task_id;
  buffer->stack_usage = rt_stack_usage_get(p_tcb);
  buffer->ptask = p_tcb->ptask;
  
  return OS_R_OK;
}


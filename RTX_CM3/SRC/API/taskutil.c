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
		P_TCB task_ptr;
	
		//look through os_active_TCB and check the status
		for (i = 0; i < os_maxtaskrun; i++) {
				task_ptr = os_active_TCB[i];	//get a pointer
			
				//check if the task exists (ptr is not null), if it does, check the state.
				if (os_active_TCB[i] != NULL && ((P_TCB)os_active_TCB[i])->state != INACTIVE)
						active_count ++;
		}
	
		return active_count;
}

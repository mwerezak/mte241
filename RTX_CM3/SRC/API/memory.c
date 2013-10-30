#include "..\CM\rt_TypeDef.h"
#include "..\CM\RTX_Config.h"
#include "..\CM\rt_Task.h"
#include "..\CM\rt_MemBox.h"
#include "..\CM\rt_List.h"

void* rt_mem_alloc (void *box_mem) {
	void* p_mem;
	
	p_mem = rt_alloc_box(box_mem);	//attempt to allocate mem
	
	if (p_mem == NULL) {	//block task until mem is available
		rt_put_prio(&os_wait_list, os_tsk);	//add the current task to waiting list
		rt_block(0xffff, WAIT_MEM);		//block the running task
	} else {
		return p_mem;	//return the pointer
	}
}

OS_RESULT rt_mem_free (void *box_mem, void *box) {
	P_TCB p_task;
	
	//free the memory
	if (rt_free_box (box_mem, box))
		return OS_R_NOK;
	
	//see if there are any tasks waiting for mem
	if (os_wait_list->p_lnk != NULL) {
		p_task = rt_get_first(os_wait_list);
		p_task->retval = box;
		p_task->state = READY;
		
		rt_dispatch(p_task);
	}
	
	return OS_R_OK;
}

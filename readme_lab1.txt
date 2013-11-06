***********************************************************************
MTE 241 Lab1

Lab1 Readme

Michael Daniel Werezak 20303777
Mathew Mendelsohn 20416425
***********************************************************************

The descriptions of each task is located in lab1_test_spec.txt
The prelab is located in PreLab.txt

The source code for our test cases for parts A and B is located in .\HelloWorld\src and
the program entry point is in lab1_main.c

The source code for our kernel is located in .\RTX_CM3\SRC\API and .\RTX_CM3\SRC\CM.
The header for our OS functions are located at the end of .\RTX_CM3\INC\RTL.h

To build our project, open the multi-project workspace file helloworld_rtxlib.uvmpw in
the Kiel IDE and set HelloWorld as the active project.

The RL_TASK_INFO struct is defined in rt_TypeDef.h and in RTL.h.
The function os_tsk_get() is defined in .\RTX_CM3\SRC\API\taskutil.c
The functions os_mem_alloc() and os_mem_free() are defined in .\RTX_CM3\SRC\API\memory.c
The priority queue for tasks waiting for memory is located in rt_List.c This queue is
initialized by rt_sys_init() located in rt_Task.c



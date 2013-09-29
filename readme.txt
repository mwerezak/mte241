***********************************************************************
MTE 241 Lab0B - Introduction to ARM RL-RTX Kernel and Application Programming

Lab0B Readme

Michael Daniel Werezak 20303777
Mathew Mendelsohn 20416425

***********************************************************************

The answers to the lab questions can be found in Lab0B_Kiel.txt

os_tsk_count_get() is a wrapper around the kernel function rt_tsk_count_get(). This is declared at line 655 of .\RTX_CM3\INC\RTL.h. The implementation of rt_tsk_count_get() can be found in .\RTX_CM3\SRC\API\taskutil.c

The application code can be found in .\HelloWorld\src\main.c
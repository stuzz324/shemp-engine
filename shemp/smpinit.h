#ifndef SMPINIT_H
#define SMPINIT_H
#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
//PUBLIC MACROS & PREDEFS
#define SMP_EIGLFW 0x01 //Failed to instantiate GLFW
#define SMP_ECGWIN 0x02 //Failed to create GLFWwindow
#define SMP_EIGLAD 0x04 //Failed to instantiate GLAD

//GLOBAL EXTERN VARIABLES
extern GLFWwindow* smp_window;
extern int smp_errno;

//PUBLIC FUNCTIONS
//init function
int smp_init();

//error printing
void smp_error(const char* msg);
void smp_error_test();

int smp_verify();

#endif

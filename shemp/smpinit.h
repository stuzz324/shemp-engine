#ifndef SMPINIT_H
#define SMPINIT_H
#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <smptypes.h>
//PUBLIC MACROS & PREDEFS

//GLOBAL EXTERN VARIABLES
extern GLFWwindow* smp_window;

//PUBLIC FUNCTIONS
//init function
int smp_init();

int smp_verify();

#endif

#ifndef SMPTYPES_H
#define SMPTYPES_H

//smpinit
#define SMP_EIGLFW 0x00000001 //Failed to instantiate GLFW
#define SMP_ECGWIN 0x00000002 //Failed to create GLFWwindow
#define SMP_EIGLAD 0x00000004 //Failed to instantiate GLAD

//smpshdr
#define SMP_ESHDRD 0x00000100 //Failed to read shader
#define SMP_ESHDWR 0x00000200 //Failed to write shader

extern int smpi_errno;
extern int smps_errno;

#endif

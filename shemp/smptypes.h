#ifndef SMPTYPES_H
#define SMPTYPES_H

//ERROR BIT-FLAGS
//smpinit error bit codes
#define SMP_EIGLFW 0x00000001 //Failed to instantiate GLFW
#define SMP_ECGWIN 0x00000002 //Failed to create GLFWwindow
#define SMP_EIGLAD 0x00000004 //Failed to instantiate GLAD

//smpshdr error bit codes
#define SMP_ESHDRD 0x00000100 //Failed to read shader
#define SMP_ESHDWR 0x00000200 //Failed to write shader

//SHADER BIT-FLAGS
//smpshdr function mode bit codes
#define SMP_SHLVRT 0x00000001 //Load vertex shader
#define SMP_SHLFRG 0x00000002 //Load fragment shader

//smpshdr directory function mode bit codes
#define SMP_SHGVRT 0x00000004 //Get vertex shader files
#define SMP_SHGFRG 0x00000008 //Get fragment shader files
#define SMP_SHGALL 0x00000010 //Get ALL shader files specified
#define SMP_SHGTRG 0x00000020 //Get target shader files


extern int smpi_errno;
extern int smps_errno;

#endif

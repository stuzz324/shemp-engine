#include "smpinit.h"
//PRIVATE MACROS & PREDEFS


//PRIVATE FUNCTIONS


//GLOBAL EXTERN VARIABLES
GLFWwindow* smp_window = NULL;
int smpi_errno = 0;

//PUBLIC FUNCTIONS
int smp_init() {
    if (!glfwInit()) {
        printf("smp_init()::glfwInit(): failed\n");
        smpi_errno |= SMP_EIGLFW;
    }

    if ((smp_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL)) == NULL) {
        printf("smp_init()::glfwCreateWindow(): failed\n");
        glfwTerminate();
        smpi_errno |= SMP_ECGWIN;
    }
    glfwMakeContextCurrent(smp_window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        printf("smp_init()::gladLoadGL(): failed\n");
        smpi_errno |= SMP_EIGLAD;
    }

    if (smpi_errno != 0) return -1;
    return 0;
}

int smp_init_shdrs() {
    smp_pmatches_t* matches;
    //get shader source code
    smp_get_shdr_files(SMP_SHGVRT, &matches);

    //load shader source code


    //compile shader source code


    return 0;
}

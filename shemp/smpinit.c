#include "smpinit.h"
//PRIVATE MACROS & PREDEFS


//PRIVATE FUNCTIONS


//GLOBAL EXTERN VARIABLES
GLFWwindow* smp_window = NULL;
int smp_errno = 0;

//PUBLIC FUNCTIONS
int smp_init() {
    if (!glfwInit()) {
        printf("smp_init()::glfwInit(): failed\n");
        smp_errno |= SMP_EIGLFW;
    }

    if ((smp_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL)) == NULL) {
        printf("smp_init()::glfwCreateWindow(): failed\n");
        glfwTerminate();
        smp_errno |= SMP_ECGWIN;
    }
    glfwMakeContextCurrent(smp_window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        printf("smp_init()::gladLoadGL(): failed\n");
        smp_errno |= SMP_EIGLAD;
    }

    if (smp_errno != 0) return -1;
    return 0;
}

void smp_error(const char* msg) {
    printf("========SMP_ERROR========\n%s:\n", msg);
    if ((smp_errno & SMP_EIGLFW) == SMP_EIGLFW)
        printf("\tFailed to initialize GLFW\n");
    if ((smp_errno & SMP_ECGWIN) == SMP_ECGWIN)
        printf("\tFailed to create GLFWwindow\n");
    if ((smp_errno & SMP_EIGLAD) == SMP_EIGLAD)
        printf("\tFailed to initialize GLAD\n");
    printf("=========================\n");
}

void smp_error_test() {
    smp_errno |= SMP_EIGLFW | SMP_ECGWIN | SMP_EIGLAD;
    smp_error("[SMP_ERROR_TEST]");
    smp_errno = 0;
    smp_errno |= SMP_EIGLFW | SMP_EIGLAD;
    smp_error("[SMP_ERROR_TEST]");
    smp_errno = 0;
    smp_errno |= SMP_ECGWIN | SMP_EIGLAD;
    smp_error("[SMP_ERROR_TEST]");
    smp_errno = 0;
}

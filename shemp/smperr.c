#include "smperr.h"

void smpi_error(const char* msg) {
    printf("========SMPI_ERROR========\n%s:\n", msg);
    if ((smpi_errno & SMP_EIGLFW) == SMP_EIGLFW)
        printf("\t[%.8x] Failed to initialize GLFW\n", SMP_EIGLFW);
    if ((smpi_errno & SMP_ECGWIN) == SMP_ECGWIN)
        printf("\t[%.8x] Failed to create GLFWwindow\n", SMP_ECGWIN);
    if ((smpi_errno & SMP_EIGLAD) == SMP_EIGLAD)
        printf("\t[%.8x] Failed to initialize GLAD\n", SMP_EIGLAD);
    printf("==========================\n");
}

void smps_error(const char* msg) {
    printf("========SMPS_ERROR========\n%s:\n", msg);
    if ((smps_errno & SMP_ESHDRD) == SMP_ESHDRD)
        printf("\t[%.8x] Failed to read shader\n", SMP_ESHDRD);
    if ((smps_errno & SMP_ESHDWR) == SMP_ESHDWR)
        printf("\t[%.8x] Failed to write shader\n", SMP_ESHDWR);
    printf("==========================\n");
}

void smp_error() {
    if (0 < smpi_errno) {
        smpi_error("[ERROR TEST]");
    }
    if (0 < smps_errno) {
        smps_error("[ERROR TEST]");
    }
}

void smp_error_test() {
    smpi_errno |= SMP_EIGLFW | SMP_ECGWIN | SMP_EIGLAD;
    smps_errno |= SMP_ESHDRD | SMP_ESHDWR;
    smp_error();
    smpi_errno = 0;
    smps_errno = 0;
}

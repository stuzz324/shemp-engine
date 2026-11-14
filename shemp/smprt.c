#include "smprt.h"

void smp_inputs(GLFWwindow* window) {
    int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS) glfwSetWindowShouldClose(window, 1);
}

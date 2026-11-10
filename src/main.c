#include <stdlib.h>
#include <stdio.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <smpinit.h>
#include <smperr.h>

int main(int argc, char** argv) {
    smp_error_test();
    int init_ret = smp_init();

    printf("smp_window: %p\n", smp_window);

    //render loop
    if (init_ret != -1) {
        while (!glfwWindowShouldClose(smp_window)) {
            glClearColor(0.3f,0.3f,0.3f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwPollEvents();
            glfwSwapBuffers(smp_window);
        }
    } else printf("skipping render loop; killing program\n");

    glfwTerminate();
    return 0;
}

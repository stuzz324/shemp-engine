#include <stdlib.h>
#include <stdio.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <smpinit.h>
#include <smperr.h>
#include <smprt.h>
#include <smpshdr.h>
#include <getopt.h>
#include <sys/time.h>

const char* smp_opt_arr = {
    "-t|--test "
};

void print_help_list() {
    printf("Usage:\n");
    printf("  shemp_main [options]\n\n");
    printf("Options:\n");
    printf("  -t, --test\t\ttest default program");
}

struct flags {
    int help;
    int test;
} flags;

int lo_idx;
struct option l_opts[] = {
    { "help",    no_argument,    &flags.help,   'h' },
    { "test",    no_argument,    &flags.test,   't' },
    { 0,         0,              0,              0  }
};

int main(int argc, char** argv) {
    int opt;
    while ((opt = getopt_long(argc, argv, ":th", l_opts, &lo_idx)) != -1) {
        switch (opt) {
            //Long opt
            case 1:
                break;
            //Test opt
            case 't':
                //smp_error_test();
                //smp_test_shdr();
                //smp_test_gsf();
                //smp_proto_get_test();
                // smp_pmatches_t* matches;
                // struct timeval t0, t1;
                // unsigned int i;
                //
                // gettimeofday(&t0, NULL);
                // for(i = 0; i < 1000; i++) {
                //     smp_get_shdr_files(SMP_SHGVRT, &matches);
                // }
                // gettimeofday(&t1, NULL);
                // printf("%u calls in %g\n", i, t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));

                smp_test_sources();

                break;
            //Help opt
            case 'h':
                print_help_list();
                break;
            case '?':
                printf("Unknown option '%c'\n", optarg);
                print_help_list();
                break;
            case ':':
                printf("Option argument required for '%c'\n", optarg);
                print_help_list();
                break;
        }
    }
    if (flags.test) {
        int init_ret = smp_init();

        printf("smp_window: %p\n", smp_window);

        //render loop
        if (init_ret != -1) {
            while (!glfwWindowShouldClose(smp_window)) {
                smp_inputs(smp_window);
                glClearColor(0.3f,0.3f,0.3f,1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                glfwPollEvents();
                glfwSwapBuffers(smp_window);
            }
        } else printf("skipping render loop; killing program\n");

        glfwTerminate();
    }

    return 0;
}

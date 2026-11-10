#include "smpshdr.h"

int smps_errno = 0;

rdbuf* smp_read_shdr() {
    int fd;
    //open
    if ((fd = open("./data/shaders", O_RDONLY)) == -1) {
        perror("smp_read_shdr()::open()");
        return NULL;
    }

    //read
    rdbuf* rb = create_rdbuf(fd);
    if (read(fd, rb->str, rb->len) == -1) {
        perror("smp_read_shdr()::read()");
        return NULL;
    }


    return rb;
}

int smp_write_shdr() {

    return 0;
}

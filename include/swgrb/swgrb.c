#include "swgrb.h"

//fd MUST be open
rdbuf* create_rdbuf(int fd) {
    rdbuf* rb;
    size_t len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    rb = malloc(sizeof(rdbuf) + len + 1);
    rb->len = len;

    return rb;
}

rdbuf* create_rdbuf_path(const char* path, int flags) {
    rdbuf* rb;
    int fd;

    if ((fd = open(path, flags)) == -1) {
        perror("create_rdbuf_path()::open()");
        return NULL;
    }

    size_t len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    rb = malloc(sizeof(rdbuf) + len + 1);
    rb->len = len;

    return rb;
}

void resize_rdbuf(rdbuf** rb, size_t new_len) {
    *rb = realloc(*rb, sizeof(rdbuf) + new_len + 1);
    (*rb)->len = new_len;
}



#ifndef SWGRB_H
#define SWGRB_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
typedef struct rdbuf {
    size_t len;
    char str[];
} rdbuf;

//fd MUST be open
rdbuf* create_rdbuf(int fd);
rdbuf* create_rdbuf_path(const char* path, int flags);

void resize_rdbuf(rdbuf** rb, size_t new_len);

#endif

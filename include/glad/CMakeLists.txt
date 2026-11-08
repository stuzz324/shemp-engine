cmake_minimum_required(VERSION 4.4.0)

add_library(glad)

target_sources(glad
    PRIVATE
        src/gl.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            include/glad/gl.h
)

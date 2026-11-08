cmake_minimum_required(VERSION 4.4.0)

add_library(shemp_libs)

target_sources(shemp_libs
    PRIVATE
        smpinit.c
        smpshdr.c
    PUBLIC
        FILE_SET HEADERS
        FILES
            smpinit.h
            smpshdr.h
)

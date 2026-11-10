cmake_minimum_required(VERSION 4.4.0)

add_library(swgrb)

target_sources(swgrb
    PRIVATE
        swgrb.c
    PUBLIC
        FILE_SET HEADERS
        FILES
            swgrb.h
)

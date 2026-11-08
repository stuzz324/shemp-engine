cmake_minimum_required(VERSION 4.4.0)

project(shemp_engine)

add_executable(shemp_main)

target_sources(shemp_main
    PRIVATE
        src/main.c
)

add_subdirectory(shemp)
add_subdirectory(include)

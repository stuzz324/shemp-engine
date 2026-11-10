cmake_minimum_required(VERSION 4.4.0)

# loader library
add_subdirectory(glad)
# framework
add_subdirectory(glfw)
# c-based math library for graphics rendering
add_subdirectory(cglm)
# custom read buffer library
add_subdirectory(swgrb)

find_package(OpenGL REQUIRED)

target_link_libraries(shemp_libs
    PUBLIC
        glad
        glfw
        OpenGL::GL
        cglm
        swgrb
)

target_link_libraries(shemp_main
    PUBLIC
        shemp_libs
)


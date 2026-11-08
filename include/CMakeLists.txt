cmake_minimum_required(VERSION 4.4.0)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(cglm)

find_package(OpenGL REQUIRED)

target_link_libraries(shemp_main
    PRIVATE
        glad
        glfw
        OpenGL::GL
        cglm
)

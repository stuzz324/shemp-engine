cmake_minimum_required(VERSION 4.4.0)

add_subdirectory(glfw)
add_subdirectory(glad)

find_package(OpenGL REQUIRED)

target_link_libraries(shemp_main
    PRIVATE
        OpenGL::GL
        glad
        glfw
)

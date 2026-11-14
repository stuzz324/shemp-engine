# SHEMP-ENGINE

## What it is.

## Why it is named this.

## The things it uses.

## Reading shader data from files.
Shader data is stored in a specific, simple way:


# KNOWN ISSUES
1. make keeps detecting clock-skews for *glad/src/gl.c* on 
   project build. This is most likely due to how I am linking 
   it in CMakeLists.txt. Specifically that *gl.h* already gets 
   linked through GLFW. (11-09-2026: has disappeared??)

# TODO
1. Settle upon a way to store vertex data in arrays.

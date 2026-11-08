# SHEMP-ENGINE

## What it is.

## Why it is named this.

## The things it uses.

# KNOWN ISSUES
1. make keeps detecting clock-skews for *glad/src/gl.c* on 
   project build. This is most likely due to how I am linking 
   it in CMakeLists.txt. Specifically that *gl.h* already gets 
   linked through GLFW.

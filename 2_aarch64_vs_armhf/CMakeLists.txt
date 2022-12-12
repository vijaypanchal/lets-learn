# set minimum cmake version
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

if(ARMHF) 
    message("-- Compiler is selected for Armhf Arch !!")
    set(CMAKE_C_COMPILER arm-linux-gnueabi-gcc)
    set(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)
else()
    message("-- Compiler is selected for Aarch64 Arch !!")
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)    
endif()
    
# project name and language
project(cmake-compiler-flags LANGUAGES CXX)

# set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_compile_options("-fsanitize=address")
#link_libraries("-fsanitize=address")

# always build shared libraries by default
set(BUILD_SHARED_LIBS OFF)

# export symbols on Windows for shared libraries to work
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# compile an object library for producing a shared and dynamic library
if(ARMHF) 
    message("-- Library name selected : src-armhf")
    add_library(src-armhf
        inc/inc.h
        src/src.cpp
    )
else()
    message("-- Library name selected : src-aarch64")
    add_library(src-aarch64
        inc/inc.h
        src/src.cpp
    )
endif()

# generate executable
add_executable(main main.cpp)

# link to shared library 
if(ARMHF) 
    target_link_libraries(main src-armhf)
else() 
    target_link_libraries(main src-aarch64)   
endif()
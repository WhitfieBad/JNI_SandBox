cmake_minimum_required(VERSION 3.19)
project(JNI_SandBox)

set(CMAKE_CXX_STANDARD 20)

add_library(JNI_SandBox SHARED main.cpp)

target_include_directories(JNI_SandBox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/jni)
target_include_directories(JNI_SandBox PRIVATE include/jni/linux)

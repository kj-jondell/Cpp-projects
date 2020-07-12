cmake_minimum_required(VERSION 3.10)
project(CHuffman VERSION 0.01)

find_library(RTMIDI RtMidi)
add_library(RtMidi SHARED IMPORTED GLOBAL)

add_executable(CHuffman huffman.cpp)

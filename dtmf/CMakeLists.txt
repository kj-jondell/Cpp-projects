cmake_minimum_required(VERSION 3.10)
project(DTMFDecoder VERSION 0.01)

find_package(portaudio)

add_executable(DTMFDecoder Player.cpp Player.h Decoder.h Decoder.cpp main.cpp)

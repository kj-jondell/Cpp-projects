cmake_minimum_required(VERSION 3.10..3.17)
set(CMAKE_CXX_STANDARD 14)
project(Sampler VERSION 0.01)

if(APPLE)
    find_library(SNDFILE SndFile)
endif()

add_library(
    libsampler STATIC
    Sampler.h Sampler.cpp
)

if(NOT APPLE)
    target_link_libraries(libsampler sndfile)
endif()

if(APPLE)
    target_include_directories(libsampler PUBLIC /usr/local/include)
    target_link_libraries(libsampler ${SNDFILE})
endif()

cmake_minimum_required(VERSION 3.10..3.17)
set(CMAKE_CXX_STANDARD 14)
project(Sampler VERSION 0.01)

if(APPLE)
    find_library(AUDIO_UNIT AudioUnit)
    find_library(CORE_SERVICES CoreServices)
    find_library(CORE_FOUNDATION CoreFoundation)
    find_library(AUDIO_TOOLBOX AudioToolbox)
    find_library(CORE_AUDIO CoreAudio)
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
    target_link_libraries(libsampler ${AUDIO_UNIT})
    target_link_libraries(libsampler ${CORE_SERVICES})
    target_link_libraries(libsampler ${CORE_FOUNDATION})
    target_link_libraries(libsampler ${AUDIO_TOOLBOX})
    target_link_libraries(libsampler ${CORE_AUDIO})
    target_include_directories(libsampler PUBLIC /usr/local/include)
    target_link_libraries(libsampler ${SNDFILE})
endif()

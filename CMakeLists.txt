cmake_minimum_required(VERSION 3.10..3.17)
set(CMAKE_CXX_STANDARD 17)
project(DTMFDecoder VERSION 0.01)

if(APPLE)
    find_library(AUDIO_UNIT AudioUnit)
    find_library(CORE_SERVICES CoreServices)
    find_library(CORE_FOUNDATION CoreFoundation)
    find_library(AUDIO_TOOLBOX AudioToolbox)
    find_library(CORE_AUDIO CoreAudio)
    find_library(PORTAUDIO portaudio)
endif()

include_directories(sampler)
add_subdirectory(sampler)

add_library(
    playerlib STATIC
    Player.cpp Player.h Decoder.h Decoder.cpp 
)

target_link_libraries(playerlib libsampler)
add_executable(DTMFDecoder main.cpp)

target_include_directories(playerlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/goertzel/include") 

if(NOT APPLE)
target_link_libraries(playerlib portaudio)
endif()

if(APPLE)
    target_link_libraries(playerlib ${AUDIO_UNIT})
    target_link_libraries(playerlib ${CORE_SERVICES})
    target_link_libraries(playerlib ${CORE_FOUNDATION})
    target_link_libraries(playerlib ${AUDIO_TOOLBOX})
    target_link_libraries(playerlib ${CORE_AUDIO})
    target_include_directories(playerlib PUBLIC /usr/local/include)
    target_link_libraries(playerlib ${PORTAUDIO})
endif()

target_link_libraries(DTMFDecoder playerlib)

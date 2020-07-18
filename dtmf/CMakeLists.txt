cmake_minimum_required(VERSION 3.10..3.17)
project(DTMFDecoder VERSION 0.01)

if(APPLE)
    find_library(AUDIO_UNIT AudioUnit)
    find_library(CORE_SERVICES CoreServices)
    find_library(CORE_FOUNDATION CoreFoundation)
    find_library(AUDIO_TOOLBOX AudioToolbox)
    find_library(CORE_AUDIO CoreAudio)
endif()

add_library(
    playerlib STATIC
    Player.cpp Player.h Decoder.h Decoder.cpp 
)

add_executable(DTMFDecoder main.cpp)

target_include_directories(playerlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/goertzel/include") 

target_include_directories(playerlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/libsndfile/include") 
target_link_libraries(playerlib "${CMAKE_CURRENT_SOURCE_DIR}/libs/libsndfile/lib/libsndfile.a")

target_include_directories(playerlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/portaudio/include")
target_link_libraries(playerlib "${CMAKE_CURRENT_SOURCE_DIR}/libs/portaudio/lib/libportaudio.a")
target_link_libraries(playerlib "${CMAKE_CURRENT_SOURCE_DIR}/libs/portaudio/lib/libportaudiocpp.a")

if(APPLE)
    target_link_libraries(playerlib ${AUDIO_UNIT})
    target_link_libraries(playerlib ${CORE_SERVICES})
    target_link_libraries(playerlib ${CORE_FOUNDATION})
    target_link_libraries(playerlib ${AUDIO_TOOLBOX})
    target_link_libraries(playerlib ${CORE_AUDIO})
endif()

target_link_libraries(DTMFDecoder playerlib)

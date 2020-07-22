cmake_minimum_required(VERSION 3.10..3.17)
set(CMAKE_CXX_STANDARD 14)
project(Sampler VERSION 0.01)

if(APPLE)
    find_library(AUDIO_UNIT AudioUnit)
    find_library(CORE_SERVICES CoreServices)
    find_library(CORE_FOUNDATION CoreFoundation)
    find_library(AUDIO_TOOLBOX AudioToolbox)
    find_library(CORE_AUDIO CoreAudio)
    find_library(LIBSNDFILE Sndfile)
endif()

add_library(
    libsampler STATIC
    Sampler.h Sampler.cpp
)

add_executable(Sampler main.cpp)

if(NOT APPLE)
    target_link_libraries(libsampler sndfile)
endif()

if(APPLE)
    target_link_libraries(libsampler ${AUDIO_UNIT})
    target_link_libraries(libsampler ${CORE_SERVICES})
    target_link_libraries(libsampler ${CORE_FOUNDATION})
    target_link_libraries(libsampler ${AUDIO_TOOLBOX})
    target_link_libraries(libsampler ${CORE_AUDIO})
    target_include_directories(libsampler PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../libs/libsndfile/include") 
    target_link_libraries(libsampler ${LIBSNDFILE})
endif()

target_link_libraries(Sampler libsampler)

cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(openmpSTFT VERSION 0.1.0 LANGUAGES C CXX)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(openmpsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/)


add_executable(openmpRun ${openmpsrc})


cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(templateRunner VERSION 0.1.0 LANGUAGES C CXX)




include(FetchContent)


FetchContent_Declare(
  ixws
  GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
  GIT_TAG v11.4.5
)

FetchContent_MakeAvailable(ixws)

find_package(ZLIB REQUIRED)
find_package(CapnProto REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)



set(templatesrc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TemplateImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/functionImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../GLOBAL/RunnerCommon.cpp #common implementation
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/FFTStruct.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/FFTStruct_SetGet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/FFTcapnp.capnp.c++
    
    )



add_executable(templateRun ${templatesrc})

target_link_libraries(templateRun PRIVATE CapnProto::capnp CapnProto::kj)

target_include_directories(templateRun PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../GLOBAL#reverseOOP
    ${CMAKE_CURRENT_SOURCE_DIR}/kernel
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

if(WIN32)
    if(MSVC)
        target_link_libraries(templateRun PRIVATE
            $<$<CONFIG:Release>:${ixws_BINARY_DIR}/Release/ixwebsocket.lib>
            $<$<CONFIG:Debug>:${ixws_BINARY_DIR}/Debug/ixwebsocket.lib>
            )
    else()
        target_link_libraries(templateRun PRIVATE 
        ${ixws_BINARY_DIR}/ixwebsocket.lib)
    endif()
else()
    target_link_libraries(templateRun PRIVATE 
    ${ixws_BINARY_DIR}/libixwebsocket.a)
    
endif()
target_link_libraries(templateRun PRIVATE ZLIB::ZLIB)
target_include_directories(templateRun PRIVATE ${ixws_SOURCE_DIR}/ixwebsocket)
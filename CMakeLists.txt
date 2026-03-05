# Copyright(C) 2024 Rokae Technology Co., Ltd. All Rights Reserved.
# Information in this file is the intellectual property of Rokae Technology Co., Ltd,
# And may contains trade secrets that must be stored and viewed confidentially.
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project (example CXX C)

# 1. 定义编译架构参数，默认 x86_64（本地编译）
# 使用方式：cmake -DARCH=aarch64 .. （交叉编译）；cmake .. （默认x86本地编译）
set(ARCH "x86_64" CACHE STRING "Target architecture: x86_64 or aarch64")

# 2. 根据架构选择编译工具链
if(ARCH STREQUAL "aarch64")
    # aarch64交叉编译工具链路径
    set(CMAKE_C_COMPILER "aarch64-linux-gnu-gcc")
    set(CMAKE_CXX_COMPILER "aarch64-linux-gnu-g++")
    # 可选：添加交叉编译的系统根目录（如果需要）
    # set(CMAKE_SYSROOT "/path/to/aarch64/sysroot")
    message(STATUS "Using aarch64 cross compiler: ${CMAKE_CXX_COMPILER}")
elseif(ARCH STREQUAL "x86_64")
    # x86_64本地编译，使用系统默认的gcc/g++
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
    message(STATUS "Using x86_64 native compiler: ${CMAKE_CXX_COMPILER}")
else()
    message(FATAL_ERROR "Unsupported ARCH: ${ARCH}, only x86_64 and aarch64 are supported")
endif()

SET(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)

add_compile_options(-fPIC)
#add_compile_options(-shared)
#add_compile_options(-g)


add_library (${PROJECT_NAME} SHARED)

#默认设置动态库外部不可见，需要自行导出
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

#logger define 
ADD_DEFINITIONS(-DLOGIMPL_TYPE=1)
ADD_DEFINITIONS(-DOROCOS_TARGET=xenomai)

ADD_DEFINITIONS(-DAPI_EXCLUDE_XROBOT)
ADD_DEFINITIONS(-DAPI_EXCLUDE_XSUPPORT)








#设置头文件路径
target_include_directories(${PROJECT_NAME}  PUBLIC
    
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/x64/google/g3log/include
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/x64/jsoncpp/include

    ${CMAKE_CURRENT_SOURCE_DIR}/imol_api
    ${CMAKE_CURRENT_SOURCE_DIR}/xcore_api

    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/src

)


set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "") 
#set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX "")

#[[ ]]

add_subdirectory (config)
add_subdirectory (src)
add_subdirectory (examples)


TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE cmrc_config)

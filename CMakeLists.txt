# Copyright(C) 2024 Rokae Technology Co., Ltd. All Rights Reserved.
# Information in this file is the intellectual property of Rokae Technology Co., Ltd,
# And may contains trade secrets that must be stored and viewed confidentially.
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project (example CXX C)

SET(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)

if(NOT ROKAE_ARCH)
    set(ROKAE_ARCH "x86_64")
    # 或者 message(FATAL_ERROR "Please set -DROKAE_ARCH=...")
endif()

add_compile_options(-fPIC)

add_library (${PROJECT_NAME} SHARED)

#默认设置动态库外部不可见，需要自行导出
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

#设置头文件路径
target_include_directories(${PROJECT_NAME}  PUBLIC
    
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/${ROKAE_ARCH}/google/g3log/include
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/${ROKAE_ARCH}/jsoncpp/include

    ${CMAKE_CURRENT_SOURCE_DIR}/xcore_api

    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/src

)

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "") 

add_subdirectory (config)
add_subdirectory (src)
add_subdirectory (examples)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE cmrc_config)

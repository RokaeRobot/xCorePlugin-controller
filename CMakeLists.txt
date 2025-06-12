# Copyright(C) 2025 Rokae Technology Co., Ltd. All Rights Reserved.
# Information in this file is the intellectual property of Rokae Technology Co., Ltd,
# And may contains trade secrets that must be stored and viewed confidentially.
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

#开发者需要在此修改为自己的插件名字
project (example CXX C)

SET(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)

add_compile_options(-fPIC)
add_compile_options(-shared)

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

#设置头文件查找路径
target_include_directories(${PROJECT_NAME}  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/x64/google/g3log/include
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/x64/jsoncpp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/xcore_api
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
#设置插件生成路径
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "") 

add_subdirectory (src)
#add_subdirectory (examples)


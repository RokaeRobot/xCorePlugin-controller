cmake_minimum_required(VERSION 3.0.0)
Project(orocos-kdl)

add_definitions(-std=c++11)
# add_definitions(-DBOOST_ALL_DYN_LINK)

IF (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
ENDIF()

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	ADD_DEFINITIONS(-DDEBUG)
ELSEIF (CMAKE_BUILD_TYPE STREQUAL Release)
	ADD_DEFINITIONS(-DRELEASE)
ENDIF()

message(STATUS "project src path : ${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/kdl)
include_directories(${PROJECT_SOURCE_DIR}/kdl/utilities)
# Eigen 头文件位于 src_lib/Eigen/Core，故 include 根目录为 src_lib(即 Eigen 的父目录)
include_directories(${PROJECT_SOURCE_DIR}/..)

file(GLOB KDL_SRC kdl/*.cpp)
file(GLOB UTIL_LIST  kdl/utilities/*.cpp)

add_library(orocos-kdl 
			${KDL_SRC}
            ${UTIL_LIST}
            )

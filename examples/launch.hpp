/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file launch.cpp
 * @brief 各模块例子的入口函数
 */
#pragma once
#include "launch/launch_api.hpp"

/**
 * @brief 1：继承LaunchAPI
 * @note 继承类的生命周期:
 * 1>加载插件时调用构造函数，
 * 2>插件加载完毕，按优先级依次调用各个模块的Init，Start,Stop函数
 * 3>调用析构函数
 */
class ExampleLaunch:public xcore_api::launch::LaunchAPI{
public:
    explicit ExampleLaunch();
    virtual void Init();
    virtual void Start();
    virtual void Stop();
    virtual ~ExampleLaunch();
};


/**
 * @brief 各个模块的入口函数声明
*/
void FunctionCodeExample();

void HooksExample();

void LogExampleInit();
void LogExample();

void ModbusExample();

void MotionCmdExampleInit();
    
void RLCmdExampleInit();

void RLTaskExample();

void ServiceExampleInit();

void StatesExample();

void UserLogExampleInit();
void UserLogExample();










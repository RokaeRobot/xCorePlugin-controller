/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file launch.cpp
 * @brief 例子的入口,从这里调用各个例子函数
 */
#include <iostream>
#include <string>
#include <g3log/g3log.hpp>
#include <cassert>
#include "utils/thread_pool_api.hpp"
#include "launch.hpp"
#include "rl_cmd.hpp"

/**
 * @brief 2：声明该类为一个初始化模块
 * @note 不声明该类不会执行初始化逻辑
 */
LAUNCH_MODULE(ExampleLaunch);

/**
 * @brief 3:构造函数
 * @note 各个无依赖的插件的构造顺序未定义，如果插件A依赖插件B
 * 会保证A比B后加载
 */
ExampleLaunch::ExampleLaunch(){
    LOG(INFO)<<"construct Example launch";
}

/**
 * @brief 4：在此实现注册时候的逻辑，所有插件都执行完Init之后才会开始执行Start
 */
void ExampleLaunch::Init() {
    //log 
    LogExampleInit();
    //motion cmd
    MotionCmdExampleInit();
    //multiple cmd
    MultipleCmdExampleInit();
    //printq
    RLCmdExampleInit();
    //service
    ServiceExampleInit();
    //userlog
    UserLogExampleInit();
}
/**
 * @brief 5：启动阶段
 */
void ExampleLaunch::Start() {
    LOG(INFO)<<"Example launch Start";
   
    //function code
    FunctionCodeExample();
    //hooks
    HooksExample();

    LogExample();

    ModbusExample();

   //rl task
    xcore_api::utils::RunInThreadPoolAPI(RLTaskExample);
    //states
    xcore_api::utils::RunInThreadPoolAPI(StatesExample);

    UserLogExample();
}

/**
 * @brief 6：结束阶段，可在此按优先级顺序回收资源
 */
void ExampleLaunch::Stop() {
    LOG(INFO)<<"Example launch Stop";
}

/**
 * @brief 7:析构函数，析构时候顺序未定义，无论是否有依赖关系
 */
ExampleLaunch::~ExampleLaunch(){
    LOG(INFO)<<"deconstruct Example launch";
}





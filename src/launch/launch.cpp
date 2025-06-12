/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file launch.cpp
 * @brief 插件启动入口模块，作为插件程序的调用入口
 *
 */

#include <iostream>
#include <string>
#include <g3log/g3log.hpp>
#include <cassert>

#include "launch.hpp"
#include "utils/singleton_api.hpp"

namespace plugin{
/**
 * @brief 声明模块作为启动入口模块，优先级越高越先执行
 */
LAUNCH_MODULE_PRIORITY(Launch,0)

/**
 * @brief 构造函数,保证有依赖关系的插件先构造。
 * eg: A插件依赖B插件，保证A插件所有的入口模块在B插件之前执行。
 * 没有依赖关系的插件入口模块构造顺序未定义
 */
Launch::Launch() {
     LOG(INFO)<<"construct lauunch";
}
/**
 * @brief 插件构造完毕之后，所有插件按优先级依次执行Init函数
 */
void Launch::Init() {
    LOG(INFO)<<"launch init";
}
/**
 * @brief 所有插件执行完Init之后,按优先级依次执行Start函数
 */
void Launch::Start() {
    LOG(INFO)<<"launch start";
}
/**
 * @brief 所有插件销毁时按优先级依次执行stop函数
 */
void Launch::Stop() {
    LOG(INFO)<<"launch stop";
}
/**
 * @brief 销毁所有入口模块，此时不保证销毁顺序。
 */
Launch::~Launch() {
     LOG(INFO)<<"deconstruct launch";
}



}







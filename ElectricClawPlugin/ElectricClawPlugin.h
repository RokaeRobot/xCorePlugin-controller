/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 *
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 *
 * @file ElectricClawPlugin.h
 * @brief 插件主流程
 */
#pragma once
#include <iostream>
#include <string>
#include <g3log/g3log.hpp>
#include <cassert>
#include "utils/thread_pool_api.hpp"
#include "launch/launch_api.hpp"
#include "ElectricClawRLCmd.h"
#include "ElectricClawService.h"

/**
 * @brief 1：继承LaunchAPI
 * 继承类的生命周期:
 * 1>加载插件时调用构造函数，
 * 2>插件加载完毕，按优先级依次调用各个模块的Init，Start,Stop函数
 * 3>调用析构函数
 */
class ElectricClawPlugin : public xcore_api::launch::LaunchAPI{
public:
    explicit ElectricClawPlugin();
    virtual void Init();
    virtual void Start();
    virtual void Stop();
    virtual ~ElectricClawPlugin();
};

/**
 * @brief 2：声明该类为一个初始化模块
 * 不声明该类不会执行初始化逻辑
 */
LAUNCH_MODULE(ElectricClawPlugin);
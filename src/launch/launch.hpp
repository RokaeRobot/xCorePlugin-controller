/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file launch.hpp
 * @brief 插件入口模块
 */
#pragma once
#include "launch/launch_api.hpp"

namespace plugin{

class Launch:public xcore_api::launch::LaunchAPI{
public:
    /**
     * @brief 构造入口模块,控制器保证有依赖关系的插件先构造
     */
    explicit Launch();
    /**
     * @brief 启动前的初始化工作
     */
    virtual void Init() override;
    /**
     * @brief 插件具体实现功能可在此启动
     */
    virtual void Start() override;
    /**
     * @brief 插件销毁前的清理工作
     */
    virtual void Stop() override;
    /**
     * @brief 销毁该入口模块
     */
    virtual ~Launch();
};


}






/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file launch_api.hpp
 * @brief 插件的入口模块
 */
#pragma once
#include <memory>

namespace xcore_api{
namespace launch{

/**
 * @brief 入口模块的基类，继承该类并声明module即可作为入口类。
 * @example 具体执行流程：
 * 1: 插件A,B(构造),如无依赖顺序未定义
 * 2: 插件A Init()  ----> B Init()
 * 3: 插件A Start() ----> B Start() 
 * 4: 插件A Stop() ----> B Stop()  
 * 5：插件A，B(析构),顺序未定义
 */
class LaunchAPI{
public:
    /**
     * @brief 所有插件所有的入口模块按优先级依次执行初始化流程
     */
    virtual void Init() = 0;
    /**
     * @brief 所有插件所有的入口模块Init完毕之后依优先级执行Start
     */
    virtual void Start() = 0;
    /**
     * @brief 所有插件所有的入口模块依优先级执行Stop
     */
    virtual void Stop() = 0;
    /**
     * @brief 自动注册模块到控制器
     * @param priority 优先级
     * @param ptr 模块指针
     * @return true 成功
     * @return false 失败
     */
    static bool Register(int priority,std::shared_ptr<LaunchAPI> ptr);
};

}
}
/**
 * @brief 自动注册入口类对象到控制器中
 */
#define AUTO_REGISTER_NAME(_PREFIX, _SUFFIX) _PREFIX##_SUFFIX

#define AUTO_REGISTER_FUNC AUTO_REGISTER_NAME(_auto_register_func_, __LINE__)

#define AUTO_REGISTER_VAR AUTO_REGISTER_NAME(_auto_register_var_, __LINE__)

#define AUTO_REGISTER(_CONTENT) namespace {int AUTO_REGISTER_FUNC() { _CONTENT; return 0; } \
    const int __attribute__ ((unused)) AUTO_REGISTER_VAR = AUTO_REGISTER_FUNC(); /* NOLINT */}

/**
 * @brief 声明带有优先级的入口模块，优先级越高该模块初始化顺序越靠前
 */
#define LAUNCH_MODULE_PRIORITY(_CLASS_NAME, _PRI) AUTO_REGISTER(xcore_api::launch::LaunchAPI::Register(_PRI,std::make_shared<_CLASS_NAME>());)

/**
 * @brief 声明默认优先级位0的入口模块
 */
#define LAUNCH_MODULE(_CLASS_NAME) LAUNCH_MODULE_PRIORITY(_CLASS_NAME, 0)

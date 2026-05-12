/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 *
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 *
 * @file ElectricClawPlugin.cpp
 * @brief 插件主流程
 */
#include "ElectricClawPlugin.h"

/**
 * @brief 3：构造函数
 * 各个无依赖的插件的构造顺序未定义，如果插件A依赖插件B
 * 会保证A比B后加载
 */
ElectricClawPlugin::ElectricClawPlugin()
{
    LOG(INFO)<< "construct ElectricClawPlugin launch";
}

/**
 * @brief 4：在此实现注册时候的逻辑，所有插件都执行完Init之后才会开始执行Start
 */
void ElectricClawPlugin::Init() 
{
    LOG(INFO)<<"ElectricClawPlugin launch init";
    //electric claw cmd
    ElectricClawCmd();
    //service
    ServiceProtocol();
}
/**
 * @brief 5：启动阶段
 */
void ElectricClawPlugin::Start() 
{
    LOG(INFO) << "ElectricClawPlugin launch Start";
}

/**
 * @brief 6：结束阶段，可在此按优先级顺序回收资源
 */
void ElectricClawPlugin::Stop() 
{
    LOG(INFO)<< "ElectricClawPlugin launch Stop";
}

/**
 * @brief 7:析构函数，析构时候顺序未定义，无论是否有依赖关系
 */
ElectricClawPlugin::~ElectricClawPlugin()
{
    LOG(INFO)<< "deconstruct ElectricClawPlugin launch";
}





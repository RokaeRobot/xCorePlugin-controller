/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file states.cpp
 * @brief 当前机器人状态
 */
#include "states/states_api.hpp"
#include "log/log_api.hpp"

void StatesExample(){
    using namespace xcore_api::states;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    LOG_INFO<<"------------------start test state api------------------------------";
    xcore_api::states::StatesAPI api;
    //仿真模式
    LOG_INFO<<"is simu mode: "<<api.IsSimuMode();
    //手自动模式
    LOG_INFO<<"is auto mode: "<<api.IsAutoMode();
    //true设为自动，false设为手动
    LOG_INFO<<"set auto mode: "<<api.SetAutoMode(true);
    LOG_INFO<<"after set auto mode: "<<api.IsAutoMode();
    LOG_INFO<<"set manaual  mode: "<<api.SetAutoMode(false);
    LOG_INFO<<"is auto mode: "<<api.IsAutoMode();
    //true上电状态，false下电状态
    LOG_INFO<<"power state: "<<api.IsPowerOn();
    //上电
    LOG_INFO<<"set power on: "<<api.SetPowerOn(true);
    LOG_INFO<<"power state: "<<api.IsPowerOn();
    //下电
    LOG_INFO<<"set power off: "<<api.SetPowerOn(false);
    LOG_INFO<<"power state: "<<api.IsPowerOn();

    //任务空间空闲
    LOG_INFO<<"is task space ready:"<<api.IsTaskSpaceReady();
    LOG_INFO<<"set task space busy:"<<api.SetTaskSpace(TaskSpaceAPI::TS_BUSY,true);
    LOG_INFO<<"is task space ready: "<<api.IsTaskSpaceReady();
    LOG_INFO<<"set task space idle: "<<api.SetTaskSpace(TaskSpaceAPI::TS_BUSY,false);
    LOG_INFO<<"is task space ready: "<<api.IsTaskSpaceReady();

    //当前机器人状态繁/忙
    LOG_INFO<<"robot busy: "<<api.IsRobotBusy();
    LOG_INFO<<"set robot busy:"<<api.SetRobotBusy(true);
    LOG_INFO<<"robot busy: "<<api.IsRobotBusy();
    LOG_INFO<<"set robot idle: "<<api.SetRobotBusy(false);
    LOG_INFO<<"robot busy: "<<api.IsRobotBusy();
    //当前控制器处于的阶段，单步/连续等
    LOG_INFO<<"running state: "<<(int)api.GetRunningState();

    LOG_INFO<<"------------------end test state api------------------------------";
};

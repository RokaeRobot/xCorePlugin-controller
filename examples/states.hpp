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
#pragma once
#include "states/states_api.hpp"
#include <g3log/g3log.hpp>

void StatesExample(){
    using namespace xcore_api::states;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    LOG(INFO)<<"------------------start test state api------------------------------";
    xcore_api::states::StatesAPI api;
    //手自动模式
    LOG(INFO)<<"is auto mode: "<<api.IsAutoMode();
    //true设为自动，false设为手动
    LOG(INFO)<<"set auto mode: "<<api.SetAutoMode(true);
    LOG(INFO)<<"after set auto mode: "<<api.IsAutoMode();
    LOG(INFO)<<"set manaual  mode: "<<api.SetAutoMode(false);
    LOG(INFO)<<"is auto mode: "<<api.IsAutoMode();
    //true上电状态，false下电状态
    LOG(INFO)<<"power state: "<<api.IsPowerOn();
    //上电
    LOG(INFO)<<"set power on: "<<api.SetPowerOn(true);
    LOG(INFO)<<"power state: "<<api.IsPowerOn();
    //下电
    LOG(INFO)<<"set power off: "<<api.SetPowerOn(false);
    LOG(INFO)<<"power state: "<<api.IsPowerOn();

    //任务空间空闲
    LOG(INFO)<<"is task space ready:"<<api.IsTaskSpaceReady();
    LOG(INFO)<<"set task space busy:"<<api.SetTaskSpace(TaskSpaceAPI::TS_BUSY,true);
    LOG(INFO)<<"is task space ready: "<<api.IsTaskSpaceReady();
    LOG(INFO)<<"set task space idle: "<<api.SetTaskSpace(TaskSpaceAPI::TS_BUSY,false);
    LOG(INFO)<<"is task space ready: "<<api.IsTaskSpaceReady();

    //当前机器人状态繁/忙
    LOG(INFO)<<"robot busy: "<<api.IsRobotBusy();
    LOG(INFO)<<"set robot busy:"<<api.SetRobotBusy(true);
    LOG(INFO)<<"robot busy: "<<api.IsRobotBusy();
    LOG(INFO)<<"set robot idle: "<<api.SetRobotBusy(false);
    LOG(INFO)<<"robot busy: "<<api.IsRobotBusy();
    //当前控制器处于的阶段，单步/连续等
    LOG(INFO)<<"running state: "<<(int)api.GetRunningState();

    LOG(INFO)<<"------------------end test state api------------------------------";
};

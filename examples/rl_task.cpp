/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file rl_task.cpp
 * @brief 使用rl task的例子
 */
#include "rl_task/rl_task_api.hpp"
#include "log/log_api.hpp"

void RLTaskExample(){
    std::this_thread::sleep_for(std::chrono::seconds(5));
    LOG_INFO<<"------------------start test rl task api------------------------------";
    xcore_api::rl_task::RLTaskAPI api;
    LOG_INFO<<api.PPToMain();
    LOG_INFO<<api.IsProgramResetDone();
    //LOG_INFO<<api.PPToLine(1);
    //LOG_INFO<<api.PPToFunc(2);
    //LOG_INFO<<api.PPToMain();
    LOG_INFO<<api.ModifyProgramLoop(false);
    LOG_INFO<<api.StartRun();
    LOG_INFO<<api.IsTaskExists("task1");
    LOG_INFO<<api.IsTaskRunning("task0");
    LOG_INFO<<api.IsTaskRunning();
        auto par = api.GetPointedLine("task0");
    LOG_INFO<<par.first<<" "<<par.second;
    par = api.GetExecLine("task0");
    LOG_INFO<<par.first<<" "<<par.second;
    LOG_INFO<<api.SetPointedLine("task0","main.mod",10);
    LOG_INFO<<api.SetExecLine("task0","main.mod",11);
    par = api.GetPointedLine("task0");
    LOG_INFO<<par.first<<" "<<par.second;
    par = api.GetExecLine("task0");
    LOG_INFO<<par.first<<" "<<par.second;
    LOG_INFO<<api.PauseRun();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    LOG_INFO<<api.StartRun();
    LOG_INFO<<api.AlarmRLTask("task0");
    LOG_INFO<<api.PauseRunAndWaitIdle();
    LOG_INFO<<api.PauseTask("task0");
    LOG_INFO<<api.StopRun();
    LOG_INFO<<"------------------end test rl task api------------------------------";
}


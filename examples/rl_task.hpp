/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file rl_task.hpp
 * @brief 使用rl task的例子
 */
#include "rl_task/rl_task_api.hpp"
#include <g3log/g3log.hpp>

void RLTaskExample(){
    std::this_thread::sleep_for(std::chrono::seconds(5));
    LOG(INFO)<<"------------------start test rl task api------------------------------";
    xcore_api::rl_task::RLTaskAPI api;
    LOG(INFO)<<api.PPToMain();
    LOG(INFO)<<api.IsProgramResetDone();
    //LOG(INFO)<<api.PPToLine(1);
    //LOG(INFO)<<api.PPToFunc(2);
    //LOG(INFO)<<api.PPToMain();
    LOG(INFO)<<api.ModifyProgramLoop(false);
    LOG(INFO)<<api.StartRun();
    LOG(INFO)<<api.IsTaskExists("task1");
    LOG(INFO)<<api.IsTaskRunning("task0");
    LOG(INFO)<<api.IsTaskRunning();
        auto par = api.GetPointedLine("task0");
    LOG(INFO)<<par.first<<" "<<par.second;
    par = api.GetExecLine("task0");
    LOG(INFO)<<par.first<<" "<<par.second;
    LOG(INFO)<<api.SetPointedLine("task0","main.mod",10);
    LOG(INFO)<<api.SetExecLine("task0","main.mod",11);
    par = api.GetPointedLine("task0");
    LOG(INFO)<<par.first<<" "<<par.second;
    par = api.GetExecLine("task0");
    LOG(INFO)<<par.first<<" "<<par.second;
    LOG(INFO)<<api.PauseRun();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    LOG(INFO)<<api.StartRun();
    LOG(INFO)<<api.AlarmRLTask("task0");
    LOG(INFO)<<api.PauseRunAndWaitIdle();
    LOG(INFO)<<api.PauseTask("task0");
    LOG(INFO)<<api.StopRun();
    LOG(INFO)<<"------------------end test rl task api------------------------------";
}


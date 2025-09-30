/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file hooks.cpp
 * @brief hooks使用例子
 */
#include <iostream>
#include <string>
#include "log/log_api.hpp"
#include "hooks/hooks_api.hpp"

/**
 * @brief 测试所有的hooks
*/
void TestAllHooks(){
    namespace xhooks = xcore_api::hooks;
    xhooks::HookDataAPI data;
    using namespace xhooks;
    std::vector<HookEventAPI>v_data{POINT_CHANGE,PP_TO_MAIN,PP_TO_LINE,B_START_RUN,B_PAUSE_RUN,E_STOP_RUN};
    std::vector<std::string>v_name{"POINT_CHANGE","PP_TO_MAIN","PP_TO_LINE","B_START_RUN","B_PAUSE_RUN","E_STOP_RUN"};
    for(int i = 0;i<v_data.size();++i){
        data.SetEvent(v_data[i]);
        auto name = v_name[i];
        auto func = [name](const std::shared_ptr<const xhooks::HookArgsBaseAPI> p){
            LOG_INFO<<"this is "<<name<< " empty callback";
        };
        data.SetHook(func);
        int id = xhooks::RegisterHooksAPI(data);
        LOG_INFO<<"register hook id:"<<id;
    }
}

/**
 * @brief 测试pp2line带参数的hook
*/
void TestPP2LineHooks(){
    namespace xhooks = xcore_api::hooks;
    xhooks::HookDataAPI data;
    data.SetEvent(xhooks::PP_TO_LINE);
    auto func = [](const std::shared_ptr<const xhooks::HookArgsBaseAPI> p){
        LOG_INFO<<"this is pp2line callback:";
        const auto ptr = std::dynamic_pointer_cast<const xhooks::HookPPToLineArgsAPI>(p);
        if(ptr == nullptr){
            LOG_INFO<<"pp2line callback: nullptr";
        } else {
            LOG_INFO<<ptr->GetTaskName()<<" : "<<ptr->GetFileName()<<" : "<<ptr->GetFileLine();
        }
    };
    data.SetHook(func);
    int id = xhooks::RegisterHooksAPI(data);
    LOG_INFO<<"register pp2line hook id:"<<id;
}

/**
 * @brief 测试点位更新带参数的hook
*/
void TestPointHooks(){
    namespace xhooks = xcore_api::hooks;
    xhooks::HookDataAPI data;
    data.SetEvent(xhooks::POINT_CHANGE);
    auto func = [](const std::shared_ptr<const xhooks::HookArgsBaseAPI> p){
        LOG_INFO<<"this is point change callback:";
        const auto ptr = std::dynamic_pointer_cast<const xhooks::HookPointArgsAPI>(p);
        if(ptr == nullptr){
            LOG(ERROR)<<"this is point change callback: nullptr";
        } else {
            LOG_INFO<<ptr->GetPointName()<<" : "<<(int)ptr->GetOperate();
        }
    };
    data.SetHook(func);
    int id = xhooks::RegisterHooksAPI(data);
    LOG_INFO<<"register point hook id:"<<id;
}

/**
 * @brief hooks的入口函数
*/
void HooksExample(){
    TestAllHooks();
    TestPP2LineHooks();
    TestPointHooks();
}

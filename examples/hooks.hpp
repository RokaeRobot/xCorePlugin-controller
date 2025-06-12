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
#pragma once
#include <iostream>
#include <string>
#include <g3log/g3log.hpp>
#include "hooks/hooks_api.hpp"

void HooksExample(){
    namespace xhooks = xcore_api::hooks;
    xhooks::HookDataAPI data;
    //设置关注点位变化通知
    data.SetEvent(xhooks::POINT_CHANGE);
    auto func = [](const std::shared_ptr<const xhooks::HookArgsBaseAPI> p){
        const auto ptr = std::dynamic_pointer_cast<const xhooks::HookPointArgsAPI>(p);
        if(ptr == nullptr){
            LOG(ERROR)<<"this is point change callback: nullptr";
        } else {
            LOG(INFO)<<ptr->GetPointName()<<" operate:"<<(int)ptr->GetOperate();
        }
    };
    data.SetHook(func);
    //注册到控制器，点位更新删除新建都会调用上述的func
    int id = xhooks::RegisterHooksAPI(data);
    LOG(INFO)<<"register hook id:"<<id;
}
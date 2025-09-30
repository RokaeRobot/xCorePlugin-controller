/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file log.cpp
 * @brief 插件单独日志的例子
 *
 */
#include <iostream>
#include <string>
#include <cassert>
#include "log/log_api.hpp"

void LogExampleInit() {
    //日志存储在当前插件的/data/log目录下
    xcore_api::log::InitLogAPI("log",10,3);
}
void LogExample() {
    std::thread t([](){
        int i = 0;
        while(i < 1000){
            LOG_DEBUG<<"test debug:"<<i++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            LOG_INFO<<"test info:"<<i++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            LOG_WARNING<<"test warning:"<<i++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            LOG_ERROR<<"test error:"<<i++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    t.detach();
}















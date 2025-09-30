/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file userlog.cpp
 * @brief 上报功能码例子
 */

#include <iostream>
#include <string>
#include <cmrc/cmrc.hpp>
#include "user_log/user_log_api.hpp"
#include "config/config.hpp"


CMRC_DECLARE(cmrc_config);

void UserLogExampleInit(){
    SINGLETON_INSTANCE(config::Config)->Init();
}

void UserLogExample(){
    SINGLETON_INSTANCE(config::Config)->Idle();

    xcore_api::user_log::ReportUserLogAPI(1000000);
    xcore_api::user_log::ReportUserLogAPI(1000000,"1000000.code","1000000");

    xcore_api::user_log::ReportRunLogAPI(1000100);

    assert(SINGLETON_INSTANCE(config::Config)->CheckUserLog() == true);
}












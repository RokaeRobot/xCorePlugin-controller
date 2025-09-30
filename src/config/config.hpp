/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file config.hpp
 * @brief 配置打包功能
 */
#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <json/json.h>


#include "utils/singleton_api.hpp"

namespace config{

class Config : public ::xcore_api::utils::SingletonBaseAPI<Config>{
    DECLARE_SINGLETON(Config);
public:
    void Init();
    void Idle();
    bool CheckUserLog();
    std::map<std::string,Json::Value> GetJsonFiles(const std::string &dir_in_conf_data);
private:
    Config(){};
    ~Config(){};
};



 



}












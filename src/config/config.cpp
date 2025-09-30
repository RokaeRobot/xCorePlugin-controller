/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file config.cpp
 * @brief 配置打包功能
 */
#include <unordered_set>
#include <cmrc/cmrc.hpp>

#include "log/log_api.hpp"
#include "user_log/user_log_api.hpp"
#include "utils/filesystem_api.hpp"
#include "config.hpp"

CMRC_DECLARE(cmrc_config);

namespace config{


void Config::Init() {
    using namespace xcore_api::user_log;
    auto userlog = GetJsonFiles("user_log/");
    for(auto &item : userlog){
        ConfigReportLogAPI(item.second);
    }
    auto userlog_en = GetJsonFiles("user_log_en/");
    for(auto &item : userlog_en){
        ConfigEnglishReportLogAPI(item.second);
    }

}


void Config::Idle() {
    ::xcore_api::user_log::RegisterReportLogAPI();
}

std::map<std::string,Json::Value> Config::GetJsonFiles(const std::string &dir_in_conf_data) {
    std::map<std::string,Json::Value> ret;
    try{
        auto cmrc_fs = cmrc::cmrc_config::get_filesystem();
        // conf_data目录下所有的json文件
        auto file_path = "cmrc_config/conf_data/" + dir_in_conf_data;

        for (auto&& entry : cmrc_fs.iterate_directory(file_path)) {
            Json::Value root;
            auto json_file = cmrc_fs.open(file_path + entry.filename());
            auto json_str = std::string(json_file.begin(), json_file.end());
            xcore_api::utils::LoadFromStringAPI(root,json_str);
            ret[dir_in_conf_data + entry.filename()] = root;
        }
    } catch (const std::exception& e) {
        LOG_WARNING<<dir_in_conf_data<<" exception:"<<e.what();
    }
    return ret;
}


bool Config::CheckUserLog() {
    
    auto func = [](const std::map<std::string,Json::Value> &userlog){
        std::map<int,std::set<std::string>> jkeys;
        for(auto &item:userlog){
                auto& record = item.second["user_record_t"];
                for (auto&rec : record) {
                    auto names = rec.getMemberNames();
                    std::set<std::string> keys_set(names.begin(),names.end());
                    jkeys[rec["id"].asInt()] = keys_set;
                }
            }
        return jkeys;
    };
    auto userlog = func(GetJsonFiles("user_log/"));
    auto userlog_en = func(GetJsonFiles("user_log_en/"));

    if(userlog != userlog_en){
        std::unordered_set<int>ids;
        for(auto &item:userlog){
            if(userlog_en[item.first] != item.second){
                ids.emplace(item.first);
            }
        }
        for(auto &item:userlog_en){
            if(userlog[item.first] != item.second){
                ids.emplace(item.first);
            }
        }
        for(auto &item:ids){
            LOG_ERROR<<"user_log id and user_log_en id not match:"<<item;
        }
        return false;
    }
    return true;
}





}













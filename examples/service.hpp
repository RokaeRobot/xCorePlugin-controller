/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file service.cpp
 * @brief 自定义协议
 */
#pragma once
#include <iostream>
#include <string>
#include <g3log/g3log.hpp>
#include "service/service_api.hpp"

/**
 * @brief 大于json数据
 * @param value json数据
 * @return std::string 字符串数据
 */
std::string json_serialize(const Json::Value& value){
    std::string raw = Json::FastWriter().write(value);
    raw[raw.length() - 1] = '\r'; // ending control, instead of \n
    return raw;
}
/**
 * @brief 实现自定义的通信协议
 * @note 需搭配客户端使用
 */
void ServiceProtocolExample() {
    /**
     * @brief 插件名称，插件的key，回调函数
     * @note 控制器收到json协议就会回调对应的函数
     * 用户收到的协议数据为{"key":"value"}
     */
    xcore_api::service::RegServiceAPI("example","get",
        [](const Json::Value &in){
            LOG(INFO)<<"receive:"<<json_serialize(in);
            //simu user process 
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Json::Value out;
            out["return"] = "0";
            return out;
        });
    xcore_api::service::RegServiceAPI("example","set",
        [](const Json::Value &in){
            LOG(INFO)<<json_serialize(in);
            Json::Value out;
            out["return"] = "0";
            return out;
        });
    xcore_api::service::RegServiceAPI("example","delete",
        [](const Json::Value &in){
            LOG(INFO)<<json_serialize(in);
            Json::Value out;
            out["return"] = "0";
            return out;
        });
}












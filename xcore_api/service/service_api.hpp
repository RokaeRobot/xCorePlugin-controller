/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file service_api.hpp
 * @brief 插件跟Client的通信协议，用户可自定义json数据实现自定义协议
 */
#pragma once
#include <string>
#include <functional>
#include <json/json.h>

namespace xcore_api{
namespace service{

/**
 * @brief 注册回调到一个协议，收到client发送的协议会匹配调用func回调
 * @param plugin_name 插件名称
 * @param key 定义插件的key
 * @param func 回调函数
 * @return int 0正常，其他错误
 */
int RegServiceAPI(const std::string & plugin_name,const std::string & key,
        const std::function<Json::Value(const Json::Value &)> & func);

}
}


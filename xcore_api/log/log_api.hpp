/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file log_api.hpp
 * @brief 插件日志模块
 */
#pragma once
#include <iostream>
#include <g3log/g3log.hpp>
#include "utils/filesystem_api.hpp"

namespace xcore_api{
namespace log{

/**
 * @brief 初始化插件日志信息
 * @param dir 日志存储目录，以插件的data目录为根目录
 * @param max_size 日志文件大小，单位M
 * @param max_number 日志存储数量
 * @note 存储不能超过1G
 * @return 0成功,其他失败
 */
int InitLogAPI(const std::string& dir,size_t max_size,size_t max_nubmer);

/**
 * @brief 用来初始化插件日志名称
 */
const std::string PLUGIN = xcore_api::utils::GetPluginNameAPI();

}
}

const LEVELS PDEBUG{::g3::kDebugValue,{"DEBUG|" + xcore_api::log::PLUGIN}},
   PINFO {::g3::kInfoValue, {"INFO|" + xcore_api::log::PLUGIN}},
   PWARNING {::g3::kWarningValue, {"WARN|" + xcore_api::log::PLUGIN}},
   PERROR{ ::g3::kWarningValue + 1,{"ERROR|" + xcore_api::log::PLUGIN} },
   PFATAL{ ::g3::kFatalValue, {"FATAL|" + xcore_api::log::PLUGIN} };

/**
 * @brief 插件日志宏，用户直接使用即可将日志过滤到该插件的单独日志中
 * @note 不使用如下宏，日志会跟控制器输出到一起
 */

#define LOG_DEBUG   LOG(PDEBUG)
#define LOG_INFO    LOG(PINFO)
#define LOG_WARNING LOG(PWARNING)
#define LOG_ERROR   LOG(PERROR)
#define LOG_FATAL   LOG(PFATAL)













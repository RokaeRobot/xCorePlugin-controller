/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file user_log_api.hpp
 * @brief 用户自定义的错误码
 */
#pragma once
#include <string>
#include <memory>
#include <json/json.h>

namespace xcore_api {
namespace user_log {

/**
 * @brief 初始化配置本插件的日志配置
 * @note 在插件的启动模块init阶段调用
 * @param val 具体json数据
 * @return int 0成功，其他失败
 */
int ConfigReportLogAPI(const Json::Value& val);

 /**
  * @brief 初始化配置插件的英文兜底日志。
  * @note 在插件的启动模块init阶段调用
  * @param val 
  * @return int 0成功，其他失败
  */
int ConfigEnglishReportLogAPI(const Json::Value& val);


/**
 * @brief 注册到xcore中并生效
 * @note 在插件的启动模块Start阶段调用
 * @return int 0成功，其他失败
 */
int RegisterReportLogAPI();

/**
 * @brief  多语言用户日志上报
 * @param1 log_no：日志编号（对于机器人状况的类型描述）
 * @param2 detail: 详细日志（同一个错误可能有若干细化的错误原因）
 * @param3 context:上下文，用以替换日志产生原因中的$arg，用于输入错误的上下文数据
 * @example
 *  {
 *      "14021": {
 *          "ZH":{
 *              "content":"打开总线设备失败, $arg",
 *              "others": ...
 *          }
 *      }
 *  },
 *
 * // user_log_details.json
 * {
 *      "14021.device_not_exist":{
 *          "ZH": "总线设备[$arg]不存在",
 *          "EN": "Device [$arg] not exist"
 *      }
 * }
 * ReportUserLog(14021, "14021.device_not_exist", "MODBUS_1");
 */
void ReportUserLogAPI(int log_no, const std::string& detail = "", const std::string& context = "");

/**
 * @brief  多语言用户运行日志上报
 * @param1 log_no：日志编号对应RunLog.json编号
 * @param2 arg: 参数用以替换content中的$arg参数
 * @param3 detail: 详细补充日志，会记录并最后在客户端详情页展示
 * */
void ReportRunLogAPI(int log_no, const std::string& arg = "", const std::string& detail = "");

}
}

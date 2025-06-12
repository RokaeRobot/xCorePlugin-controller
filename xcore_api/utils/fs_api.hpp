/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file fs_api.hpp
 * @brief 对文件操作的函数接口
 */

#pragma once
#include <string>
#include <json/json.h>

namespace xcore_api{
namespace utils{

/**
 * @brief 写入二进制文件
 * @param filename 文件名
 * @param content 写入内容
 * @return true成功
 * @return false失败
 */
bool WriteBinaryToFileAPI(const std::string& filename, const std::string& content);

/**
 * @brief 从文件中读取二进制内容
 * @param[in] filename 文件名
 * @param[out] content 读取内容
 * @return true成功
 * @return false失败
 */
bool ReadBinaryFromFileAPI(const std::string& filename, std::string& content);


/**
 * @brief 从文件解析并载入到Json::Value
 * @param root Json::Value
 * @param file_name 文件名
 * @return true成功
 * @return false失败
 */
bool LoadFromFileAPI(Json::Value &root, const std::string& file_name);

/**
 * @brief 从std::string解析JSON
 * @param root Json::Value
 * @param json_str JSON字符串
 * @return true成功
 * @return false失败
 */
bool LoadFromStringAPI(Json::Value& root, const std::string& json_str);

/**
 * @brief 将Json::Value写入到文件
 * @param root Json::Value
 * @param file_name 文件名
 * @return true成功
 * @return false失败
 */
bool SaveToFileAPI(const Json::Value& root, const std::string& file_name);

/**
 * @brief 将Json::Value写入到std::string
 * @param root Json数据
 * @return string字符串
 */
std::string SaveToStringAPI(const Json::Value& root);

/**
 * @brief 按行保存json数据到字符串
 * @param root json数据
 * @return std::string 字符串
 */
std::string SaveToStringInLineAPI(const Json::Value& root);

/**
 * @brief 新建一个空的的Json文件
 * @param path文件路径
 */
void CreateEmptyJsonFileAPI(const std::string& file_name);

/**
 * @brief 判断某个文件是否为Json文件
 * @param path：输入的文件路径
 * @return true 是
 * @return false 不是
 */
bool IsJsonFileAPI(const std::string& file_name);

} /* namespace utils */
} /* namespace xcore_api*/

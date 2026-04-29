/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 *
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 *
 * @file ElectricClawService.h
 * @brief 自定义协议
 */
#pragma once
#include <iostream>
#include <string>
#include <g3log/g3log.hpp>
#include "endtool/endtool_api.hpp"
#include "service/service_api.hpp"

#include "ElectricClawAPI.h"

extern ElectricClawUtil::ElectricClawAPI api;

/**
 * @brief 大于json数据
 * @param value json数据
 * @return std::string 字符串数据
 */
std::string json_serialize(const Json::Value &value);

/**
 * @brief 实现自定义的通信协议
 * 需搭配客户端使用
 */
void ServiceProtocol();

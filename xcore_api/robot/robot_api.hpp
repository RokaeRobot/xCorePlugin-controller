/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file robot_api.hpp
 * @brief 机器人相关的接口
 */
#pragma once
#include "const_data/pose_api.hpp"

namespace xcore_api{
namespace robot{
namespace xpose = ::xcore_api::const_data::pose;
/**
 * @brief 获取当前机器人位姿
*/
xpose::PointAPI GetCurPos();
/**
 * @brief 获取对应工具工件下当前机器人位姿
*/
xpose::PointAPI GetCurPosByToolWobj(const xcore_api::const_data::pose::ToolAPI& tool0,
                                                          const xcore_api::const_data::pose::WobjAPI& wobj0);

/**
 * @brief 获取当前界面右上角的工具
 * @return ToolAPI
 */
xcore_api::const_data::pose::ToolAPI GetCurToolAPI();

/**
 * @brief 获取当前界面右上角的工件
 * @return WobjAPI
 */
xcore_api::const_data::pose::WobjAPI GetCurWobjAPI();
}
}
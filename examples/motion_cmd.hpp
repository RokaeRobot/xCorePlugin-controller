/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file motion_cmd.hpp
 * @brief 测试各个运动指令的使用功能
 */
#pragma once
#include "rl_cmd/morden_rl_cmd_api.hpp"
#include "motion_cmd/motion_cmd_api.hpp"

namespace motion_cmd {
using namespace xcore_api::motion_cmd;
using namespace xcore_api::rl_cmd;
using namespace xcore_api::const_data::pose;

/**
 * @brief 实现指令PMoveAbsj
 */
DECLARE_MORDEN_RLCMD_API(PMoveAbsj);


/**
 * @brief 实现指令PMoveL
 */
DECLARE_MORDEN_RLCMD_API(PMoveL);


/**
 * @brief 实现指令PMoveC
 */
DECLARE_MORDEN_RLCMD_API(PMoveC);


/**
 * @brief 实现指令PMoveCF
 */
DECLARE_MORDEN_RLCMD_API(PMoveCF);


/**
 * @brief 实现指令PMoveJ
 */
DECLARE_MORDEN_RLCMD_API(PMoveJ);

/**
 * @brief 实现指令PSegMoveL
 */

DECLARE_MORDEN_RLCMD_API(PSegMoveL);

/**
 * @brief 实现步退直线指令PMoveBackL
 */

DECLARE_MORDEN_RLCMD_API(PMoveBackL);


/**
 * @brief 实现步退指令PMoveBackC
 */
DECLARE_MORDEN_RLCMD_API(PMoveBackC);

/**
 * @brief 实现坐标变换指令PPoseXPose，带返回值
 */
DECLARE_MORDEN_RLCMD_API(PPoseXPose);


}
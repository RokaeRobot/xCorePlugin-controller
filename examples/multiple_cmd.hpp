/**
 * Copyright (C) 2026 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 *
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 *
 * @file multiple_cmd.hpp
 * @brief 演示如何配置一条单语句多指令
 */
#pragma once
#include "rl_cmd/morden_rl_cmd_api.hpp"
#include "motion_cmd/motion_cmd_api.hpp"

namespace multiple_cmd {
using namespace xcore_api::motion_cmd;
using namespace xcore_api::rl_cmd;
using namespace xcore_api::const_data::pose;

/**
 * @brief 实现指令PMultiMoveL
 */
void RegMultiMoveL();

}

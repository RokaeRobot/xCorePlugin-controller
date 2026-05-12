/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 *
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 *
 * @file ElectricClawRLCmd.h
 * @brief 注册 RL 指令
 */
#pragma once
#include <g3log/g3log.hpp>
#include <unistd.h>
#include "endtool/endtool_api.hpp"
#include "rl_cmd/morden_rl_cmd_api.hpp"

#include "ElectricClawService.h"

extern ElectricClawUtil::ElectricClawAPI api;

namespace electric_claw_cmd
{
    using namespace xcore_api::rl_cmd;
    using namespace xcore_api::endtool;
    /**
     * @brief 定义指令ElectricClawStop
     */
    //DECLARE_MORDEN_RLCMD_API(ElectricClawStop);
    void RegElectricClawStop();

    /**
     * @brief 定义指令ElectricClawStart
     */
    //DECLARE_MORDEN_RLCMD_API(ElectricClawStart);
    void RegElectricClawStart();

    /**
     * @brief 定义指令ElectricClawStatus
     */
    //DECLARE_MORDEN_RLCMD_API(ElectricClawStatus);
    void RegElectricClawStatus();

}

/**
 * @brief 注册所有电磁爪控制指令到系统中
 */
void ElectricClawCmd();

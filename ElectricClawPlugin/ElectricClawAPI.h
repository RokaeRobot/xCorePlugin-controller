/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 *
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 *
 * @file ElectricClawAPI.h
 * @brief 插件操作接口
 */
#pragma once
#include <g3log/g3log.hpp>
#include <unistd.h>
#include "endtool/endtool_api.hpp"
#include "rl_cmd/morden_rl_cmd_api.hpp"

namespace ElectricClawUtil
{
    /**
     * @brief 电动夹爪 Modbus API 封装类
     * 通过底层 Modbus 接口（ModbusRTUEndtoolAPI）封装夹爪的控制指令。
     */
    class ElectricClawAPI
    {
    public:
        /**
         * @brief 启动电动夹爪
         * @param slave_id 从设备 ID
         * @param width 抓取宽度
         * @param force 抓取力度
         * @param speed 抓取速度
         * @param mode 工作模式
         * @return 是否写入成功
         */
        bool startElectricClaw(int slave_id, int width, int force, int speed, int mode);

        /**
         * @brief 停止电动夹爪
         * @param slave_id 从设备 ID
         * @return 是否写入成功
         */
        bool stopElectricClaw(int slave_id);

        /**
         * @brief 获取电动夹爪状态
         * @param slave_id 从设备 ID
         * @param status 状态码输出
         * @param external_width 外部宽度输出
         * @param internal_width 内部宽度输出
         * @param force 实际力度输出
         * @return 是否读取成功
         */
        bool getStatusElectricClaw(int slave_id,
                                   int& status, int& external_width, int& internal_width, int& force);

    private:
        xcore_api::endtool::ModbusRTUEndtoolAPI api;  // 底层 Modbus 通信对象
    };
}
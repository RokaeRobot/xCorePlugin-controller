/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 *
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 *
 * @file ElectricClawAPI.cpp
 * @brief 插件操作接口
 */
#include "ElectricClawAPI.h"

// 全局对象用于操作夹爪（可以考虑替换为单例或静态函数）
ElectricClawUtil::ElectricClawAPI api;

/**
 * @brief 启动夹爪设备（写入宽度、力度、速度、模式）
 */
bool ElectricClawUtil::ElectricClawAPI::startElectricClaw(int slave_id, int width, int force, int speed, int mode)
{
    bool ret = false;
    const int maxRetries = 3;
    const int retryDelayUs = 10000;            // 每次重试间隔 10ms
    const int registerAddress = 0x0000;        // 起始寄存器地址
    const int dataLength = 4;                  // 4 个寄存器

    for (int attempt = 1; attempt <= maxRetries; ++attempt)
    {
        ret = api.WriteRegister_10(
            slave_id,
            registerAddress,
            dataLength,
            {
                static_cast<uint16_t>(width),
                static_cast<uint16_t>(force),
                static_cast<uint16_t>(speed),
                static_cast<uint16_t>(mode)
            });

        if (ret)
            break;
        else
        {
            LOG(WARNING) << "WriteRegister_10 failed. Retry " << attempt << "/" << maxRetries;
            if (attempt < maxRetries)
                usleep(retryDelayUs);
        }
    }

    return ret;
}

/**
 * @brief 向夹爪发送停止命令
 */
bool ElectricClawUtil::ElectricClawAPI::stopElectricClaw(int slave_id)
{
    bool ret = false;
    const int maxRetries = 3;
    const int retryDelayUs = 10000;
    const int registerAddress = 0x0003;         // 停止命令寄存器
    const int dataLength = 1;
    const std::vector<uint16_t> data = {3};     // 3 表示停止命令

    for (int attempt = 1; attempt <= maxRetries; ++attempt)
    {
        ret = api.WriteRegister_06(slave_id, registerAddress, dataLength, data);

        if (ret)
            break;
        else
        {
            LOG(WARNING) << "WriteRegister_06 failed. Retry " << attempt << "/" << maxRetries;
            if (attempt < maxRetries)
                usleep(retryDelayUs);
        }
    }

    return ret;
}

/**
 * @brief 获取夹爪状态，包括状态码、外宽、内宽、抓力
 */
bool ElectricClawUtil::ElectricClawAPI::getStatusElectricClaw(int slave_id,
                                                              int& status, int& external_width, int& internal_width, int& force)
{
    bool ret = false;
    const int maxRetries = 3;
    const int retryDelayUs = 10000;
    const int registerAddress = 0x0100;         // 读取状态的起始寄存器
    const int dataLength = 8;                   // 共读取 8 个寄存器
    std::vector<uint16_t> data;

    for (int attempt = 1; attempt <= maxRetries; ++attempt)
    {
        ret = api.ReadRegister_03(slave_id, registerAddress, dataLength, data);

        if (ret)
        {
            if (data.size() >= 8)
            {
                status         = data[0];
                external_width = data[1];
                internal_width = data[2];
                force          = data[7];  // 第 8 个寄存器为抓力值
            }
            break;
        }
        else
        {
            LOG(WARNING) << "ReadRegister_03 failed. Retry " << attempt << "/" << maxRetries;
            if (attempt < maxRetries)
                usleep(retryDelayUs);
        }
    }

    return ret;
}
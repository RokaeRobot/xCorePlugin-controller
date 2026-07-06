/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file rl_cmd.hpp
 * @brief 指令注册例子
 */
#include "rl_cmd/morden_rl_cmd_api.hpp"


namespace _printq_ {
using namespace xcore_api::rl_cmd;

/**
 * @brief 指令注册函数
 */
void RegPrintq();

}

namespace _async_cmd_ {
using namespace xcore_api::rl_cmd;

/**
 * @brief 异步等待指令：参数 int n，异步暂停 n 秒后结束
 */
void RegAsyncWait();

/**
 * @brief 启动后台线程，每秒打印日志
 */
void RegStartLogThread();

/**
 * @brief 参数 int n，使上一个日志线程在 n 秒后结束
 */
void RegStopLogThread();

}

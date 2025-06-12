/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file thread_pool_api.hpp
 * @brief 线程池的使用接口
 */
#pragma once
#include <functional>
#include <future>

namespace xcore_api{
namespace utils{

/**
 * @brief 在线程池里面执行函数，不关心返回值
 * @param func 要执行的函数逻辑
 * @return std::future<void> 
 */
std::future<void> RunInThreadPoolAPI(const std::function<void()> &func);

/**
 * @brief 在线程池里面执行函数，返回值为int类型
 * @param func 要执行的函数逻辑
 * @return std::future<int> 通过future.get获取返回值
 */
std::future<int> RunInThreadPoolIntAPI(const std::function<int()> &func);

}
}


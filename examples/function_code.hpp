/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file function_code.hpp
 * @brief 寄存器功能码拓展例子
 */
#pragma once
#include "registers/function_code_api.hpp"

namespace xreg = xcore_api::registers;

/**
 * @brief 声明两个寄存器功能码类
*/
DECLARE_FUNCTION_CODE_API(PluginReadReg);

DECLARE_FUNCTION_CODE_API(PluginWriteReg);


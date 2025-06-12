/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file authorize.cpp
 * @brief 插件开发者自行决定该插件是否需要授权方可使用
 * @note 如需授权开发者联系珞石获取每台机器授权码
 */

#define EXPORT extern "C" __attribute__((visibility("default")))

/**
 * @brief 默认不需要授权
 * @note 变量名固定
 */
 EXPORT const bool plugin_need_authorize = false;


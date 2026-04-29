/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file ecat_api.hpp
 * @brief 定义ethercat常用的PDO SDO数据
 */

#pragma once
#include <string.h>
#include <vector>
#include <functional>
#include <string>

namespace xcore_api {
namespace const_data {
namespace ecat {

/**
 * @brief 回调函数
 */
typedef std::function< void()>  ThreadFunc;

/**
 * @brief Ethercat的PDO数据类型定义
 */
struct PdoAPI {
    PdoAPI() :
        baseIndex(0),
        byteOffs(0),
        byteSize(0) {}
    PdoAPI(uint16_t byte_offs, uint16_t byte_size) :
        baseIndex(0),
        byteOffs(byte_offs),
        byteSize(byte_size) {}
    uint16_t    baseIndex; ///<  数据index
    uint16_t    byteOffs; ///<  数据偏移
    uint16_t    byteSize; ///<  数据大小
    std::string name; ///<  PDO数据名
};

/**
 * @brief Ethercat的SDO数据类型定义
 */
struct SdoAPI {
    SdoAPI() :
        index(0),
        subIndex(0),
        dateLen(0),
        timeOut(4000),
        flags(0) {}
    uint16_t    index;  ///< 索引
    uint8_t     subIndex; ///< 子索引
    uint32_t    dateLen; ///< 数据长度
    uint32_t    timeOut; ///< 超时时间
    uint32_t    flags; ///< 标志位
    ThreadFunc m_msg_callback; ///< 回调函数
};

}
}
}

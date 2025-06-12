/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file ecat_base_api.hpp
 * @brief 操作ethercat pdo sdo的接口
 */
#pragma once
#include <stdint.h>
#include "const_data/ecat_api.hpp"

namespace xcore_api{
namespace ecat{
namespace xecat = ::xcore_api::const_data::ecat;

class EcatBaseAPI
{
public:
    EcatBaseAPI(uint16_t slave_id);

    virtual ~EcatBaseAPI() = default;

    /**
     * @brief  从站获取PDO数据
     * @param  obj  pdo对象
     * @param  value  获取的pdo值，
     * @param  bOutputData true  read output data,  true  read input data
     * @note 传入的value空间要足够大，能够容纳相应的值
     * @return 成功返回0，失败返回相应的错误码
     */
    int GetPdoValue(const xecat::PdoAPI& obj, void* value, bool bOutputData = false);

    /**
     * @brief  设置Pdo的值
     * @param   obj  pdo对象
     * @param   value  数据指针
     * @return 0 表示成功，其他表示失败
     */
    int SetPdoValue(const xecat::PdoAPI& obj, void* value);

    /**
     * @brief   设置sdo的值
     * @param   sdo  sdo对象
     * @param   value  传入的数据指针
     * @return 0 表示成功，其他表示失败
     */
    int SetSdoValue(xecat::SdoAPI& sdo, void* value);

    /**
     * @brief   设置Sdo值
     * @param   sdo  sdo 对象
     * @param   value  数据指针
     * @return 0表示成功，其他失败
     */
    int GetSdoValue(xecat::SdoAPI& sdo, void* value);

protected:
    /**
     * @brief 初始化ethercat
     * @return true 成功
     * @return false 失败
     */
    bool InitEcat();

    /**
     * @brief 注册pdo数据到对应的偏移上
     * @param pdo pdo数据 
     * @param baseIndex 基地址
     * @param byteoffs 字节偏移
     * @param byteLen 数据长度
     * @return int 0 成功，其他失败
     */
    int RegisterPdo(xecat::PdoAPI& pdo, uint16_t baseIndex, uint16_t byteoffs, uint16_t byteLen);

    /**
     * @brief 注册sdo数据 
     * @param sdo 
     * @param index 地址
     * @param subIndex 子地址
     * @param dateLen 数据长度
     * @param timeOut 超时时间
     * @param func 回调函数
     * @return int 0成功其他值失败
     */
    int RegisterSdo(xecat::SdoAPI& sdo, uint16_t index, uint16_t subIndex, uint16_t dateLen, uint16_t timeOut, const xecat::ThreadFunc& func);

    uint16_t m_slave_id;
};



}
}


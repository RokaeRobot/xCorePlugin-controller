/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file entool_api.hpp
 * @brief 使用末端协议透传控制电爪等
 */

#pragma once
#include <vector>
#include <stdint.h>

namespace xcore_api {
namespace endtool {

/**
 * @brief modbus rtu协议控制末端工具
 */
class ModbusRTUEndtoolAPI {
public:
    virtual ~ModbusRTUEndtoolAPI();
    ModbusRTUEndtoolAPI();

public:
    /**
     * @brief modbus rtu协议，直接透传数据
     * @param send_len 发送数据长度
     * @param send_data 发送数据
     * @param rev_len 接收数据长度
     * @param rev_data 接收数据
     * @param ret_status 返回状态
     * @return true 成功
     * @return false 失败
     */
    bool RWData(const int& send_len, const std::vector<uint8_t>& send_data,
               const int& rev_len, std::vector<uint8_t>& rev_data, int& ret_status);

    /**
     * @brief modbus rtu协议读线圈，功能号01
     * @param slave_id 从设备id
     * @param addr 寄存器地址
     * @param len 数据长度
     * @param data 具体数据
     * @param crc_inverse 是否反转crc 
     * @return true 成功
     * @return false 失败
     */
    bool ReadCoil_01(const int& slave_id, const uint16_t& addr,
                    const int& len, std::vector<bool>& data, bool crc_inverse = false);
    /**
     * @brief modbus rtu协议读离散输入，功能号02
     * @param slave_id 从设备id
     * @param addr 寄存器地址
     * @param len 数据长度
     * @param data 具体数据
     * @param crc_inverse 是否反转crc
     * @return true 成功
     * @return false 失败
     */
    bool ReadDiscreteInput_02(const int& slave_id, const uint16_t& addr,
                            const int& len, std::vector<bool>& data, bool crc_inverse = false);
     /**
     * @brief modbus rtu协议读保持寄存器，功能号03
     * @param slave_id 从设备id
     * @param addr 寄存器地址
     * @param len 数据长度
     * @param data 具体数据
     * @param crc_inverse 是否反转crc
     * @return true 成功
     * @return false 失败
     */
    bool ReadRegister_03(const int& slave_id, const uint16_t& addr,
                        const uint16_t& len, std::vector<uint16_t>& data, bool crc_inverse = false);
     /**
     * @brief modbus rtu协议读输入寄存器，功能号04
     * @param slave_id 从设备id
     * @param addr 寄存器地址
     * @param len 数据长度
     * @param data 具体数据
     * @param crc_inverse 是否反转crc
     * @return true 成功
     * @return false 失败
     */
    bool ReadRegister_04(const int& slave_id, const uint16_t& addr,
                        const uint16_t& len, std::vector<uint16_t>& data, bool crc_inverse = false);

     /**
     * @brief modbus rtu协议写单个线圈，功能号05
     * @param slave_id 从设备id
     * @param addr 寄存器地址
     * @param len 数据长度
     * @param data 具体数据
     * @param crc_inverse 是否反转crc
     * @return true 成功
     * @return false 失败
     */
    bool WriteCoil_05(const int& slave_id, const uint16_t& addr,
                     const int& len, std::vector<bool>& data, bool crc_inverse = false);
    
     /**
     * @brief modbus rtu协议写单个寄存器，功能号06
     * @param slave_id 从设备id
     * @param addr 寄存器地址
     * @param len 数据长度
     * @param data 具体数据
     * @param crc_inverse 是否反转crc
     * @return true 成功
     * @return false 失败
     */                 
    bool WriteRegister_06(const int& slave_id, const uint16_t& addr,
                         const uint16_t& len, const std::vector<uint16_t>& data, bool crc_inverse = false);
     /**
     * @brief modbus rtu协议写多个线圈，功能号15
     * @param slave_id 从设备id
     * @param addr 寄存器地址
     * @param len 数据长度
     * @param data 具体数据
     * @param crc_inverse 是否反转crc
     * @return true 成功
     * @return false 失败
     */
    bool WriteCoil_0F(const int& slave_id, const uint16_t& addr,
                     const int& len, std::vector<bool>& data, bool crc_inverse = false);
     /**
     * @brief modbus rtu协议写多个寄存器，功能号16
     * @param slave_id 从设备id
     * @param addr 寄存器地址
     * @param len 数据长度
     * @param data 具体数据
     * @param crc_inverse 是否反转crc
     * @return true 成功
     * @return false 失败
     */
    bool WriteRegister_10(const int& slave_id, const uint16_t& addr,
                         const uint16_t& len, const std::vector<uint16_t>& data, bool crc_inverse = false);

};

}
}
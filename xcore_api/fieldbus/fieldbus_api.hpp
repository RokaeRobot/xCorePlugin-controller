/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file fieldbus_api.hpp
 * @brief 现场总线如modbus/profinet/EIP/cclink接口
 */
#pragma once
#include <mutex>
#include <map>
#include <memory>

namespace xcore_api{
namespace fieldbus {

/**
 * @brief 支持的总线设备类型
 */
enum DeviceTypeAPI {
    MODBUS_TCP_MASTER,
    MODBUS_TCP_SLAVER,
    MODBUS_RTU_MASTER,
    MODBUS_RTU_SLAVER,
    PROFINET_SLAVER,
    EIP_SLAVER,
    CCLINK_IE_SLAVER,
    CCLINK_ECAT_SLAVER
};

/**
 * @brief 设置数据读取大小端模式
 */
enum EndianAPI {
    ABCD, ///< 大端序
    CDAB, ///< 字节大端序,字小端序
    BADC, ///< 字节小端,字大端 
    DCBA ///< 字节和字都是小端
};

class FieldbusImpl;
 /**
 * @brief 总线设备的基类配置
 */
class FieldbusCfgAPI{
public:
    FieldbusCfgAPI(DeviceTypeAPI type);
    FieldbusCfgAPI();
    virtual ~FieldbusCfgAPI();
public:
    /**
     * @brief   重置设备类型
     * @param type  总线设备类型
     */
    void Reset(DeviceTypeAPI type);

     /**
     * @brief       设置设备名称
     * @param value  设备名
     * @return 0正常，其他异常
     */
    int SetName(const std::string& value);

    /**
     * @brief       获取设备名称
     * @return  具体设备名,默认为空
     */
    std::string GetName();
    
    /**
     * @brief       设置大小端序列
     * @param   endian    具体大小端信息
     * @return  0正常，其他异常
     */
    int SetEndian(EndianAPI endian);

    /**
     * @brief    获取设置大小端序列
     * @return  具体大小端信息
     */
    EndianAPI GetEndian();
protected:
    std::shared_ptr<FieldbusImpl> pimpl;
    friend class FieldbusAPI;
};

/**
 * @brief modbus具体配置数据
 */
class ModbusCfgAPI:public FieldbusCfgAPI{
public:
    ModbusCfgAPI(DeviceTypeAPI type);
    virtual ~ModbusCfgAPI();
public:
    /**
     * @brief   设置ip,modbus tcp类型有效
     * @param   value    具体ip数据
     */
    void SetIp(const std::string& value);

    /**
     * @brief   获取设置ip
     * @return  具体ip数据
     */
    const std::string GetIp() const;

    /**
     * @brief   设置端口,modbus tcp类型有效
     * @param   value    具体端口
     */
    void SetPort(const uint32_t& value);

    /**
     * @brief   获取端口，modbus tcp类型有效
     * @return  具体端口数据
     */
    const uint32_t GetPort() const;

     /**
     * @brief   设置串口数据,modbus rtu类型有效
     * @param   value    具体数据
     */
    void SetSerialName(const std::string& value);

    /**
     * @brief   获取串口名，modbus rtu类型有效
     * @return  具体端口名
     */
    const std::string GetSerialName() const;

     /**
     * @brief   设置从站id
     * @param   value    具体数据
     */
    void SetSlaverId(const uint32_t& value);

    /**
     * @brief   获取从站id
     * @return  具体从站id
     */
    const uint32_t GetSlaverId() const;

    /**
     * @brief   设置保持寄存器起始地址
     * @param   value   起始地址
     */
    void SetHoldRegStartAddr(const uint32_t& value);

    /**
     * @brief   获取保持寄存器起始地址
     * @return  起始地址值
     */
    const uint32_t GetHoldRegStartAddr() const;

    /**
     * @brief   设置保持寄存器数量
     * @param   value    具体数目
     */
    void SetHoldRegNum(const uint32_t& value);

    /**
     * @brief   获取保持寄存器数量
     * @return  保持寄存器数量
     */
    const uint32_t GetHoldRegNum() const;

     /**
     * @brief   设置输入寄存器起始地址
     * @param   value    起始地址
     */
    void SetInputRegStartAddr(const uint32_t& value);

    /**
     * @brief   获取输入寄存器起始地址
     * @return  起始地址
     */
    const uint32_t GetInputRegStartAddr() const;

    /**
     * @brief   设置输入寄存器数量
     * @param   value    具体数量
     */
    void SetInputRegNum(const uint32_t& value);

    /**
     * @brief   获取输入寄存器数量
     * @return  输入寄存器总数
     */
    const uint32_t GetInputRegNum() const;

    /**
     * @brief   设置线圈起始地址
     * @param   value    起始地址
     */
    void SetCoilsStartAddr(const uint32_t& value);

    /**
     * @brief   获取线圈起始地址
     * @return  起始地址
     */
    const uint32_t GetCoilsStartAddr() const;

    /**
     * @brief   设置线圈数量
     * @param   value    具体数量
     */
    void SetCoilsNum(const uint32_t& value);

    /**
     * @brief   获取线圈数量
     * @return  具体数量
     */
    const uint32_t GetCoilsNum() const;

    /**
     * @brief   设置离散输入起始地址
     * @param   value    起始地址
     */
    void SetDiscInputStartAddr(const uint32_t& value);

    /**
     * @brief   获取离散输入起始地址
     * @return  起始地址值
     */
    const uint32_t GetDiscInputStartAddr() const;

    /**
     * @brief   设置离散输入数量
     * @param   value    具体数量
     */
    void SetDiscInputNum(const uint32_t& value);

    /**
     * @brief   获取离散输入数量
     * @return  具体数量
     */
    const uint32_t GetDiscInputNum() const;
};


/**
 * @brief profinet具体配置数据
 */
class ProfinetCfgAPI : public FieldbusCfgAPI {
public:
    ProfinetCfgAPI(DeviceTypeAPI type);
    virtual ~ProfinetCfgAPI();
public:
    /**
     * @brief   设置站点名称
     * @param   value    名字
     */
    void SetStationName(const std::string& value);

    /**
     * @brief   获取站点名称
     * @return  具体名字
     */
    const std::string GetStationName() const;

    /**
     * @brief   设置网卡值
     * @param   value    网卡值
     */
    void SetNetcard(const std::string& value);

    /**
     * @brief   获取网卡值
     * @return  具体值
     */
    const std::string GetNetcard() const;

    /**
     * @brief   设置更新周期
     * @param   value    周期值
     */
    void SetUpdateDataInternal(const uint32_t& value);

    /**
     * @brief   获取更新周期
     * @return  具体周期值
     */
    const uint32_t GetUpdateDataInternal() const;

    /**
     * @brief   设置槽1的id
     * @param   value    具体id
     */
    void SetSlot1ModuleID(const uint32_t& value);

    /**
     * @brief   获取槽1的id
     * @return  具体id
     */
    const uint32_t GetSlot1ModuleID() const ;

    /**
     * @brief   设置槽2的id
     * @param   value    具体id
     */
    void SetSlot2ModuleID(const uint32_t& value);
    
    /**
     * @brief   获取槽2的id
     * @return  具体id
     */
    const uint32_t GetSlot2ModuleID() const ;
   
    /**
     * @brief   设置槽3的id
     * @param   value    具体id
     */
    void SetSlot3MmoduleID(const uint32_t& value);

    /**
     * @brief   获取槽3的id
     * @return  具体id
     */
    const uint32_t GetSlot3ModuleID() const ;
    
    /**
     * @brief   设置槽4的id
     * @param   value    具体id
     */
    void SetSlot4ModuleID(const uint32_t& value);
    
    /**
     * @brief   获取槽4的id
     * @return  具体id
     */
    const uint32_t GetSlot4ModuleID() const ;
    
    /**
     * @brief   设置槽5的id
     * @param   value    具体id
     */
    void SetSlot5ModuleID(const uint32_t& value);
    
    /**
     * @brief   获取槽5的id
     * @return  具体id
     */
    const uint32_t GetSlot5ModuleID() const ;
    
    /**
     * @brief   设置槽6的id
     * @param   value    具体id
     */
    void SetSlot6ModuleID(const uint32_t& value);
    
    /**
     * @brief   获取槽6的id
     * @return  具体id
     */
    const uint32_t GetSlot6ModuleID() const ;

};

/**
 * @brief EIP具体配置数据
 */
class EipCfgAPI : public FieldbusCfgAPI {
public:
    EipCfgAPI(DeviceTypeAPI type);
    virtual ~EipCfgAPI();
public:
    /**
     * @brief   设置读寄存器数量
     * @param   value    具体数量
     */
    void SetReadRegNum(const uint16_t& value);
    
    /**
     * @brief   获取读寄存器数量
     * @return  具体数量
     */
    const uint16_t GetReadRegNum() const;
    
    /**
     * @brief   设置写寄存器的数量
     * @param   value    具体数量
     */
    void SetWriteRegNum(const uint16_t& value);
    
    /**
     * @brief   获取写寄存器数量
     * @return  具体数量
     */
    const uint16_t GetWriteRegNum() const;
    
    /**
     * @brief   设置网卡
     * @param   value    具体数值
     */
    void SetNetCard(const std::string& value);
    
    /**
     * @brief   获取网卡
     * @return  具体数据
     */
    const std::string GetNetCard() const;

};

/**
 * @brief cclink具体配置数据
 */
class CCLinkCfgAPI : public FieldbusCfgAPI {
public:
    CCLinkCfgAPI(DeviceTypeAPI type);
    virtual ~CCLinkCfgAPI();
public:
    /**
     * @brief   设置协议类型
     * @param   value    具体类型
     */
    void SetProtoType(const std::string&  value);

    /**
     * @brief   获取协议类型
     * @return  具体类型
     */
    const std::string GetProtoType() const;

    /**
     * @brief   设置网卡
     * @param   value    具体数据
     */
    void SetNetCard(const std::string&  value);

    /**
     * @brief   获取网卡
     * @return  具体数据
     */
    const std::string GetNetCard() const;

    /**
     * @brief   设置占用站个数
     * @param   value    具体数量
     */
    void SetOccupiedStaNum(const uint32_t&  value);

    /**
     * @brief   获取占用站个数
     * @return  具体个数
     */
    const uint32_t GetOccupiedStationNum() const;

    /**
     * @brief   设置波特率
     * @param   value    具体数据
     */
    void    SetBaudRate(const uint32_t&  value);

    /**
     * @brief   获取波特率
     * @return  具体数据
     */
    const uint32_t GetBaudRate() const;

    /**
     * @brief   设置协议版本
     * @param   value    具体数据
     */
    void SetProtoVersion(const uint32_t& value);

    /**
     * @brief   获取协议版本
     * @return  具体数据
     */
    const uint32_t GetProtoVersion() const;
};

/**
 * @brief modbus具体配置数据
 */
class FieldbusAPI {
public:
    FieldbusAPI(const FieldbusCfgAPI &cfg);
    virtual ~FieldbusAPI();
public:
    /**
     * @brief   打开设备
     * @return  0正常，其他异常
     */
    int Open();

    /**
     * @brief   关闭设备
     * @return  0正常，其他异常
     */
    int Close();

    /**
     * @brief   读取寄存器数据
     * @param addr 寄存器地址
     * @param dest 存放数据
     * @param nb 数组索引
     * @return  0正常，其他异常
     */
    int ReadRegisters(uint32_t addr, uint16_t *dest, const uint32_t& nb = 1) ;

    /**
     * @brief   写入寄存器数据
     * @param addr 寄存器地址
     * @param dest 原数据
     * @param nb 数组索引
     * @return  0正常，其他异常
     */
    int WriteRegisters(uint32_t addr, const uint16_t *src, const uint32_t& nb = 1);

    /**
     * @brief   获取输入数量
     * @return  具体值
     */
    int GetDINum();

    /**
     * @brief   获取输出数量
     * @return  具体值
     */
    int GetDONum();

    /**
     * @brief   设置DO值
     * @param index 索引
     * @param value 数据值
     * @return  0正常，其他异常
     */
    int SetDO(const uint32_t& index, const bool& value);

    /**
     * @brief   获取DI值
     * @param index 索引
     * @param value 输出值
     * @return  0正常，其他异常
     */
    int GetDI(const uint32_t& index, bool& value);

private:
    std::shared_ptr<FieldbusImpl> pimpl;
};



} 
} 

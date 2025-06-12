/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file analog_api.hpp
 * @brief 模拟量相关接口定义
 */
#pragma once
#include <stdint.h>
#include <string>

namespace xcore_api{
namespace io{

/**
 * @brief 模拟量相关操作，包括AI/AO/寄存器
 */
class Analog
{
public:
    /**
    * @brief 获取模拟量的实例
    * @return 模拟量对象指针
    */
    static Analog* getInstance() {
        static Analog instance;
        return &instance;
    }

    virtual ~Analog() = default;

    /**
    * @brief 获取AI信号值
    * @param signal_name  信号名称
    * @param value 输出，AI信号值
    * @return true 成功
    * @return false 失败，signal不存在   
    */
    bool GetAIValue(const std::string& signal_name, double& value);

    /**
     * @brief 获取AO信号值
     * @param signal_name 信号名称
     * @param value 输出，AO信号值
     * @return true 成功
     * @return false 失败，signal不存在   
     */
    bool GetAOValue(const std::string& signal_name, double& value);

    /**
     * @brief 设置AO信号值，修改控制系统内部的信号值
     * @param signal_name 信号名称
     * @param value 输入AO信号值
     * @return true 成功
     * @return false 失败，signal不存在   
     */
    bool SetAOValue(const std::string& signal_name, const double value);

    /**
    * @brief 获取DI信号值
    * @param signal_name 信号名称
    * @param value 输出，DI信号值
    * @return true 成功
    * @return false 失败，signal不存在   
    */
    bool GetDIValue(const std::string& signal_name, bool& value);

    /**
     * @brief 获取DO信号值
     * @param signal_name 信号名称
     * @param value 输出，DO信号值
     * @return true 成功
     * @return false 失败，signal不存在   
     */
    bool GetDOValue(const std::string& signal_name, bool& value);

    /**
     * @brief 设置DO信号值，修改控制系统内部的DO信号值
     * @param signal_name 信号名称
     * @param value 输入，DI信号值
     * @return true 成功
     * @return false 失败，signal不存在   
     */
    bool SetDOValue(const std::string& signal_name, const bool value);

    /**
     * @brief 获取GI信号值
     * @param signal_name 信号名称
     * @param value 输出，GI信号值
     * @return true 成功
     * @return false 失败，signal不存在   
     */
    bool GetGIValue(const std::string& signal_name, unsigned int& value);

    /**
     * @brief 获取GO信号值
     * @param signal_name 信号名称
     * @param value 输出，GO信号值
     * @return true 成功
     * @return false 失败，signal不存在   
     */
    bool GetGOValue(const std::string& signal_name, unsigned int& value);

    /**
     * @brief 设置GO信号值，修改控制系统内部的I信号值
     * @param signal_name 信号名称
     * @param value 输入GO信号值
     * @return true 成功
     * @return false 失败，signal不存在或者GO信号超出GO限制
     */
    bool SetGOValue(const std::string& signal_name, const unsigned int value);

    /**
    * @brief 设置int16寄存器值
    * @param name 寄存器名称
    * @param value 写入寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码  
    */
    int WriteInt16Register(const std::string& name, const int16_t& value, int bias);

    /**
    * @brief 设置bool寄存器值
    * @param name 寄存器名称
    * @param value 写入寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int WriteBoolRegister(const std::string& name, const bool& value, int bias);

    /**
    * @brief 设置float寄存器值
    * @param name 寄存器名称
    * @param value 写入寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int WriteFloatRegister(const std::string& name, const float& value, int bias);

    /**
    * @brief 设置bit寄存器值
    * @param name 寄存器名称
    * @param value 写入寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int WriteBitRegister(const std::string& name, const bool& value, int bias);

    /**
    * @brief 设置int32寄存器值
    * @param name 寄存器名称
    * @param value 写入寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int WriteInt32Register(const std::string& name, const int32_t& value, int bias);

    /**
    * @brief 设置byte寄存器值
    * @param name 寄存器名称
    * @param value 写入寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int WriteByteRegister(const std::string& name, const uint8_t& value, int bias);

    /**
    * @brief 读取int16寄存器值
    * @param name 寄存器名称
    * @param value 读取寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int ReadInt16Register(const std::string& name, int16_t& value, int bias);

    /**
    * @brief 读取bool寄存器值
    * @param name 寄存器名称
    * @param value 读取寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int ReadBoolRegister(const std::string& name, bool& value, int bias);

    /**
    * @brief 读取float寄存器值
    * @param name 寄存器名称
    * @param value 读取寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int ReadFloatRegister(const std::string& name, float& value, int bias);

    /**
    * @brief 读取bit寄存器值
    * @param name 寄存器名称
    * @param value 读取寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int ReadBitRegister(const std::string& name, bool& value, int bias);

    /**
    * @brief 读取int32寄存器值
    * @param name 寄存器名称
    * @param value 读取寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int ReadInt32Register(const std::string& name, int32_t& value, int bias);

    /**
    * @brief 读取byte寄存器值
    * @param name 寄存器名称
    * @param value 读取寄存器值
    * @param bias 偏置
    * @return 0无错误，其他具体错误码 
    */
    int ReadByteRegister(const std::string& name, uint8_t& value, int bias);

    /**
    * @brief 按名称检索AI端口是否存在
    * @param name 端口名称
    * @return true 端口存在; 
    * @return false 端口不存在
    */
    bool IsAiExist(const std::string& signal_name);

    /**
    * @brief 按名称检索AO端口是否存在
    * @param name 端口名称
    * @return true 端口存在;
    * @return false 端口不存在
    */
    bool IsAoExist(const std::string& signal_name);

    /**
    * @brief 按名称检索DI端口是否存在
    * @param name 端口名称
    * @return true 端口存在; 
    * @return false 端口不存在
    */
    bool IsDiExist(const std::string& signal_name);

    /**
    * @brief 按名称检索DO端口是否存在
    * @param name 端口名称
    * @return true 端口存在;
    * @return false 端口不存在
    */
    bool IsDoExist(const std::string& signal_name);

    /**
    * @brief 按名称检索GI端口是否存在
    * @param name 端口名称
    * @return true 端口存在
    * @return false 端口不存在
    */
    bool IsGiExist(const std::string& signal_name);

    /**
    * @brief 按名称检索GO端口是否存在
    * @param name 端口名称
    * @return true 端口存在; 
    * @return false 端口不存在
    */
    bool IsGoExist(const std::string& signal_name);

    /**
    * @brief 按名称获取寄存器类型
    * @param name 端口名称
    * @param type 寄存器类型: int16,bool,float,bit,int32,byte
    * @return true 寄存器存在;
    * @return false 寄存器不存在
    */
    bool RegisterType(const std::string& register_name, std::string& type);

    /**
    * @brief 按名称获取寄存器是否可写
    * @param name 端口名称
    * @param writeable 寄存器是否可读: 
    * @return true 寄存器存在; 
    * @return false 寄存器不存在
    */
    bool RegisterWriteable(const std::string& register_name, bool& writeable);

    /**
    * @brief 指定名称寄存器类型是否满足作为指定类型IO替代使用
    * @param register_name 寄存器名称
    * @param io_type IO类型:
    * @return true 寄存器类型满足作为指定类型IO替代使用; 
    * @return false 寄存器类型不满足作为指定类型IO替代使用
    */
    bool CheckRegisterCanUsedAsIO(const std::string& register_name, const std::string& io_type);

protected:
    /**
     * @brief 构造函数
     */
    Analog();
    /**
     * @brief 
     * @return true 初始化成功 
     * @return false 初始化失败
     */
    bool InitIO();
};

}
}
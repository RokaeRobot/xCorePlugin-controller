/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file function_code_api.hpp
 * @brief 寄存器功能码相应的接口
 */
#pragma once
#include <stdint.h>
#include <vector>
#include <string>
#include <memory>

namespace xcore_api{
namespace registers{

/**
 * @brief 寄存器数据类型
*/
enum RegTypeAPI{
    BIT,
    BOOL,
    BYTE,
    INT16,
    INT32,
    FLOAT
};
class FuncCodeCfgImpl;

/**
 * @brief 寄存器功能码配置
 */
class FuncCodeCfgAPI{
public:
    FuncCodeCfgAPI();
    virtual ~FuncCodeCfgAPI();
public:
    /**
     * @brief 设置功能码的名字
     * @param name名字
     * @return true成功，false失败
     */
    bool SetName(const std::string &name);

    /**
     * @brief 获取功能码名字
     * @return 名字
     */
    std::string GetName();

    /**
     * @brief 设置寄存器支持的类型
     * @param v 支持的寄存器类型集合
     * @return true成功，false失败
     */
    bool SetSupportType(const std::vector<RegTypeAPI> &v);

    /**
     * @brief 获取寄存器支持的类型
     * @return 支持的寄存器类型集合
     */
    std::vector<RegTypeAPI> GetSupportType();

    /**
     * @brief 设置寄存器长度
     * @param len 长度
     * @return true成功，false失败
     */
    bool SetLen(uint32_t len);

    /**
     * @brief 获取寄存器长度
     * @return 长度
     */
    uint32_t GetLen();

    /**
     * @brief 设置寄存器读写类型
     * param writeable true写类型。false读类型
     * @return true成功，false失败
     */
    bool SetWriteable(bool writeable);
    /**
     * @brief 获取寄存器读写类型
     * @return true写类型，false读类型
     */
    bool IsWriteable();
private:
    friend class FuncCodeAPI;
    std::shared_ptr<FuncCodeCfgImpl> pimpl;
};

/**
 * @brief 寄存器功能码基类
 */
class FuncCodeAPI{
public:
    FuncCodeAPI(const FuncCodeCfgAPI &cfg);
    virtual ~FuncCodeAPI();
public:
    /**
     * @brief 功能码执行逻辑
     */
    virtual bool ExecFuncCode() = 0;

    /**
     * @brief 克隆实现
     */
    virtual  std::shared_ptr<FuncCodeAPI> Clone() = 0;

    /**
     * @brief 获取配置
     * @return 寄存器功能码配置
     */
    FuncCodeCfgAPI GetCfg();

    /**
     * @brief 读取int类型寄存器
     * @param v 读取到的数据
     * @return 0正常，其他异常
     */
    int ReadIntRegValue(std::vector<int> &v);

    /**
     * @brief 读取float类型寄存器
     * @param v 读取到的数据
     * @return 0正常，其他异常
     */
    int ReadFloatRegValue(std::vector<float> &v);

    /**
     * @brief 写int数据到寄存器中
     * @param v 要写的数据
     * @return 0正常，其他异常
     */
    int WriteIntRegValue(const std::vector<int> &v);

    /**
     * @brief 写float数据到寄存器中
     * @param v 要写入的数据
     * @return 0正常，其他异常
     */
    int WriteFloatRegValue(const std::vector<float> &v);
private:
    friend class FuncCodeImpl;
    std::shared_ptr<FuncCodeCfgImpl> pimpl;
};

namespace xreg = xcore_api::registers;

/**
* @brief 使用此宏快速声明寄存器功能码
*/
#define DECLARE_FUNCTION_CODE_API(_type_name_)\
class _type_name_ : public xreg::FuncCodeAPI{\
public:\
    _type_name_(const xreg::FuncCodeCfgAPI &cfg):xreg::FuncCodeAPI(cfg){}\
    virtual std::shared_ptr<xreg::FuncCodeAPI> Clone(){\
        return std::make_shared<_type_name_>(this->GetCfg());\
    }\
    virtual bool ExecFuncCode() override;\
};

#define FUNCTION_CODE_EXECUTE_API(_type_name_)\
bool _type_name_::ExecFuncCode()


/**
* @brief 将寄存器功能码注册到控制器中
*/
bool RegFuncCodeAPI(std::shared_ptr<FuncCodeAPI> ptr);


}
}
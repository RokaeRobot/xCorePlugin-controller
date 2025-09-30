/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file function_code.cpp
 * @brief 寄存器功能码使用例子
 */
#include "log/log_api.hpp"
#include "function_code.hpp"

/**
 * @brief 实现功能码类
*/
FUNCTION_CODE_EXECUTE_API(PluginReadReg){
    std::vector<int> v;
    ReadIntRegValue(v);
    std::string str;
    for(auto &item:v){
        str += std::to_string(item) + ",";
    }
    LOG_INFO<<"PluginReadReg:"<<str;
    return true;
}

/**
 * @brief 创建功能码实例
*/
std::shared_ptr<xreg::FuncCodeAPI> makeReadRegCmd(){
    xreg::FuncCodeCfgAPI cfg;
    cfg.SetName("plugin_read_reg_cmd");
    cfg.SetSupportType({xreg::RegTypeAPI::BIT,xreg::RegTypeAPI::BOOL,xreg::RegTypeAPI::BYTE,xreg::RegTypeAPI::INT16,xreg::RegTypeAPI::INT32});
    cfg.SetLen(1);
    cfg.SetWriteable(false);
    return std::make_shared<PluginReadReg>(cfg);
}


FUNCTION_CODE_EXECUTE_API(PluginWriteReg){
    std::vector<float> v{0.123,0.132,0.213,0.231,0.312,0.321};
    static int i = 0;
    static int j = 0;
    ++i;
    if(i %3000 == 0){
        ++j;
    }
    for(auto &item:v){
        item += j;
    }
    WriteFloatRegValue(v);
    LOG_EVERY_N(PINFO,2000)<<"PluginWriteReg:"<<i;
    return true;
}

std::shared_ptr<xreg::FuncCodeAPI> makeWriteRegCmd(){
    xreg::FuncCodeCfgAPI cfg;
    cfg.SetName("plugin_write_reg_cmd");
    cfg.SetSupportType({xreg::RegTypeAPI::FLOAT});
    cfg.SetLen(10);
    cfg.SetWriteable(true);
    return std::make_shared<PluginWriteReg>(cfg);
}

/**
 * @brief 功能码入口函数
*/
void FunctionCodeExample(){
    //注册到控制系统中
    xreg::RegFuncCodeAPI(makeReadRegCmd());
    xreg::RegFuncCodeAPI(makeWriteRegCmd());
}

/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file hooks_args_api.hpp
 * @brief 具体的hooks对应的事件触发实现
 */

#pragma once

#include <memory>
#include <string>

namespace xcore_api{
namespace hooks{

/**
 * @brief 所有hooks参数的基类 
 */
class HookArgsBaseAPI{
public:
    HookArgsBaseAPI(){};
    virtual ~HookArgsBaseAPI(){};
};


/**
 * @brief 增删改查信息
 */
enum CURDAPI{
    CREATE,
    UPDATE,
    READ,
    DELETE
};
//前向声明
class HookPointArgsImpl;

/**
 * @brief 点位回调参数的具体实现
 */
class HookPointArgsAPI:public HookArgsBaseAPI{
public:

    /**
     * @brief 获取点位名称
     * @return 点位名 
     */
    const std::string GetPointName() const;

    /**
     * @brief 设置点位名称
     * @param name 点位名
     * @return true 成功
     * @return false 失败
     */
    bool SetPointName(const std::string &name);

    /**
     * @brief 获取当前参数的操作，增/删/改
     * @return 具体操作
     */
    const CURDAPI GetOperate() const ;

    /**
     * @brief 设置参数具体操作类型
     * @param operate 增/删/改
     * @return true 成功
     * @return false 失败
     */
    bool SetOperate(const CURDAPI &operate);
public:
    HookPointArgsAPI();
    ~HookPointArgsAPI();
private:
    std::shared_ptr<HookPointArgsImpl> pimpl;
};

}
}
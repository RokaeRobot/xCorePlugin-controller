/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file states_api.hpp
 * @brief 控制器状态的查询接口
 */
#pragma once
#include <memory>

namespace xcore_api{
namespace states{

/**
 * @brief 用户空间，用于判断机器人是否属于自己控制
 */
enum TaskSpaceAPI : unsigned short {
    TS_READY,
    TS_BUSY
};
/**
 * @brief 当前机器人处于哪个调用阶段
 */
enum RunningStateAPI : int {
    RS_NONE = 0,
    RS_START, ///< 开始
    RS_PAUSE, ///< 暂停
    RS_STEP, ///< 单步
    RS_BACK,  ///< 上一步
    RS_ERROR_HANDLER, ///< 错误处理
    RS_RESET,
    RS_COLLISION, ///< 碰撞
    RS_STOP_EVENT, ///< 急停
    RS_NUM_NEVER_USE,
};

//前向声明
class StatesImpl;
/**
 * @brief 状态获取接口
 */
class StatesAPI{
public:
    StatesAPI();
    virtual ~StatesAPI();
public:
    /**
     * @brief 判断是否是自动模式
     * @return true 自动模式
     * @return false 手动模式
     */
    bool IsAutoMode();

    /**
     * @brief 设置自动模式
     * @param mode true，设置为自动
     * @param mode false，设置为手动
     * @return true 成功
     * @return false 失败
     */
    bool SetAutoMode(bool mode);

    /**
     * @brief 当前上电状态
     * @return true 已上电
     * @return false 下电状态
     */
    bool IsPowerOn();

    /**
     * @brief 设置上下电
     * @param on true 上电
     * * @param on false 下电
     * @return true 成功
     * @return false 失败
     */
    bool SetPowerOn(bool on);

    /**
     * @brief 查询任务空间空闲
     * @return true 空闲可用
     * @return false 非空闲，不可用
     */
    bool IsTaskSpaceReady();

    /**
     * @brief 设置任务空间为busy和取消任务空间
     * @param space space=BUSY，busy=true;设置任务空间忙
     * @param busy space=BUSY，busy=false; 设置任务空间闲(回到Ready状态)
     * @return int 0正常，其他异常
     */
    int SetTaskSpace(const TaskSpaceAPI &space,bool busy);
    
    /**
     * @brief 当前机器人是否占用
     * @return true 忙不可用
     * @return false 空闲可用
     */
    bool IsRobotBusy();

    /**
     * @brief 设置机器人忙
     * @param busy true 设置为忙
     * @param busy false 设置为空闲
     * @note 需要成对使用，否则导致其他模块不可用
     * @return true 成功
     * @return false 失败
     */
    bool SetRobotBusy(bool busy);

    /**
     * @brief 获取当前机器人的运行阶段
     * @return RunningStateAPI 具体数据
     */
    RunningStateAPI GetRunningState();
private:
    std::shared_ptr<StatesImpl> pimpl;
};

}
}
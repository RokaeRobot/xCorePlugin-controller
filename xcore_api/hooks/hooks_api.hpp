/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file hooks_api.hpp
 * @brief 控制器特定操作的回调通知，插件可注册对应的事件接受回调
 */
#pragma once
#include <string>
#include "hooks_args_api.hpp"

namespace xcore_api{
namespace hooks{
/**
 * @brief 事件列表
 */
enum HookEventAPI{
    INVALID_EVENT,
    POINT_CHANGE,    ///< 点位增加删除修改事件回调
    PP_TO_MAIN,     ///< pp2main回调
    PP_TO_LINE,     ///< pp2line事件回调
    B_START_RUN,    ///< 开始运行事件回调
    B_PAUSE_RUN,    ///< 暂停运行事件回调
    E_STOP_RUN     ///< 急停事件回调
};

/**
 * @brief 指定hook回调的运行方式
 */
enum RunTypeAPI:short{
    SYNC_RUN, ///< 同步运行，会阻塞控制器对应的事件
    ASYNC_RUN_IN_THREAD_POOL, ///< 在普通线程池运行
    ASYNC_RUN_IN_RT_THREAD ///< 在rt线程运行
};
/**
 * @brief hook回调的通知函数
 */
using FUNC = std::function<void(const std::shared_ptr<const HookArgsBaseAPI>)>;
// 前向声明
class HookDataImpl;
/**
 * @brief 设置hook数据注册event和回调
 */
class HookDataAPI{
public:
    /**
     * @brief 注册事件
     * @param event 具体事件
     * @return true 成功
     * @return false 失败
     */
    bool SetEvent(HookEventAPI event);
    /**
     * @brief 注册回调通知函数
     * @param hook 回调函数
     * @return true 成功
     * @return false 失败
     */
    bool SetHook(const FUNC& hook);
    /**
     * @brief 设置回调运行方式
     * @param type 同步异步
     * @return true 成功
     * @return false 失败
     */
    bool SetRunType(RunTypeAPI type);
    /**
     * @brief 该事件触发时调度顺序，越高越先调度
     * @param pri 优先级
     * @return true 成功
     * @return false 失败
     */
    bool SetPriority(int pri);
public:
    /**
     * @brief 获取注册的事件
     * @return 具体的事件类型 
     */
    const HookEventAPI GetEvent() const;

    /**
     * @brief 获取注册的回调函数
     * @return 回调函数
     */
    const  FUNC GetHook() const ;

    /**
     * @brief 获取该数据的运行类型
     * @return 运行类型
     */
    const  RunTypeAPI GetRunType() const;

    /**
     * @brief 获取该事件的优先级
     * @return 优先级
     */
    const int GetPriority() const;
public:
    HookDataAPI();
    virtual ~HookDataAPI();
private:
    std::shared_ptr<HookDataImpl> pimpl;
};


/**
 * @brief 注册事件通知到控制器，不接受插件Start之后的动态注册
 * @param data 具体数据 
 * @return int hookid 大于0成功，-1失败
 */
int RegisterHooksAPI(const HookDataAPI &data);

/**
 * @brief 删除注册的hooks，需要在所有插件Start完成之后调用生效
 * @param hook_id 注册时返回的id
 * @return int 0成功，其他失败
 */
int UnRegisterHooksAPI(int hook_id);



}
}
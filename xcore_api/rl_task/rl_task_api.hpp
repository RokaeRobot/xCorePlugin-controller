/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file rl_task_api.hpp
 * @brief 获取有关rl任务的相关信息
 */
#pragma once
#include <vector>
#include <memory>

namespace xcore_api{
namespace rl_task{

//前向声明
class RLTaskImpl;
class RLTaskAPI{
public:
    RLTaskAPI();
    virtual ~RLTaskAPI();
public:

    /**
     * @brief 重置程序
     * @return true 成功
     * @return false 失败
     */
    bool PPToMain();

    /**
     * @brief   pptomain状态判断
     * @return  true:复位成功
     * @return false:复位失败
     */
    bool IsProgramResetDone();

    /**
     * @brief   跳转到 指定任务的 指定文件的 某行指令
     *          当后面两个参数都为空时，为单任务模式下跳转到当前执行文件的某行
     *          跳转失败后状态不可控，需要重新加载任务
     * @return  成功/失败
     * @param   line 指定行号
     *          task_name 任务名
     *          file_name 文件名
     */
    bool PPToLine(const int line, const std::string& task_name = "", const std::string& file_name = "");

    /**
     * @brief   跳转到 指定任务的 指定文件的 函数
     *          当后面两个参数都为空时，为单任务模式下跳转到当前执行文件的函数, 主要用于debugging 
     *          跳转失败后解释器状态不可控，需要重新加载任务
     * @return  成功/失败
     * @param   line 指定行号
     *          task_name 任务名
     *          file_name 文件名
     */
    bool PPToFunc(const int line, const std::string& task_name = "", const std::string& file_name = "");

    /**
     * @brief 修改循环模式
     * @param prog_loop true循环执行， false不循环
     * @return true 
     * @return false 
     */
    bool ModifyProgramLoop(const bool prog_loop);

    /**
     * @brief 唤醒单个任务
     * @param name 任务名称
     * @return true 成功
     * @return false 失败
     */
    bool AlarmRLTask(const std::string &name);

    /**
     * @brief 开始执行程序
     * @return true 成功开始执行
     * @return false 执行失败
     */
    bool StartRun();

    /**
     * @brief RL暂停，可再次开始
     * @return true 暂停成功
     * @return false 暂停失败
     */
    bool PauseRun();

    /**
     * @brief 暂停程序并等待机器人停止
     * @param timeout_ms 默认等待2000ms，一般不会超过500ms
     * @return true 执行成功
     * @return false 执行失败
     */
    bool PauseRunAndWaitIdle(int timeout_ms = 2000);

    /**
     * @brief 普通暂停，仅将任务暂停
     * @param task_name 任务名称
     * @return true 成功
     * @return false 失败
     */
    bool PauseTask(const std::string& task_name);

    /**
     * @brief 停止执行，停止后会将删除任务，需要重新加载才能执行
     * @return true 成功
     * @return false 失败
     */
    bool StopRun();

public:
    /**
     * @brief   获得某个任务 运行指针 指向的文件和行号(程序指针)
     * @note 可能会有1的差别
     * @param   task_name 任务名称
     * @return  pair<file_name, line> <任务文件名，行数>
     */
    std::pair<std::string, int> GetPointedLine(const std::string& task_name = "");

    /**
     * @brief 获得运动指针相关信息
     * @note 可能会有1的差别
     * @param   task_name 任务名
     * @return  pair<file_name, line> <任务文件名，行数>
     */
    std::pair<std::string, int> GetExecLine(const std::string& task_name = "");

    /**
     * @brief   设置某个任务 运行指针 指向的文件和行号(程序指针)
     * @note 可能会有1的差别
     * @param   task_name 任务名
     * @return  0正常，其他异常
     */
    int SetPointedLine(const std::string& task_name,const std::string& file_name,int line);

    /**
     * @brief   设置运动指针相关信息
     * @note 可能会有1的差别
     * @param   task_name 任务名
     * @return  0正常，其他异常
     */
    int SetExecLine(const std::string& task_name,const std::string& file_name,int line);

    /**
     * @brief 判断任务是否存在
     * @param name 任务名称
     * @return true 存在
     * @return false 不存在
     */
    bool IsTaskExists(const std::string &name);

    /**
     * @brief 当前任务名称是否在执行
     * @param task_name 任务名称
     * @return true 是
     * @return false 否
     */
    bool IsTaskRunning(const std::string& task_name);

    /**
     * @brief 判断当前是否有任务执行
     * @return true 是
     * @return false 否
     */
    bool IsTaskRunning();

private:
    std::shared_ptr<RLTaskImpl> pimpl;
};

}
}










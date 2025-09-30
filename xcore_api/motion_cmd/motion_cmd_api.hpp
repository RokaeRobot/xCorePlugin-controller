/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file motion_cmd_api.hpp
 * @brief 运动指令的接口
 */
#pragma once
#include <string>
#include <memory>
#include "const_data/pose_api.hpp"

namespace xcore_api{
namespace motion_cmd{
namespace xpose = ::xcore_api::const_data::pose;

/**
 * @brief 运动类型
 */
enum MoveTypeAPI : unsigned short {
    MOVE_ABSJ = 0,
    MOVE_J,
    MOVE_L,
    MOVE_C,
    MOVE_CF,
    MOVE_T,
    MOVE_SP
};

/**
 * @brief 全圆旋转姿态参数
 */
enum RotTypeAPI{
    CONST_POSE,  ///< 不变姿态
    ROT_AXIS,   ///< 动轴旋转
    FIXED_AXIS  ///< 定轴旋转
};

/**
 * @brief 指令的回调类型
 */
enum CallBackTypeAPI : unsigned short {
    MOVE_START = 0,
    MOVE_PAUSE,
    MOVE_FINISH,
    MOVE_ERROR
};
//前向声明
class MotionCmdArgsImpl;

/**
 * @brief 设置一条指令的参数，可在指令上添加自己的实现逻辑
 */
class MotionCmdArgsAPI{
public:

    /**
     * @brief 构造函数
     */
    MotionCmdArgsAPI();

    /**
     * @brief 析构函数
     */
    virtual ~MotionCmdArgsAPI();
public:

    /**
     * @brief 设置目标点
     * @param point 点位
     * @return int 0成功，其他失败
     */
    int SetTargetPoint(const xpose::PointAPI &point);
    /**
     * @brief 设置运动类型
     * @param type 具体类型
     * @return int 0成功，其他失败
     */
    int SetMoveType(const MoveTypeAPI &type);

    /**
     * @brief 设置全圆运动额外参数
     * @param type 姿态旋转模式
     * @param rundeg 执行角度-359到3600度
     * @return int 0成功，其他失败
     * @note 需要搭配MOVE_CF运动使用
     */
    int SetMoveCFData(RotTypeAPI type,double rundeg);

    /**
     * @brief 设置摆线运动额外参数
     * @param radius 摆线半径，单位m
     * @param step 步进长度，单位m
     * @return int 0成功，其他失败
     * @note 需要搭配MOVE_T运动使用
     */
    int SetMoveTData(double radius,double step);

    /**
     * @brief 设置螺旋线运动额外参数
     * @param radius 初始半径，单位m
     * @param step 旋转增率，单位m/rad
     * @param angle 合计旋转角度，单位rad
     * @param clockwise 旋转方向，true顺时针，false逆时针方向
     * @return int 0成功，其他失败
     * @note 需要搭配MOVE_SP运动使用
     */
    int SetMoveSPData(double radius,double step,double angle,bool clockwise);

    /**
     * @brief 设置工具参数
     * @param tool工具数据 
     * @return int  0成功，其他失败
     */
    int SetTool(const xpose::ToolAPI &tool);

    /**
     * @brief 设置工件数据
     * @param wobj 工件数据
     * @return int 0成功，其他失败
     */
    int SetWobj(const xpose::WobjAPI &wobj);

    /**
     * @brief 设置转弯区域数据
     * @param zone 转弯区
     * @return int 0成功，其他失败
     */
    int SetZone(const xpose::ZoneAPI &zone);

    /**
     * @brief 设置速度数据
     * @param speed 速度值
     * @return int 0成功，其他失败
     */
    int SetSpeed(const xpose::SpeedAPI &speed);

    /**
     * @brief 设置该指令为最后一条指令。通常用于结束当前连续运动。
     * @param last 最后一条
     * @return int 0成功，其他失败
     */
    int SetLast(bool last);

    /**
     * @brief 设置更新客户端执行的指针指向 
     * @param task_name 当前的任务名称
     * @param file_name 当前的工程文件
     * @param line 当前的行数
     * @note 工程数据可通过指令获取
     * @return int 0成功，其他失败
     */
    int SetUpdatePointer(const std::string& task_name,const std::string& file_name,int line);

    /**
     * @brief 设置轨迹的回调函数
     * @param type 回调类型
     * @param func 回调函数
     * @return int 0成功，其他失败
     */
    int SetCallback(CallBackTypeAPI type,const std::function<void()> &func); 

    /** 
     * @brief 设置辅助点，用于指令需要多个点位的情况
     * @param point 实际点位
     * @return int 0成功，其他失败
     */
    int SetAuxPoint(const xpose::PointAPI &point);

    /**
     * @brief 设置该条轨迹可触发的trigger
     * @param triggers 触发数据
     * @note MoveAbsJ运动类型不支持
     * @return int 0成功，其他失败
     */
    int SetTriggers(const std::vector<xpose::TriggerAPI> &triggers);

    /**
     * @brief 提前终止该指令的运行
     * @note 搭配trigger和IO可实现search指令,
     * @example 设置指令为一条很长的fine轨迹，并断前瞻，触发之后调用该接口结束轨迹
     * @param distance 最大停止距离单位m，默认2mm。
     * @return int 0成功,其他失败
     */
    int SetFinishInAdvance(double distance = 0.002);

private:
    std::shared_ptr<MotionCmdArgsImpl> pimpl;
    friend class MotionCmdArgsImpl;
};

/**
 * @brief 具体的指令发送接口
 */
class MotionCmdAPI{
public:
    MotionCmdAPI();
    virtual ~MotionCmdAPI();
public:

    /**
     * @brief 发送单条运动指令
     * @param args 指令的具体参数 
     * @return int 0成功，其他失败。
     */
    int SendCmd(const MotionCmdArgsAPI& args);

    /**
     * @brief 多条运动指令间断连续运行，适用于RL指令包含多条运动轨迹
     * @note 每条运动结束之后会暂停，严格保证上一条运动结束之后开始下一条轨迹
     * @example 轨迹1 startcallback--move--stop--finishcallback--轨迹2 startcallback--move--stop--finishcallback
     * @param vargs 多条运动数据
     * @return int 0成功，其他失败。
     */
    int SendSegmentCmds(const std::vector<MotionCmdArgsAPI>& vargs);
    
    /**
     * @brief 生成步退指令
     * @param args 步退指令参数
     * @return int 0成功，其他失败。
     */
    int SendStepBackCmd(const MotionCmdArgsAPI& args);
};







}
}
/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file pose_api.hpp
 * @brief 定义位姿常用的数据结构
 * @note 采用国际单位,米，弧度，千克等
 */

#pragma once
#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace xcore_api {
namespace const_data {
namespace pose{

/**
 * @brief 位置定义
 * @note 单位是m
 */
struct PositionAPI{
    double x;///< 单位m
    double y;
    double z;
    PositionAPI():x(0.0),y(0.0),z(0.0){};
};

/**
 * @brief 姿态四元数
 */
struct QuaternionAPI{
    double q1;
    double q2;
    double q3;
    double q4;
    QuaternionAPI():q1(1),q2(0),q3(0),q4(0){}
};

/**
 * @brief 姿态conf数据,确定机器人通过哪组解到目标位置
 */
struct ConfDataAPI {
    int cfx;
    int cf1;
    int cf2;
    int cf3;
    int cf4;
    int cf5;
    int cf6;
    int cf7;
    ConfDataAPI() :cfx(0), cf1(0), cf2(0), cf3(0), cf4(0), cf5(0), cf6(0), cf7(0) {};
};

/**
 * @brief 姿态，坐标系
 */
struct PoseAPI {
    PositionAPI p;
    QuaternionAPI q;
    PoseAPI operator *(const PoseAPI &right) const;///< 坐标系相乘，右乘
    PoseAPI Inverse() const;///< 逆
};

/**
 * @brief 点位信息，笛卡尔或关节
 */
struct PointAPI{
    PoseAPI pose; ///< 笛卡尔位姿
    std::vector<double>joint; ///< 轴关节，单位弧度
    bool is_joint{false};///< 笛卡尔或者轴关节
    std::vector<double> extjoint; ///< 外部轴数据（示教侧多为用户单位，见下方标志）
    /// 为 true 时：extjoint 已是控制器标准单位（如 GetExtJntPosUnit），SetTargetPoint 内不再做用户单位换算（与 RLProcessCmd 中 Ex 后一致）
    bool extjoint_already_standard{true};
    bool is_ext_rad{false};///< 外部轴是度
    double arm_angle; ///< 7轴机器人的臂角
    ConfDataAPI confdata; ///< conf配置
};

/**
 * @brief 转弯区数据
 */
struct ZoneAPI {
    double distance;///< 单位m
    double percent;///< 百分比
    ZoneAPI() :distance(0), percent(0) {};
};

/**
 * @brief 速度相关
 */
struct SpeedAPI {
    double tcpvel; ///< 平动速度m/s
    double orivel; ///< 旋转速度rad/s
    double psivel; ///< 7轴机器人的臂角
    double percent; ///< 关节速度百分比
    double ext_vel_l; ///< 外部轴线速度m/s
    double ext_vel_r; ///<外部轴角速度rad/s
    bool forced;///< 强制速度不受速度滑条影响
    SpeedAPI():tcpvel(0),orivel(0),psivel(0),percent(0), ext_vel_l(0), ext_vel_r(0),forced(false){}
};

/**
 * @brief 负载数据
 */
struct LoadAPI {
    double mass;///< 质量kg
    PoseAPI cog;///< 质心位置
    double ix;///< 转动惯量
    double iy;
    double iz;
    LoadAPI() :mass(0), ix(0), iy(0), iz(0) {};
};

/**
 * @brief trigger触发的相关定义
 */
struct TriggerAPI {
    enum TriggerType {
        DISTANCE,
        TIME
    };
    TriggerType type;///< 距离或者时间触发
    bool reference_is_from_start;///<  是否从起点开始计算
    double value_from_reference;///<  距离参考点的值,单位米(m)或者秒(s)
    std::function<void(void)> trigger_callback;///< 触发函数
    TriggerAPI():type(TriggerType::DISTANCE),reference_is_from_start(true),
    value_from_reference(0),trigger_callback([]{}){};
};

/**
 * @brief 工具坐标系
 */
struct ToolAPI {
    ToolAPI():rob_hold(true), tool_frame(), tool_load() {}
    bool rob_hold;///< true 手持，false 外部工具
    PoseAPI tool_frame;///< 工具坐标
    LoadAPI  tool_load;///< 工具负载
};

/**
 * @brief 工件相关数据定义
 */
struct WobjAPI {
    WobjAPI() : rob_hold(false), uf_prog(false), uf_id(0),mech_unit(nullptr){}
    bool rob_hold;///< true手持工件，false外部工件
    PoseAPI wobj_frame;///< 工件坐标系，相对用户坐标系定义
    LoadAPI wobj_load;///<  工件负载
    PoseAPI user_frame;///< 用户坐标系
    bool uf_prog; ///< 用户坐标系是否移动
    std::string uf_mec;///< 关联的机械单元
    int uf_id;///< 用户坐标id
    void *mech_unit;///< 机械单元具体数据
};


}
}
}

/**
 * @brief 打印位置数据重载，直接输出位置
 * @param os 
 * @param pos 位置
 * @return std::ostream& 
 */
inline std::ostream& operator << (std::ostream& os, const xcore_api::const_data::pose::PoseAPI& pos) {
    os << "pose:{{" << pos.p.x << "," << pos.p.y << "," << pos.p.z << "}, {" << pos.q.q1 << "," << pos.q.q2 << "," << pos.q.q3 << "," << pos.q.q4 << "}}";
    return os;
}
/**
 * @brief 打印点位数据的重载
 * @param os 
 * @param p 点位
 * @return std::ostream& 
 */
inline std::ostream& operator << (std::ostream& os, const xcore_api::const_data::pose::PointAPI& p) {
    os << "point:{"<<p.pose<<" is_joint: "<<p.is_joint<<" joint:{{";
    
    for(const auto &item:p.joint){
        os << item<<" ";
    }
    os<<"} ext:{";
    for(const auto &item:p.extjoint){
        os << item<<" ";
    }
    os<<"}}"<<" arm_angle:"<<p.arm_angle<<" confdata:{"<<p.confdata.cfx<<" "<<
    p.confdata.cf1<<" "<<p.confdata.cf2<<" "<<p.confdata.cf3<<" "<<p.confdata.cf4<<" "
    <<p.confdata.cf5<<" "<<p.confdata.cf6<<" "<<p.confdata.cf7;
    return os;
}
/**
 * @brief 打印速度数据结构
 * @param os 
 * @param speed 
 * @return std::ostream& 
 */
inline std::ostream& operator << (std::ostream& os, const xcore_api::const_data::pose::SpeedAPI& speed) {
    os<<"speed:{tcp:"<<speed.tcpvel<<" ori:"<<speed.orivel
    <<" psi:"<<speed.psivel<<" percent:"<<speed.percent<<" forced:"<<speed.forced;
    return os;
}
/**
 * @brief 打印转弯区数据
 * @param os 
 * @param zone 
 * @return std::ostream& 
 */
inline std::ostream& operator << (std::ostream& os, const xcore_api::const_data::pose::ZoneAPI& zone) {
    os << "zone:{distance:" << zone.distance << ",percent:"<<zone.percent<<"}";
    return os;
}
/**
 * @brief 打印trigger相关数据 
 * @param os 
 * @param t 
 * @return std::ostream& 
 */
inline std::ostream& operator << (std::ostream& os, const xcore_api::const_data::pose::TriggerAPI& t) {
    os << "trigger:{ distance?" << (int)t.type << " from_start?" << t.reference_is_from_start<<
        " value:" <<t.value_from_reference;
    return os;
}
/**
 * @brief 打印点位数据的操作符重载
 * @param os 
 * @param t 
 * @return std::ostream& 
 */
inline std::ostream& operator << (std::ostream& os, const xcore_api::const_data::pose::ToolAPI& t) {
    os << "tool:{ hold?" <<t.rob_hold << " tool_frame{" << t.tool_frame<<
        "} load:{ mass:"<<t.tool_load.mass<<" ix,iy,iz"<<t.tool_load.ix<<" "
        <<t.tool_load.iy<<" "<<t.tool_load.iz<<" cog:"<<t.tool_load.cog;
    return os;
}
/**
 * @brief 打印工件操作的重载
 * @param os 
 * @param w 
 * @return std::ostream& 
 */
inline std::ostream& operator << (std::ostream& os, const xcore_api::const_data::pose::WobjAPI& w) {
    os << "wobj:{ hold?" <<w.rob_hold << " wobj_frame{" << w.wobj_frame<<
        "} load:{ mass:"<<w.wobj_load.mass<<" ix,iy,iz"<<w.wobj_load.ix<<" "
        <<w.wobj_load.iy<<" "<<w.wobj_load.iz<<" cog:"<<w.wobj_load.cog
        <<" user_frame:"<<w.user_frame<<" uf_prog:"<<w.uf_prog<<" uf_mec"<< w.uf_mec
        <<" uf_id:"<<w.uf_id;

    return os;
}

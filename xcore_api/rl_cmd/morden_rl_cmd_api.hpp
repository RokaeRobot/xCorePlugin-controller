/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file morden_rl_cmd_api.hpp
 * @brief 实现一条自定义指令的接口
 */
#pragma once
#include <json/json.h>
#include "string.h"
#include "const_data/pose_api.hpp"

namespace xcore_api{
namespace rl_cmd{

/**
 * @brief 指令变量的类型
 */
enum class ValueTypeAPI : unsigned short
{
    VALUE_UNKNOWN = 0,
    VALUE_PROC_VOID,
    VALUE_TRAP_VOID,
    VALUE_INT, ///< 基础数据类型
    VALUE_DOUBLE,
    VALUE_BOOL,
    VALUE_STRING,
    VALUE_BYTE,
    VALUE_CLOCK, ///< 时钟
    VALUE_CONFDATA, ///< 配置数据
    VALUE_FCBOXVOL, ///< 力控相关信息
    VALUE_FCCARTNUM,
    VALUE_FCCYLINDERVOL,
    VALUE_FCSPHEREVOL,
    VALUE_FCXYZNUM,
    VALUE_INTNUM, ///< 整数
    VALUE_JOINTTARGET, ///< 关节数据
    VALUE_LOAD, ///< 负载数据
    VALUE_ORIENT, ///< 方向
    VALUE_PATH, ///< 路径
    VALUE_POS, ///< 位置
    VALUE_POSE, ///< 位姿
    VALUE_ROBTARGET, ///< 笛卡尔类型
    VALUE_SPEED, ///< 速度
    VALUE_SYNCIDENT,
    VALUE_TASKS, ///< 任务
    VALUE_TOOL, ///< 工具
    VALUE_TRIGDATA, ///< trigger类型
    VALUE_WOBJ, ///< 工件
    VALUE_ZONE, ///< 转弯区
    VALUE_SIGNAL_DI, ///< DI DO GI GO AI AO
    VALUE_SIGNAL_DO,
    VALUE_SIGNAL_GI,
    VALUE_SIGNAL_GO,
    VALUE_SIGNAL_AI,
    VALUE_SIGNAL_AO,
    VALUE_SIGNAL_DOUT,
    VALUE_SIGNAL_DIN,
    VALUE_SIGNAL_AOUT,
    VALUE_SIGNAL_AIN,
    VALUE_MODBUS, ///<  ModBus
    VALUE_INPUT_SIGNAL,
    VALUE_TRANS, ///<  TRANS 例如\STOP 指令的附加参数
    VALUE_KEY_PARA,
    VALUE_SWITCH, ///< On/Off
    VALUE_TORQUE_INFO, ///<  力矩信息
    VALUE_JOINT_TORQUE, ///< 轴空间观测力 外部力
    VALUE_CART_TORQUE, ///<  笛卡尔力 力矩
    VALUE_SOCKET_SERVER, ///<  网络控制信息
    VALUE_SOCKET_CONNECT,
    VALUE_CATCH_ERROR, ///<  捕获的错误信息
    VALUE_SERIAL, ///<  串口设备
    VALUE_NULL,
    VALUE_NULLABLE_SPEED  ///<  可缺省速度
};

//前向声明
class ArgTypeImpl;

/**
 * @brief 设置参数类型接口
 * 
 */
class ArgTypeAPI{
public:
    /**
     * @brief 构造函数
     */
    ArgTypeAPI();

    /**
     * @brief 带参构造函数
     * @param type 参数类型 
     * @param require 是必选参数，非可省参数
     */
    ArgTypeAPI(const ValueTypeAPI &type,const bool &require);

    /**
     * @brief 析构函数
     */
    ~ArgTypeAPI();
public:

    /**
     * @brief 设置当前的参数类型
     * @param type 具体类型
     */
    void SetValueType(const ValueTypeAPI &type);

    /**
     * @brief 必选参数还是可选参数
     * @param require 
     */
    void SetRequire(const bool &require);

public:
    /**
     * @brief 获取当前参数类型
     * @return ValueTypeAPI 具体类型
     */
    ValueTypeAPI GetValueType() const;

    /**
     * @brief 获取当前参数可选类型
     * @return true 必须参数
     * @return false 可省参数
     */
    bool GetRequire() const;
private:
     std::shared_ptr<ArgTypeImpl> pimpl;
};
/**
 * @brief 指令的调度结果数据
 */
enum CommandProcessResultAPI : int {
    CMD_PROCESS_SUCCESS = 0, ///< 成功继续运行
    CMD_PROCESS_ERROR, ///< 失败，仅暂停当前任务
    CMD_PROCESS_FATAL, ///< 致命错误，RL停止
    CMD_PROCESS_IGNORE, ///< 异步指令，任务被标记为异步等待
    CMD_PROCESS_EXTRA, ///< 额外执行的指令，不需要响应，常用于运动指令。
    CMD_PROCESS_RESCHEDULE, ///< 重新调度
    CMD_PROCESS_SPECIAL, ///< 特殊指令，会影响调度
};

/**
 * @brief 设置指令的前瞻类型
 */
enum CmdLookAheadImplAPI : int {
    WAIT_MOVE_PAUSE = 0, ///< 等运动执行完，指令断前瞻
    ACTIVATE_AT_LOOKAHEAD = 1, ///< 前瞻触发，比如print指令
    ACTIVATE_IN_ZONE = 2, ///< 转弯区域触发，上一条指令运动后触发
    MOVEMENT_ITSELF = 3, ///< 运动指令本身
};

/**
 * @brief 任务限制
 */
enum TaskLimitAPI : int {
    TASK_NO_LIMIT = 0, ///< 不限制
    TASK_LIMIT_MOVE = 1, ///< 限制运动任务
    TASK_LIMIT_NORMAL_AND_STATIC = 2 ///< 限制普通任务和半静态任务。
};

/**
 * @brief 步退行为
 */
enum StepBackAPI : int {
    STEP_BACK_SKIP = 0, ///< 跳过指令
    STEP_BACK_STOP = 1, ///< 停止步退
    STEP_BACK_CUSTOM = 2 ///< 使用定制行为。
};

//前向声明
class SymbolVarBaseAPI;
class ModernRLCmdImpl;
class RLCmdArgImpl;
class RLCmdConfigImpl;

/**
 * @brief 指令配置参数
 */
class RLCmdConfigAPI{
public:
    /**
     * @brief 默认构造函数
     */
    RLCmdConfigAPI();

    /**
     * @brief 带参的构造函数
     * @param ptr 参数具体指针
     */
    RLCmdConfigAPI(std::shared_ptr<RLCmdConfigImpl> ptr);

    /**
     * @brief 析构函数
     */
    ~RLCmdConfigAPI();
    
    /**
     * @brief 设置指令函数名称
     * @param func_name 指令函数名称
     */
    void SetFuncName(const std::string& func_name);
    
    /**
     * @brief 设置指令前瞻方式，默认断前瞻
     * @param look_ahead 具体数据
     */
    void SetLookAhead(const CmdLookAheadImplAPI &look_ahead) ;
    
    /**
     * @brief 设置任务限制类型
     * @param limit 限制数据
     */
    void SetTaskLimit(const TaskLimitAPI& limit);
    
    /**
     * @brief 设置指令是否需要括号
     * @param require_bracket true 需要，false 不需要
     */
    void SetRequireBracket(const bool& require_bracket);
    
    /**
     * @brief 设置指令函数的返回值类型
     * @param return_type 返回类型 
     */
    void SetReturnType(const ValueTypeAPI& return_type);
    
    /**
     * @brief 设置步退的类型
     * @param step_type 步退类型
     */
    void SetStepBack(const StepBackAPI& step_type);

public:
    /**
     * @brief 获取指令名称
     * @return  std::string 具体名称 
     */
    std::string GetFuncName() const;

    /**
     * @brief 获取前瞻类型
     * @return CmdLookAheadImplAPI 
     */
    CmdLookAheadImplAPI GetLookAhead() const;

    /**
     * @brief 获取任务限制类型
     * @return TaskLimitAPI 具体限制类型
     */
    TaskLimitAPI GetTaskLimit() const;

    /**
     * @brief 指令是否需要括号
     * @return true 需要
     * @return false 不需要
     */
    bool GetRequireBracket() const;

    /**
     * @brief 获取返回类型
     * @return  ValueTypeAPI
     */
    ValueTypeAPI GetReturnType() const;
    
    /**
     * @brief 获取步退行为
     * @return StepBackAPI 
     */
    StepBackAPI GetStepBack() const;
private:
    friend class ModernRLCmdImpl;
    std::shared_ptr<RLCmdConfigImpl> pimpl;
};

/**
 * @brief 指令返回值
 */
using cmdExecute_t = std::function<CommandProcessResultAPI()>;

/**
 * @brief 指令参数接口
 * @param v 指令需要的参数集合
 * @return std::shared_ptr<RLCmdArgImpl> 
 */
std::shared_ptr<RLCmdArgImpl> RequireArgsAPI(const std::vector<ArgTypeAPI> &v);

/**
 * @brief 指令实现的基类
 */
class ModernRLCmdAPI{
public:

    /**
     * @brief 构造函数，传入配置数据
     * @param cfg 配置数据
     */
    explicit ModernRLCmdAPI(const RLCmdConfigAPI& cfg);

    /**
     * @brief 析构函数
     */
    virtual ~ModernRLCmdAPI();

    /**
     * @brief 指令需要实现的具体执行逻辑
     * @return cmdExecute_t 
     */
    virtual cmdExecute_t ExecuteAction() = 0;

    /**
     * @brief 指令需要实现的需要的参数逻辑
     * @return std::shared_ptr<RLCmdArgImpl> 
     */
    virtual std::shared_ptr<RLCmdArgImpl> RequireArgs() = 0;
public:
    /**
     * @brief 获取当前的任务名称
     * @return std::string 任务名称
     */
    std::string GetCmdTask();

    /**
     * @brief 获取当前指令所在的文件
     * @return std::string 文件信息
     */
    std::string GetCmdFile();

    /**
     * @brief 获取指令当前所在的行数
     * @return int 
     */
    int GetCmdLine();

    /**
     * @brief 获取访问过的行数
     * @note 主要用于步退指令获取行数，步退时从后往前解释。
     * @return int 
     */
    int GetVisitedLine();

    /**
     * @brief 获取当前指令的配置数据
     * @return RLCmdConfigAPI 
     */
    RLCmdConfigAPI GetCmdConfig();

    /**
     * @brief 获取当前指令的所有参数
     * @note 通过符号表获取具体的数据
     * @return const std::vector<SymbolVarBaseAPI>& 符号的集合
     */
    const std::vector<SymbolVarBaseAPI>& GetCmdArgs();
    /**
     * @brief 设置当前指令的返回值
     * @param val 具体返回值数据
     */
    void SetReturnValue(const SymbolVarBaseAPI& val);
private:
    friend class MordenRLCmdSymbolImpl;
    std::shared_ptr<ModernRLCmdImpl> pimpl;
};

/**
 * @brief 1：宏实现指令的继承定义
 */
#define DECLARE_MORDEN_RLCMD_API(_type_name_) \
class _type_name_ : public ModernRLCmdAPI {\
public:\
    explicit _type_name_(const RLCmdConfigAPI& cfg):ModernRLCmdAPI(cfg){}\
    virtual ~_type_name_() {}\
    virtual cmdExecute_t ExecuteAction() override;\
    virtual std::shared_ptr<RLCmdArgImpl> RequireArgs() override;\
};

/**
 * @brief 2:该指令需要的参数
 */
#define MORDERN_CMD_ARGS_API(_type_name_)\
std::shared_ptr<RLCmdArgImpl> _type_name_::RequireArgs()

/**
 * @brief 3:指令的具体实现逻辑
 */
#define MORDERN_CMD_EXECUTE_API(_type_name_)\
cmdExecute_t _type_name_::ExecuteAction()


namespace xpose = ::xcore_api::const_data::pose;

//前向声明
class SymbolVarBaseImpl;

/**
 * @brief 参数的解析，获取具体的数据
 * @note 需要用户确认数据类型然后获取相应的数据
 */
class SymbolVarBaseAPI{
public:
    /**
     * @brief 有参构造，用户无需关心
     * @param ptr 
     */
    SymbolVarBaseAPI(std::shared_ptr<SymbolVarBaseImpl> ptr);

    /**
     * @brief 默认构造函数
     */
    SymbolVarBaseAPI();

    /**
     * @brief 默认析构函数
     */
    ~SymbolVarBaseAPI();

    /**
     * @brief 获取子单元数据，常用于复合结构
     * @param key 
     * @return SymbolVarBaseAPI 
     */
    SymbolVarBaseAPI GetSubUnit(const std::string &key);

    /**
     * @brief 获取double类型的数据
     * @note 需要数据匹配，默认返回0
     * @return double 
     */
    double GetDoubleVal();

    /**
     * @brief 获取当前bool类型的具体数据
     * @return true/false 
     */
    bool GetBoolVal();

    /**
     * @brief 获取当前int类型数据的具体值
     * @return int 
     */
    int GetIntVal();

    /**
     * @brief 获取当前byte类型数据的具体值
     * @return unsigned char 
     */
    unsigned char GetByteVal();

    /**
     * @brief 获取当前string类型数据的具体值
     * @return std::string 
     */
    std::string GetStringVal();

    /**
     * @brief 获取当前点位的数据
     * @return xpose::PointAPI 
     */
    xpose::PointAPI GetPointAPI();

    /**
     * @brief 获取当前的速度数据
     * @return xpose::SpeedAPI 
     */
    xpose::SpeedAPI GetSpeedAPI();

    /**
     * @brief 获取当前转弯区数据
     * @return xpose::ZoneAPI 
     */
    xpose::ZoneAPI GetZoneAPI();

    /**
     * @brief 获取当前工具数据
     * @return xpose::ToolAPI 
     */
    xpose::ToolAPI GetToolAPI();

    /**
     * @brief 获取当前的工件数据
     * @return xpose::WobjAPI 
     */
    xpose::WobjAPI GetWobjAPI();

    /**
     * @brief 给robtarget类型参数赋值
     * @param point点位数据 
     */
    void ResetRobTarget(const xpose::PointAPI &point);

    /**
     * @brief 给布尔类型参数赋值
     * @param val 具体数值
     */
    void ResetBool(bool val);

    /**
     * @brief 将当前int参数重新赋值
     * @param val 新值
     */
    void ResetInt(int val);

    /**
     * @brief 将当前参数的double数据重新赋值
     * @param val 新数据
     */
    void ResetDouble(double val);

    /**
     * @brief 将当前string类型数据重新赋值
     * @param val 新数据
     */
    void ResetString(const std::string &val);

    /**
     * @brief 将bool类型的数组数据重新赋值
     * @note 需要注意数据长度 
     * @param v 新数据
     */
    void ResetBoolArr(const std::vector<bool> &v);

    /**
     * @brief 将int类型的数组数据重新赋值
     * @param v 新数据
     */
    void ResetIntArr(const std::vector<int> &v);

    /**
     * @brief 将dopuble类型的数组数据重新赋值
     * @param v 新数据
     */
    void ResetDoubleArr(const std::vector<double> &v);

    /**
     * @brief 将string类型的数组数据重新赋值
     * @param v 新数据
     */
    void ResetStringArr(const std::vector<std::string> &v);
private:
    friend class ModernRLCmdAPI;
    std::shared_ptr<SymbolVarBaseImpl> pimpl;
};

/**
 * @brief 将当前指令注册到控制器中
 * @param ptr 指令指针数据
 * @return true 成功
 * @return false 失败
 */
bool RegPluginCmdsAPI(std::shared_ptr<ModernRLCmdAPI> ptr);

/**
 * @brief 将当前步退指令的数据注册到控制器中
 * @param ptr 步退指令
 * @return true 成功
 * @return false 失败
 */
bool RegPluginStepBackCmdsAPI(std::shared_ptr<ModernRLCmdAPI> ptr);

}
}

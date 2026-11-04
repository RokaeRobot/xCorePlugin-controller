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
#include <set>

namespace data {
namespace motion {
    // 存放接触寻位结果
    struct CdTouchResult;
}
}

struct VmValue;
using VmValuePtr = std::shared_ptr<VmValue>;

struct VmArgVRuleInCmd;
namespace xcore_api{
namespace rl_cmd{

/**
 * @brief 指令变量的类型
 *        删除了在3.2解释器自定义指令中用不到的类型
 */
/**
 * @brief 指令变量的类型
 *        删除了在3.2解释器自定义指令中用不到的类型
 */
enum class ValueTypeAPI : unsigned short
{
    VALUE_UNKNOWN = 0,
//     VALUE_PROC_VOID,
//     VALUE_TRAP_VOID,
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
    VALUE_INTNUM, 
    VALUE_JOINTTARGET, ///< 关节数据
    VALUE_LOAD, ///< 负载数据
    VALUE_ORIENT, ///< 方向
    VALUE_PATH, ///< 路径
    VALUE_POS, ///< 位置
    VALUE_POSE, ///< 位姿
    VALUE_ROBTARGET, ///< 笛卡尔类型
    VALUE_SPEED, ///< 速度
//     VALUE_SYNCIDENT,
//     VALUE_TASKS, ///< 任务
    VALUE_TOOL, ///< 工具
    VALUE_TRIGDATA, ///< trigger类型
    VALUE_WOBJ, ///< 工件
    VALUE_ZONE, ///< 转弯区
    VALUE_CD, ///< 接触寻位结果
    VALUE_SIGNAL_DI, ///< DI DO GI GO AI AO
    VALUE_SIGNAL_DO,
    VALUE_SIGNAL_GI,
    VALUE_SIGNAL_GO,
    VALUE_SIGNAL_AI,
    VALUE_SIGNAL_AO,
   // 以下无效
//     VALUE_SIGNAL_DOUT,
//     VALUE_SIGNAL_DIN,
//     VALUE_SIGNAL_AOUT,
//     VALUE_SIGNAL_AIN,
    VALUE_MODBUS, ///<  ModBus
    VALUE_INPUT_SIGNAL,
    VALUE_TRANS, ///<  TRANS 例如\STOP 指令的附加参数
    VALUE_KEY_PARA,
    VALUE_SWITCH, ///< On/Off
    VALUE_TORQUE_INFO, ///<  力矩信息
    VALUE_JOINT_TORQUE, ///< 轴空间观测力 外部力
    VALUE_CART_TORQUE, ///<  笛卡尔力 力矩
    VALUE_SOCKET_SERVER, ///<  网络控制信息*/
    VALUE_SOCKET_CONNECT,
/*    VALUE_CATCH_ERROR, ///<  捕获的错误信息*/
/*    VALUE_SERIAL, ///<  串口设备*/
    VALUE_NULL,

    // 解释器支持基本类型参数的隐式转换
    VALUE_BOOL_ANY,
    VALUE_INT_ANY,
    VALUE_DOUBLE_ANY,
/*    VALUE_NULLABLE_SPEED  ///<  可缺省速度*/
};

// 3.2解释器支持3种参数缺省形式
enum class ArgRuleTypeAPI : int {
    ARG_MUST_HAVE = 0,     // 必须存在的参数
    ARG_DEFAULT_AT_LAST,
    ARG_DEFAULT_NOT_LAST,
};
//前向声明
class ArgTypeImpl;
class SymbolVarBaseAPI;

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
     * @brief 构造不可缺省的形参
     */
    ArgTypeAPI(ValueTypeAPI type);

    /**
     * @brief 带参构造函数
     * @param types 某个参数支持的所有类型
     * @brief 构造不可缺省的形参
     */
    ArgTypeAPI(std::vector<ValueTypeAPI> types);


    /**
     * @brief 带参构造函数
     * @param type 参数类型
     * @param rule 参数缺省
     * @param value 参数默认值
     * @brief 构造可缺省的形参
     */
    ArgTypeAPI(ValueTypeAPI type, ArgRuleTypeAPI arg_rule,
        SymbolVarBaseAPI value);

    
    /**
     * @brief 带参构造函数
     * @param types 支持的参数类型列表，一个参数可以支持多种类型
     * @param rule 参数缺省
     * @param value 参数默认值
     * @brief 构造可缺省的形参
     */
    ArgTypeAPI(std::vector<ValueTypeAPI> types, ArgRuleTypeAPI arg_rule,
        SymbolVarBaseAPI value);

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
     * @brief 参数的缺省形式，不缺省，在参数列表末尾缺省，不在参数列表缺省
     * @param rule 参数缺省规则
     */
    void SetRule(const ArgRuleTypeAPI &rule);

    /**
     * @brief 缺省时的默认值
     * @param value 默认值
     */
    void SetDefaultValue(const SymbolVarBaseAPI& value);

public:
    /**
     * @brief 获取当前参数类型
     * @return ValueTypeAPI 具体类型
     */
    std::vector<ValueTypeAPI> GetValueType() const;


    /**
     * @brief 获取当前参数的缺省形式
     * @return ArgRuleTypeAPI
     */
    ArgRuleTypeAPI GetRule() const;

    /**
     * @brief 获取当前参数的默认值
     * @return SymbolVarBaseAPI
     */
    std::shared_ptr<SymbolVarBaseAPI> GetDefaultValue() const;

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
    MOVEMENT_ITSELF_AND_WAIT_MOVE_PAUSE = 4, ///< 属于运动指令本身，且等运动执行完，指令断前瞻
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
class RLCallFrameImpl;

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
     * @brief 获取步退行为
     * @return StepBackAPI 
     */
    StepBackAPI GetStepBack() const;
private:
    friend class ModernRLCmdImpl;
    std::shared_ptr<RLCmdConfigImpl> pimpl;
};

// 将一些运行时信息放到这里来提供
class RLCallFrameAPI {
public:
    RLCallFrameAPI(std::shared_ptr<RLCallFrameImpl> ptr);
    ~RLCallFrameAPI();

    std::string GetCmdTask();
    std::string GetCmdFile();
    int GetCmdLine();
    int GetVisitedLine();
    void SetReturnValue(const SymbolVarBaseAPI& val);

private:
    friend class ModernRLCmdImpl;
    std::shared_ptr<RLCallFrameImpl> pimpl;
};
 
/**
 * @brief 指令返回值
 */
// 内层lambda
using CommandExecuteAPI = std::function<CommandProcessResultAPI()>;
using CommandExecuteWithLookaheadAPI = std::pair<CommandExecuteAPI, CmdLookAheadImplAPI>;

// 外层lambda
using RLCmdActionAPI = std::function<CommandExecuteAPI(
    std::shared_ptr<RLCallFrameAPI>, std::vector<std::shared_ptr<SymbolVarBaseAPI>>)>;
//单语句多指令lamdba
using RLCmdMultipleActionAPI = std::function<std::vector<CommandExecuteAPI>(
    std::shared_ptr<RLCallFrameAPI>, std::vector<std::shared_ptr<SymbolVarBaseAPI>>, std::set<int>&)>;
//根据参数输入变更前瞻类型
using RLCmdActionWithLookaheadAPI = std::function<CommandExecuteWithLookaheadAPI(
    std::shared_ptr<RLCallFrameAPI>, std::vector<std::shared_ptr<SymbolVarBaseAPI>>)>;

/**
 * @brief 指令参数接口
 * @param v 指令需要的参数集合 
 * @return std::shared_ptr<RLCmdArgImpl> 
 */
std::shared_ptr<RLCmdArgImpl> RequireArgsAPI(const std::vector<ArgTypeAPI> &v);

/**
 * @brief 指令实现的接口类
 *        用户通过实例化这个类进行自定义指令
 *        核心是将的配置传递给内部封装的指令实现（封装了解释器向外提供的指令注册接口）
 */
class ModernRLCmdAPI{
public:

    /**
     * @brief 构造函数，传入配置数据
     * @param cfg 配置数据
     */
    explicit ModernRLCmdAPI(const RLCmdConfigAPI& cfg);

    /**
     * @brief 单语句多指令构造函数，传入配置数据，传入子指令配置
     * @param cfg 配置数据
     * @param sub_cfgs 子指令配置数据
     */
    explicit ModernRLCmdAPI(const RLCmdConfigAPI& cfg, const std::vector<RLCmdConfigAPI>& sub_cfgs);

    /** 
     * @brief 析构函数
     */
    virtual ~ModernRLCmdAPI();

public:
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
    const std::vector<std::shared_ptr<SymbolVarBaseAPI>>& GetCmdArgs();
    /**
     * @brief 设置当前指令的返回值
     * @param val 具体返回值数据
     */
    void SetParams(const std::initializer_list<ArgTypeAPI>& v);
    void SetExecutor(RLCmdActionAPI& action);
    /**
     * @brief 单语句对应的多条指令需要实现每一条子指令的具体执行逻辑
     * @return action 指令具体执行逻辑
     */
    void SetExecutorVector(RLCmdMultipleActionAPI& action);
	// 设置步退
    void SetExecutorStb(RLCmdActionAPI& action);
	// 设置单语句多指令步退
	void SetExecutorStbVector(RLCmdMultipleActionAPI& action);
    // 设置前瞻参数
	void SetExecutorWithLookahead(RLCmdActionWithLookaheadAPI& action);
    ModernRLCmdAPI Convert();
    ModernRLCmdAPI ConvertWithLookahead();
private:
    friend bool RegPluginCmdsAPI(std::shared_ptr<ModernRLCmdAPI> ptr);
    std::shared_ptr<ModernRLCmdImpl> pimpl;
};
//1.1 单语句，单指令指令定义
#define BEGIN_COMMAND_API(cmd_config) \
        ModernRLCmdAPI __builder(cmd_config);
//1.2 单语句，多指令指令定义
//注：单语句多指令暂不支持中断
#define BEGIN_MULTIPLE_COMMAND_API(cmd_config, sub_configs) \
        ModernRLCmdAPI __builder(cmd_config, sub_configs);

//2. 指令参数定义
#define PARAMS_API(...) \
    __builder.SetParams({__VA_ARGS__});

//3.1 单语句，单指令具体执行逻辑
#define EXECUTE_API(lambda) \
    __builder.SetExecutor(lambda);
//3.2 单语句，多指令具体执行逻辑
//注：单语句多指令暂不支持中断
#define EXECUTE_MULTIPLE_API(lambda) \
    __builder.SetExecutorVector(lambda);

#define EXECUTE_WITH_LOOKAHEAD_API(lambda) \
    __builder.SetExecutorWithLookahead(lambda);
    
//4,1 单语句，单指令步退逻辑
#define EXECUTE_STB_API(lambda) \
    __builder.SetExecutorStb(lambda);
//4.2 单语句，多指令步退逻辑
//注：单语句多指令暂不支持步退
#define EXECUTE_MULTIPLE_STB_API(lambda) \
    __builder.SetExecutorStbVector(lambda);

//5 指令注册
#define REGISTER_COMMAND_API \
    RegPluginCmdsAPI(std::make_shared<ModernRLCmdAPI>(__builder.Convert()));

#define REGISTER_COMMAND_WITH_LOOKAHEAD_API \
    RegPluginCmdsAPI(std::make_shared<ModernRLCmdAPI>(__builder.ConvertWithLookahead()));

namespace xpose = ::xcore_api::const_data::pose;

//前向声明
class SymbolVarBaseImpl;
VmValuePtr CreateVmValuePtr(const ValueTypeAPI& type); // 创建一个VmValuePtr变量
VmValuePtr GetVmValuePtrByName(const std::string& var_name); // 根据变量名称获取VmValuePtr变量

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
     * @brief 拷贝构造函数
     */
    SymbolVarBaseAPI(const SymbolVarBaseAPI& other) = default;

    /**
     * @brief 移动构造函数
     */
    SymbolVarBaseAPI(SymbolVarBaseAPI&& other);

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
     * @brief 获取变量名称
     * @return std::string
     */
    std::string GetVarName();

    /**
     * @brief 获取寻位结果
     * @return data::motion::CdTouchResult
     */
    data::motion::CdTouchResult GetCdTouchResult();

    /**
     * 解析robtarget, 若为NULL或参数类型不符, 返回Json::nullValue
     * @return
     */
    Json::Value GetRotTarget();
    Json::Value GetSpeed();
    Json::Value GetZone();
    Json::Value GetTool();
    Json::Value GetWobj();
    Json::Value GetCd();    //symbol转JsonValue

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

    /**
     * @brief 将当前wobj参数重新赋值
     * @param wobj 新值
     */
    void ResetWobj(const xpose::WobjAPI& wobj);

    /**
     * @brief 将当前cd参数重新赋值
     * @param cd 新值
     */
    void ResetCd(const data::motion::CdTouchResult& cd);

    /**
     * @brief 该变量是否为NULL
     */
    bool isNull();
private:
    friend class ModernRLCmdAPI;
    friend class RLCallFrameAPI;
    friend class ArgTypeAPI;
    friend VmArgVRuleInCmd GetVmArgRule(const ArgTypeAPI& arg);
    std::shared_ptr<SymbolVarBaseImpl> pimpl;
};

/**
 * @brief 将当前指令注册到控制器中
 * @param ptr 指令指针数据
 * @return true 成功
 * @return false 失败
 */
bool RegPluginCmdsAPI(std::shared_ptr<ModernRLCmdAPI> ptr);
}

}

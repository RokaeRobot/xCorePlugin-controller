/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file printq_cmd.hpp
 * @brief 指令注册
 */
#include <g3log/g3log.hpp>
#include "rl_cmd/morden_rl_cmd_api.hpp"


namespace _printq_ {
using namespace xcore_api::rl_cmd;

/**
 * @brief 1：指定指令名
 */
DECLARE_MORDEN_RLCMD_API(Printq);

/**
 * @brief 2：指定指令所需的参数
 */
MORDERN_CMD_ARGS_API(Printq) {
    std::vector<ArgTypeAPI>v;
    //必选参数rob，可选wobj和string
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_WOBJ,false);
    v.emplace_back(ValueTypeAPI::VALUE_STRING,false);
    return RequireArgsAPI(v);
}
/**
 * @brief 3：指令的具体实现逻辑
 */
MORDERN_CMD_EXECUTE_API(Printq) {
    cmdExecute_t result = [=] {
        //获取所有的参数
        auto args = GetCmdArgs();
        //获取嵌套的数据
        auto cart_pos = args[0].GetSubUnit("ROT");
        //获取task file line
        LOG(INFO) <<"printq:"<<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetCmdLine();
        std::vector<double> robs_q = {
            cart_pos.GetSubUnit("Q1").GetDoubleVal(), cart_pos.GetSubUnit("Q2").GetDoubleVal(),
            cart_pos.GetSubUnit("Q3").GetDoubleVal(), cart_pos.GetSubUnit("Q4").GetDoubleVal() };

        LOG(INFO) << "printq Q1="<<robs_q[0]<<" Q2="<<robs_q[1]<<" Q3="<<robs_q[2]<<" Q4="<<robs_q[3]<<" ";
        LOG(INFO) << "printq str="<<args[2].GetStringVal();
        return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
    };
    return result;
}

/**
 * @brief 4：生成指令
 * @return std::shared_ptr<ModernRLCmdAPI> 指令指针 
 */
std::shared_ptr<ModernRLCmdAPI> makePrintq() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("printq");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::WAIT_MOVE_PAUSE) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置指令是否需要括号
    cfg.SetRequireBracket(true);
    //函数的返回值类型
    cfg.SetReturnType(ValueTypeAPI::VALUE_DOUBLE);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);

    return std::make_shared<Printq>(cfg);
}

}
/**
 * @brief 5：在初始化调用注册到xcore系统中
 */
void PrintqCmdExample(){
    xcore_api::rl_cmd::RegPluginCmdsAPI(_printq_::makePrintq());
}


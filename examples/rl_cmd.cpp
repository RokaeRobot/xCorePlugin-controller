/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file rl_cmd.hpp
 * @brief 指令注册例子,打印四元数到日志
 */
#include "log/log_api.hpp"
#include "rl_cmd.hpp"


namespace _printq_ {
using namespace xcore_api::rl_cmd;

/**
 * @brief 指令构建和注册
 */
void RegPrintq() {
    // 1.指令配置，如名称、触发方式、任务限制等
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("printq");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::WAIT_MOVE_PAUSE) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);
    
    // 2.根据配置创建指令
    BEGIN_COMMAND_API(cfg)

    // 3.为指令配置参数检查器
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ),
        ArgTypeAPI(ValueTypeAPI::VALUE_STRING)
    )

    // 4.指令正向执行体
    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        //获取嵌套的数据
        auto cart_pos = args[0]->GetSubUnit("ROT");
        std::vector<double> robs_q = {
            cart_pos.GetSubUnit("Q1").GetDoubleVal(), cart_pos.GetSubUnit("Q2").GetDoubleVal(),
            cart_pos.GetSubUnit("Q3").GetDoubleVal(), cart_pos.GetSubUnit("Q4").GetDoubleVal()};

        CommandExecuteAPI cmd_exec = [=]()
        {
            LOG_INFO << "printq:" << frame->GetCmdTask() << " " << frame->GetCmdFile() << " " << frame->GetCmdLine();

            LOG_INFO << "printq Q1=" << robs_q[0] << " Q2=" << robs_q[1] << " Q3=" << robs_q[2] << " Q4=" << robs_q[3] << " ";
            LOG_INFO << "printq str=" << args[2]->GetStringVal();
            return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
        };
        return cmd_exec;
    };
    EXECUTE_API(cmd_func)

    // 5.指令步退执行体（根据实际需要添加）
    RLCmdActionAPI cmd_func_stb = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        //获取嵌套的数据
        auto cart_pos = args[0]->GetSubUnit("ROT");
        
        std::vector<double> robs_q = {
            cart_pos.GetSubUnit("Q1").GetDoubleVal(), cart_pos.GetSubUnit("Q2").GetDoubleVal(),
            cart_pos.GetSubUnit("Q3").GetDoubleVal(), cart_pos.GetSubUnit("Q4").GetDoubleVal()};

        CommandExecuteAPI cmd_exec = [=]()
        {
            LOG_INFO << "printq:" << frame->GetCmdTask() << " " << frame->GetCmdFile() << " " << frame->GetCmdLine();

            LOG_INFO << "printq Q1=" << robs_q[0] << " Q2=" << robs_q[1] << " Q3=" << robs_q[2] << " Q4=" << robs_q[3] << " ";
            LOG_INFO << "printq str=" << args[2]->GetStringVal();
            return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
        };
        return cmd_exec;
    };
    EXECUTE_STB_API(cmd_func_stb)
    
    // 6.将指令注册给控制器
    REGISTER_COMMAND_API
}

}
/**
 * @brief 5：在初始化调用注册到xcore系统中
 */
void RLCmdExampleInit(){
    _printq_::RegPrintq();
}


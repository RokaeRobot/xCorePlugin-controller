/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 *
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 *
 * @file ElectricClawRLCmd.cpp
 * @brief 注册 RL 指令
 */
#include "ElectricClawRLCmd.h"

namespace electric_claw_cmd
{
    using namespace xcore_api::rl_cmd;
    using namespace xcore_api::endtool;

    /**
     * @brief 实现指令ElectricClawStop
     */
    void RegElectricClawStop() {
        // 配置指令属性
        RLCmdConfigAPI cfg;
        cfg.SetFuncName("ElectricClawStop");
        // 设置指令前瞻方式
        cfg.SetLookAhead(CmdLookAheadImplAPI::ACTIVATE_AT_LOOKAHEAD);
        // 设置任务限制类型
        cfg.SetTaskLimit(TaskLimitAPI::TASK_LIMIT_MOVE);
        // 设置步退的类型
        cfg.SetStepBack(StepBackAPI::STEP_BACK_STOP);
        BEGIN_COMMAND_API(cfg)

        // 定义指令参数
        PARAMS_API(ArgTypeAPI(ValueTypeAPI::VALUE_INT))

        RLCmdActionAPI action = [=](std::shared_ptr<RLCallFrameAPI> frame,
            std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
            
            //  获取电磁爪ID
            int claw_id = args[0]->GetIntVal();
            // 停止电磁爪
            CommandExecuteAPI cmd_exec = [=]() -> CommandProcessResultAPI {
                bool ret = api.stopElectricClaw(claw_id);

                LOG(INFO) << "send electric claw stop cmd result:" << ret;
                LOG(INFO) << "claw_id:" << claw_id;
                LOG(INFO) << ":" << frame->GetCmdTask() << " " << frame->GetCmdFile() << " " << frame->GetCmdLine();
                if (ret)
                    return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
                else
                    return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            };
            return cmd_exec;

        };

        // 定义指令执行逻辑
        EXECUTE_API(action);

        // 定义指令步退执行逻辑
        // 用户点击上一步时执行该逻辑
        // EXECUTE_STB_API(action);
        //  注册指令
        REGISTER_COMMAND_API
    }

    /**
     * @brief 实现指令ElectricClawStart
     */
    void RegElectricClawStart()
    {
        // 配置指令属性
        RLCmdConfigAPI cfg;
        cfg.SetFuncName("ElectricClawStart");
        // 设置指令前瞻方式
        cfg.SetLookAhead(CmdLookAheadImplAPI::WAIT_MOVE_PAUSE);
        // 设置任务限制类型
        cfg.SetTaskLimit(TaskLimitAPI::TASK_LIMIT_MOVE);
        // 设置步退的类型
        cfg.SetStepBack(StepBackAPI::STEP_BACK_STOP);
        BEGIN_COMMAND_API(cfg)
        // 定义指令参数
        PARAMS_API(
            ArgTypeAPI(ValueTypeAPI::VALUE_INT), // 电磁爪ID
            ArgTypeAPI(ValueTypeAPI::VALUE_INT), // 电磁爪模式
            ArgTypeAPI(ValueTypeAPI::VALUE_INT), // 电磁爪宽度
            ArgTypeAPI(ValueTypeAPI::VALUE_INT), // 电磁爪力
            ArgTypeAPI(ValueTypeAPI::VALUE_INT)  // 电磁爪速度
        )
        RLCmdActionAPI action = [=](std::shared_ptr<RLCallFrameAPI> frame,
            std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {

            //  获取电磁爪ID
            int claw_id = args[0]->GetIntVal();
            // 获取电磁爪模式
            int mode = args[1]->GetIntVal();
            // 获取电磁爪宽度
            int width = args[2]->GetIntVal();
            // 获取电磁爪力
            int force = args[3]->GetIntVal(); 
            // 获取电磁爪速度
            int speed = args[4]->GetIntVal();   
            // 启动电磁爪
            CommandExecuteAPI cmd_exec = [=]() {
                bool ret = api.startElectricClaw(
                                claw_id, width, force, speed, mode);

                LOG(INFO) << "send electric claw start cmd result:" << ret;
                LOG(INFO) << "claw_id:" << claw_id;
                LOG(INFO) << "mode:" << mode;
                LOG(INFO) << "width:" << width;
                LOG(INFO) << "force:" << force;
                LOG(INFO) << "speed:" << speed;
                LOG(INFO) << ":" << frame->GetCmdTask() << " " << frame->GetCmdFile() << " " << frame->GetCmdLine();
                if (ret)
                    return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
                else
                    return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            };
            return cmd_exec;
        };
        // 定义指令执行逻辑
        EXECUTE_API(action);
        // 定义指令步退执行逻辑
        // 用户点击上一步时执行该逻辑
        // EXECUTE_STB_API(action);
        //  注册指令
        REGISTER_COMMAND_API
    }

    /**
     * @brief 实现指令ElectricClawStatus
     */
    void RegElectricClawStatus() {
        // 配置指令属性
        RLCmdConfigAPI cfg;
        cfg.SetFuncName("ElectricClawStatus");
        // 设置指令前瞻方式
        cfg.SetLookAhead(CmdLookAheadImplAPI::ACTIVATE_AT_LOOKAHEAD);
        // 设置任务限制类型
        cfg.SetTaskLimit(TaskLimitAPI::TASK_LIMIT_MOVE);
        // 设置步退的类型
        cfg.SetStepBack(StepBackAPI::STEP_BACK_STOP);
        BEGIN_COMMAND_API(cfg)
        // 定义指令参数
        PARAMS_API(
            ArgTypeAPI(ValueTypeAPI::VALUE_INT), // 电磁爪ID
            ArgTypeAPI(ValueTypeAPI::VALUE_INT), // 电磁爪状态
            ArgTypeAPI(ValueTypeAPI::VALUE_INT), // 电磁爪外部宽度
            ArgTypeAPI(ValueTypeAPI::VALUE_INT), // 电磁爪内部宽度
            ArgTypeAPI(ValueTypeAPI::VALUE_INT)  // 电磁爪力
        )

        RLCmdActionAPI action = [=](std::shared_ptr<RLCallFrameAPI> frame,
            std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI                              {
                                 
            //  获取电磁爪ID
            int claw_id = args[0]->GetIntVal();

            CommandExecuteAPI cmd_exec = [=]() {
                // 获取电磁爪状态
                int status = 0;
                // 获取电磁爪外部宽度
                int external_width = 0;
                // 获取电磁爪内部宽度
                int internal_width = 0;
                // 获取电磁爪力
                int force = 0;
                bool ret = api.getStatusElectricClaw(
                    claw_id, status, external_width, internal_width, force);
                LOG(INFO) << "get electric claw status cmd result:" << ret;
                LOG(INFO) << "claw_id:" << claw_id;
                LOG(INFO) << "status:" << status;
                LOG(INFO) << "external_width:" << external_width;
                LOG(INFO) << "internal_width:" << internal_width;
                LOG(INFO) << "force:" << force;
                LOG(INFO) << ":" << frame->GetCmdTask() << " " << frame->GetCmdFile() << " " << frame->GetCmdLine();
                args[1]->ResetInt(status);
                args[2]->ResetInt(external_width);
                args[3]->ResetInt(internal_width);
                args[4]->ResetInt(force);
                if (ret)
                    return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
                else
                    return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            }; 
            return cmd_exec;
        };
        // 定义指令执行逻辑
        EXECUTE_API(action);
        // 定义指令步退执行逻辑
        // 用户点击上一步时执行该逻辑
        // EXECUTE_STB_API(action);
        //  注册指令
        REGISTER_COMMAND_API
    }
}

/**
 * @brief 注册所有电磁爪控制指令到系统中
 */
void ElectricClawCmd()
{
    electric_claw_cmd::RegElectricClawStop();
    electric_claw_cmd::RegElectricClawStart();
    electric_claw_cmd::RegElectricClawStatus();
}
/**
 * Copyright (C) 2026 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 * @file multiple_cmd.cpp
 * @brief 演示如何配置一条单语句多指令
 */
#include <functional>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "log/log_api.hpp"
#include "multiple_cmd.hpp"

#if defined(BEGIN_MULTIPLE_COMMAND_API) && defined(EXECUTE_MULTIPLE_API)
namespace multiple_cmd {
// PMultiMoveL(pFirst, pSecond, vExample, toolExample, wobjExample, TRUE);
// PMultiMoveL（第一个点位, 第二个点位, 速度工具, 工件, 是否执行打印的动作）
// 指令示例：PMultiMoveL(p1,p2,v10,tool0,wobj0,true);
//
//
// 解析一次 RL 调用的参数，按顺序返回三个执行体；实际动作写在各执行体中。
namespace {
std::vector<CommandExecuteAPI> expandMultiMove(std::shared_ptr<RLCallFrameAPI> frame,
    std::vector<std::shared_ptr<SymbolVarBaseAPI>> args, std::set<int>& ignore_cmd_number) {
    const auto first = args[0]->GetPointAPI();
    const auto second = args[1]->GetPointAPI();
    const auto speed = args[2]->GetSpeedAPI();
    const auto tool = args[3]->GetToolAPI();
    const auto wobj = args[4]->GetWobjAPI();
    const bool run_action = args[5]->GetBoolVal();

    // ignore_cmd_number集合可以跳过对应索引的子指令
    // 索引从 0 开始；返回向量仍需要保留三个执行体，与子配置一一对应。
    if (!run_action) {
        //如：run_action为false时，可以跳过指令索引为1的子指令
        ignore_cmd_number.insert(1);
    }

    // 子指令 0：运动到第一个目标点。
    CommandExecuteAPI first_move = [=]() -> CommandProcessResultAPI {
        MotionCmdArgsAPI motion;
        motion.SetTargetPoint(first);
        motion.SetMoveType(MoveTypeAPI::MOVE_L);
        motion.SetSpeed(speed);
        motion.SetTool(tool);
        motion.SetWobj(wobj);
        // 零转弯区，保证在第一个点精确到位。
        motion.SetZone(ZoneAPI());
        motion.SetUpdatePointer(frame->GetCmdTask(), frame->GetCmdFile(), frame->GetCmdLine());
        motion.SetCallback(CallBackTypeAPI::MOVE_FINISH, []() {
            LOG_INFO << "PMultiMoveL phase 0 motion finished";
        });

        MotionCmdAPI api;
        const int ret = api.SendCmd(motion);
        if (ret != 0) {
            LOG_ERROR << "PMultiMoveL phase 0 SendCmd failed: " << ret;
            return CommandProcessResultAPI::CMD_PROCESS_ERROR;
        }
        // 提交成功后由运动模块继续执行，因此返回 EXTRA。
        return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
    };

    // 子指令 1：打印当前 RL 语句所在的任务、文件和行号。
    CommandExecuteAPI action = [=]() -> CommandProcessResultAPI {
        LOG_INFO << "PMultiMoveL phase 1 action at " << frame->GetCmdTask()
                 << " " << frame->GetCmdFile() << ":" << frame->GetCmdLine();
		// 可以执行一些自定义动作
        // 动作已完成，返回 SUCCESS 继续调度。
        return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
    };

    // 子指令 2：运动到第二个目标点。
    CommandExecuteAPI second_move = [=]() -> CommandProcessResultAPI {
        MotionCmdArgsAPI motion;
        motion.SetTargetPoint(second);
        motion.SetMoveType(MoveTypeAPI::MOVE_L);
        motion.SetSpeed(speed);
        motion.SetTool(tool);
        motion.SetWobj(wobj);
        motion.SetZone(ZoneAPI());
        motion.SetUpdatePointer(frame->GetCmdTask(), frame->GetCmdFile(), frame->GetCmdLine());
        motion.SetCallback(CallBackTypeAPI::MOVE_FINISH, []() {
            LOG_INFO << "PMultiMoveL phase 2 motion finished";
        });

        MotionCmdAPI api;
        const int ret = api.SendCmd(motion);
        if (ret != 0) {
            LOG_ERROR << "PMultiMoveL phase 2 SendCmd failed: " << ret;
            return CommandProcessResultAPI::CMD_PROCESS_ERROR;
        }
        return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
    };

    // 顺序与下面注册时的三个子指令配置保持一致。
    return {first_move, action, second_move};
}
} // namespace

// 注册分两部分：先声明主指令和子指令的配置，再绑定参数与执行体。
void RegMultiMoveL() {
    // 1. 声明 RL 中可调用的指令名 PMultiMoveL，并设置任务限制和步退方式。
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("PMultiMoveL");
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF);
    cfg.SetTaskLimit(TaskLimitAPI::TASK_LIMIT_MOVE); 
    cfg.SetStepBack(StepBackAPI::STEP_BACK_STOP); 

    // 2. 每个子指令单独配置前瞻方式，排列顺序与返回的执行体一致。


    //运动到第一个目标点
    RLCmdConfigAPI first_cfg;
    first_cfg.SetFuncName("PMultiMoveL_First");
    first_cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF);
    first_cfg.SetTaskLimit(TaskLimitAPI::TASK_LIMIT_MOVE);
    first_cfg.SetStepBack(StepBackAPI::STEP_BACK_STOP);

    //可断前瞻执行其他逻辑
    RLCmdConfigAPI action_cfg;
    action_cfg.SetFuncName("PMultiMoveL_Action");
    action_cfg.SetLookAhead(CmdLookAheadImplAPI::WAIT_MOVE_PAUSE);
    action_cfg.SetTaskLimit(TaskLimitAPI::TASK_LIMIT_MOVE);
    action_cfg.SetStepBack(StepBackAPI::STEP_BACK_STOP);

    //运动到第二个目标点
    RLCmdConfigAPI second_cfg;
    second_cfg.SetFuncName("PMultiMoveL_Second");
    second_cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF);
    second_cfg.SetTaskLimit(TaskLimitAPI::TASK_LIMIT_MOVE);
    second_cfg.SetStepBack(StepBackAPI::STEP_BACK_STOP);

    // 3. 将主配置和有序的子配置传给多指令构造接口
    std::vector<RLCmdConfigAPI> sub_configs = {first_cfg, action_cfg, second_cfg};
    BEGIN_MULTIPLE_COMMAND_API(cfg, sub_configs)

    // 4. 声明 RL 调用参数，顺序对应 expandMultiMove 中的 args 下标。
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET), // args[0]：第一个目标点。
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET), // args[1]：第二个目标点。
        ArgTypeAPI(ValueTypeAPI::VALUE_SPEED),     // args[2]：两段运动的速度。
        ArgTypeAPI(ValueTypeAPI::VALUE_TOOL),      // args[3]：工具坐标。
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ),      // args[4]：工件坐标。
        ArgTypeAPI(ValueTypeAPI::VALUE_BOOL)       // args[5]：是否执行中间的打印动作。
    )
    // 5. 绑定返回多个执行体的回调，并向控制器注册。
    RLCmdMultipleActionAPI exec = expandMultiMove;
    EXECUTE_MULTIPLE_API(exec)
    REGISTER_COMMAND_API
}
} // namespace multiple_cmd
#else
namespace multiple_cmd {
void RegMultiMoveL() {
    //缺少对应宏定义
    LOG_WARNING << "PMultiMoveL not registered: xcore_api lacks multiple-command support";
}
} // namespace multiple_cmd
#endif

void MultipleCmdExampleInit() {
    multiple_cmd::RegMultiMoveL();
}

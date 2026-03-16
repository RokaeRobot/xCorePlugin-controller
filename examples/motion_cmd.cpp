/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file motion_cmd.hpp
 * @brief 测试各个运动指令的使用功能
 */
#include "log/log_api.hpp"
#include "motion_cmd.hpp"


namespace motion_cmd {
using namespace xcore_api::motion_cmd;
using namespace xcore_api::rl_cmd;
using namespace xcore_api::const_data::pose;

void RegPMoveAbsj() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmoveabsj");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);

    //根据配置创建指令
    BEGIN_COMMAND_API(cfg)
    //为指令配置参数检查器
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_JOINTTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_SPEED),
        ArgTypeAPI(ValueTypeAPI::VALUE_ZONE),
        ArgTypeAPI(ValueTypeAPI::VALUE_TOOL),
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ)
    )
    //指令正向执行体
    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        //获取参数数据
        auto point = args[0]->GetPointAPI();
        auto speed = args[1]->GetSpeedAPI();
        auto zone = args[2]->GetZoneAPI();
        auto tool = args[3]->GetToolAPI();
        auto wobj = args[4]->GetWobjAPI();

        CommandExecuteAPI cmd_exec = [=]() {
            MotionCmdArgsAPI args_api;
            //设置目标点
            args_api.SetTargetPoint(point);
            //设置运动类型为关节运动
            args_api.SetMoveType(MoveTypeAPI::MOVE_ABSJ);
            //设置工具工具速度转弯区域信息
            args_api.SetTool(tool);
            args_api.SetWobj(wobj);
            args_api.SetZone(zone);
            args_api.SetSpeed(speed);
            //设置解释当前执行位置的指针
            args_api.SetUpdatePointer(frame->GetCmdTask(), frame->GetCmdFile(), frame->GetCmdLine());
            //设置trigger
            TriggerAPI t;
            t.type = TriggerAPI::TriggerType::DISTANCE;
            t.reference_is_from_start = true;
            t.value_from_reference = 0.1;
            t.trigger_callback = [frame]
            {
                LOG_DEBUG<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine()<<" 100mm trigger callback";
            };
            args_api.SetTriggers({t});
            //设置路径的回调
            args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG_INFO<<"moveabsj start callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG_INFO<<"moveabsj finish callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG_INFO<<"moveabsj pause callback";});
            MotionCmdAPI api;
            //发送指令
            int ret = api.SendCmd(args_api);
            LOG_INFO<<"send motion cmd:"<<ret;
            LOG_DEBUG<<"point:"<<point<<" speed:"<< speed<<" zone:"<< zone
                <<" tool:"<<tool<<" wobj:"<< wobj;

            if (ret == 0){
                return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
            }else{
                return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            }   
        };
        return cmd_exec;
    };
    
    EXECUTE_API(cmd_func)

    REGISTER_COMMAND_API
}

void RegPMoveL() {
    // 1.指令配置，如名称、触发方式、任务限制等
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovel");
    //设置指令前瞻方式为运动指令
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_CUSTOM);

    // 2.根据配置创建指令
    BEGIN_COMMAND_API(cfg)

    // 3.为指令配置参数检查器
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_SPEED),
        ArgTypeAPI(ValueTypeAPI::VALUE_ZONE),
        ArgTypeAPI(ValueTypeAPI::VALUE_TOOL),
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ)
    )

    // 4.指令正向执行体
    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        // 获取参数数据
        auto point = args[0]->GetPointAPI();
        auto speed = args[1]->GetSpeedAPI();
        auto zone = args[2]->GetZoneAPI();
        auto tool = args[3]->GetToolAPI();
        auto wobj = args[4]->GetWobjAPI();

        CommandExecuteAPI cmd_exec = [=]()
        {
            MotionCmdArgsAPI args_api;
            // 设置目标点
            args_api.SetTargetPoint(point);
            // 设置运动类型为直线
            args_api.SetMoveType(MoveTypeAPI::MOVE_L);
            // 设置工具工具速度转弯区域信息
            args_api.SetTool(tool);
            args_api.SetWobj(wobj);
            args_api.SetZone(zone);
            args_api.SetSpeed(speed);
            // 设置解释当前执行位置的指针
            args_api.SetUpdatePointer(frame->GetCmdTask(), frame->GetCmdFile(), frame->GetCmdLine());
            // 设置trigger
            TriggerAPI t;
            t.type = TriggerAPI::TriggerType::DISTANCE;
            t.reference_is_from_start = true;
            t.value_from_reference = 0.1;
            t.trigger_callback = [=]
            {
                LOG_DEBUG<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine()<<" 100mm trigger callback";
            };
            args_api.SetTriggers({t});
            // 设置路径的回调
            args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG_INFO<<"movel start callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG_INFO<<"movel finish callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG_INFO<<"movel pause callback";});
            MotionCmdAPI api;
            // 发送指令
            int ret = api.SendCmd(args_api);
            LOG_INFO<<"send motion cmd:"<<ret;
            LOG_DEBUG<<"point:"<<point<<" speed:"<<speed<<" zone:"<<zone
                <<" tool:"<<tool<<" wobj:"<<wobj;

            LOG_DEBUG<<":"<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine();
            if (ret == 0){
                return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
            }else{
                return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            }
        };
        return cmd_exec;
    };
    EXECUTE_API(cmd_func)

    // 5.将指令注册给控制器
    REGISTER_COMMAND_API
}

void RegPMoveC() {
    // 1.指令配置，如名称、触发方式、任务限制等
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovec");
    //设置指令前瞻方式为运动指令
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_CUSTOM);

    // 2.根据配置创建指令
    BEGIN_COMMAND_API(cfg)

    // 3.为指令配置参数检查器
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_SPEED),
        ArgTypeAPI(ValueTypeAPI::VALUE_ZONE),
        ArgTypeAPI(ValueTypeAPI::VALUE_TOOL),
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ)
    )

    // 4.指令正向执行体
    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        // 获取参数数据
        auto aux = args[0]->GetPointAPI();
        auto point = args[1]->GetPointAPI();
        auto speed = args[2]->GetSpeedAPI();
        auto zone = args[3]->GetZoneAPI();
        auto tool = args[4]->GetToolAPI();
        auto wobj = args[5]->GetWobjAPI();

        CommandExecuteAPI cmd_exec = [=](){
            MotionCmdArgsAPI args_api;
            // 设置目标点
            args_api.SetTargetPoint(point);
            // 设置辅助点
            args_api.SetAuxPoint(aux);
            // 设置运动类型为圆弧
            args_api.SetMoveType(MoveTypeAPI::MOVE_C);
            // 设置工具工具速度转弯区域信息
            args_api.SetTool(tool);
            args_api.SetWobj(wobj);
            args_api.SetZone(zone);
            args_api.SetSpeed(speed);
            // 设置解释当前执行位置的指针
            args_api.SetUpdatePointer(frame->GetCmdTask(),frame->GetCmdFile(),frame->GetCmdLine());
            // 设置trigger
            TriggerAPI t;
            t.type = TriggerAPI::TriggerType::TIME;
            t.reference_is_from_start = true;
            t.value_from_reference = 0.1;
            t.trigger_callback = [=]
            {
                LOG_DEBUG<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine()<<" time trigger callback";
            };
            args_api.SetTriggers({t});
            // 设置路径的回调
            args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG_INFO<<"movec start callback"; });
            args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG_INFO<<"movec finish callback"; });
            args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG_INFO<<"movec pause callback"; });
            MotionCmdAPI api;
            // 发送指令
            int ret = api.SendCmd(args_api);
            LOG_INFO<<"send motion cmd:"<<ret;
            LOG_DEBUG<<"point:"<<point<<" aux:"<<aux<<" speed:"<<speed<<" zone:"<<zone
                <<" tool:"<<tool<<" wobj:"<<wobj;
            LOG_DEBUG<<":"<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine();
            if (ret == 0){
                return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
            }else{
                return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            }
        };
        return cmd_exec;
    };
    EXECUTE_API(cmd_func)

    // 5.将指令注册给控制器
    REGISTER_COMMAND_API
}

void RegPMoveCF() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovecf");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_CUSTOM);
    BEGIN_COMMAND_API(cfg)
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_DOUBLE),
        ArgTypeAPI(ValueTypeAPI::VALUE_STRING),
        ArgTypeAPI(ValueTypeAPI::VALUE_SPEED),
        ArgTypeAPI(ValueTypeAPI::VALUE_ZONE),
        ArgTypeAPI(ValueTypeAPI::VALUE_TOOL),
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ)
    )

    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        auto aux = args[0]->GetPointAPI();
        auto point = args[1]->GetPointAPI();

        auto deg = args[2]->GetDoubleVal();
        auto rottype = args[3]->GetStringVal();

        auto speed = args[4]->GetSpeedAPI();
        auto zone = args[5]->GetZoneAPI();
        auto tool = args[6]->GetToolAPI();
        auto wobj = args[7]->GetWobjAPI();

        CommandExecuteAPI cmd_exec = [=](){
            MotionCmdArgsAPI args_api;
            // 设置目标点
            args_api.SetTargetPoint(point);
            // 设置辅助点
            args_api.SetAuxPoint(aux);
            // 设置运动类型为圆弧
            args_api.SetMoveType(MoveTypeAPI::MOVE_CF);
            RotTypeAPI type;
            if(rottype == "RotAxis"){
                type = RotTypeAPI::ROT_AXIS;
            } else if(rottype == "ConstPose"){
                type = RotTypeAPI::CONST_POSE;
            } else {
                type = RotTypeAPI::FIXED_AXIS;
            }
            args_api.SetMoveCFData(type,deg);
            // 设置工具工具速度转弯区域信息
            args_api.SetTool(tool);
            args_api.SetWobj(wobj);
            args_api.SetZone(zone);
            args_api.SetSpeed(speed);
            // 设置解释当前执行位置的指针
            args_api.SetUpdatePointer(frame->GetCmdTask(), frame->GetCmdFile(), frame->GetCmdLine());
            // 设置trigger
            TriggerAPI t;
            t.type = TriggerAPI::TriggerType::TIME;
            t.reference_is_from_start = true;
            t.value_from_reference = 0.1;
            t.trigger_callback = [=]{
                LOG_DEBUG<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine()<<" time trigger callback";
            };
            args_api.SetTriggers({t});
            // 设置路径的回调
            args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG_INFO<<"movecf start callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG_INFO<<"movecf finish callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG_INFO<<"movecf pause callback";});
            MotionCmdAPI api;
            int ret = api.SendCmd(args_api);
            LOG_INFO<<"send motion cmd movecf:"<<ret;
            LOG_INFO<<"point:"<<point<<" aux:"<<aux<<" speed:"<<speed<<" zone:"<<zone
                <<" tool:"<<tool<<" wobj:"<<wobj;

            LOG_INFO<<"MoveCF:"<<rottype<<" : "<<deg;

            LOG_INFO<<":"<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine();
            if (ret == 0){
                return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
            }else{
                return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            }
        };
        return cmd_exec;
    };
    EXECUTE_API(cmd_func)
    REGISTER_COMMAND_API
}   

void RegPMoveJ() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovej");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);
    BEGIN_COMMAND_API(cfg)
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_SPEED),
        ArgTypeAPI(ValueTypeAPI::VALUE_ZONE),
        ArgTypeAPI(ValueTypeAPI::VALUE_TOOL),
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ)
    )

    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        auto point = args[0]->GetPointAPI();
        auto speed = args[1]->GetSpeedAPI();
        auto zone = args[2]->GetZoneAPI();
        auto tool = args[3]->GetToolAPI();
        auto wobj = args[4]->GetWobjAPI();

        CommandExecuteAPI cmd_exec = [=](){
            MotionCmdArgsAPI args_api;
            // 设置目标点
            args_api.SetTargetPoint(point);
            // 设置运动类型为关节运动
            args_api.SetMoveType(MoveTypeAPI::MOVE_J);
            // 设置工具工具速度转弯区域信息
            args_api.SetTool(tool);
            args_api.SetWobj(wobj);
            args_api.SetZone(zone);
            args_api.SetSpeed(speed);
            // 设置解释当前执行位置的指针
            args_api.SetUpdatePointer(frame->GetCmdTask(), frame->GetCmdFile(), frame->GetCmdLine());
            // 设置trigger
            TriggerAPI t;
            t.type = TriggerAPI::TriggerType::DISTANCE;
            t.reference_is_from_start = true;
            t.value_from_reference = 0.01;
            t.trigger_callback = [=]{
                LOG_DEBUG<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine()<<" 10mm trigger callback";
            };
            args_api.SetTriggers({t});
            // 设置路径的回调
            args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG_INFO<<"movej start callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG_INFO<<"movej finish callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG_INFO<<"movej pause callback";});
            MotionCmdAPI api;
            int ret = api.SendCmd(args_api);
            LOG_INFO<<"send motion cmd movej:"<<ret;

            LOG_DEBUG<<":"<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine();
            if (ret == 0){
                return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
            } else {
                return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            }
        };
        return cmd_exec;
    };
    EXECUTE_API(cmd_func)
    REGISTER_COMMAND_API
}

void RegPSegMoveL() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("psegmoveL");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::WAIT_MOVE_PAUSE) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);
    //根据配置创建指令
    BEGIN_COMMAND_API(cfg)
    //为指令配置参数检查器
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_SPEED),
        ArgTypeAPI(ValueTypeAPI::VALUE_ZONE),
        ArgTypeAPI(ValueTypeAPI::VALUE_TOOL),
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ)
    )
    //指令正向执行体
    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        auto point = args[0]->GetPointAPI();
        auto speed = args[1]->GetSpeedAPI();
        auto zone = args[2]->GetZoneAPI();
        auto tool = args[3]->GetToolAPI();
        auto wobj = args[4]->GetWobjAPI();

        CommandExecuteAPI cmd_exec = [=](){
            std::vector<MotionCmdArgsAPI>v;
            for(int i = 0;i<4;++i){
                MotionCmdArgsAPI args_api;
                auto p = point;
                p.pose.p.x -= (3-i)*0.02;
                args_api.SetTargetPoint(p);

                args_api.SetMoveType(MoveTypeAPI::MOVE_L);
                args_api.SetTool(tool);

                args_api.SetWobj(wobj);
                args_api.SetZone(zone);
                args_api.SetSpeed(speed);
                args_api.SetUpdatePointer(frame->GetCmdTask(),frame->GetCmdFile(),frame->GetCmdLine());
                //设置trigger
                TriggerAPI t;
                t.type = TriggerAPI::TriggerType::DISTANCE;
                t.reference_is_from_start = true;
                t.value_from_reference = 0.1;
                t.trigger_callback = [=]{
                    LOG_DEBUG<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine()<<" 100mm trigger callback";
                };
                args_api.SetTriggers({t});
                args_api.SetCallback(CallBackTypeAPI::MOVE_START,[i]{LOG_INFO<<"segmovel start callback";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(i %2 == 0)
                        LOG_INFO<<"simu test on "<<i;
                    else
                        LOG_INFO<<"simu nothing on "<<i;
                });
                args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[i]{LOG_INFO<<"segmovel finish callback 1";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(i %2 == 0)
                        LOG_INFO<<"simu test off "<<i;
                    else
                        LOG_INFO<<"simu nothing off"<<i;
                });
                args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG_INFO<<"segmovel pause callback";});
                v.push_back(args_api);
            }
            MotionCmdAPI api;
            int ret = api.SendSegmentCmds(v);
            LOG_DEBUG<<"point:"<<point<<" speed:"<<speed<<" zone:"<<zone
                <<" tool:"<<tool<<" wobj:"<<wobj;
            LOG_DEBUG<<":"<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine();
            if(ret == 0){
                return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
            } else {
                return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            }
        };
        return cmd_exec;
    };
    EXECUTE_API(cmd_func)
    //将指令注册给控制器
    REGISTER_COMMAND_API
}

void RegPMoveBackL() {
     RLCmdConfigAPI cfg;
    cfg.SetFuncName("psegmoveL");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    //cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);
    BEGIN_COMMAND_API(cfg)
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_SPEED),
        ArgTypeAPI(ValueTypeAPI::VALUE_ZONE),
        ArgTypeAPI(ValueTypeAPI::VALUE_TOOL),
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ)
    )
    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        auto point = args[0]->GetPointAPI();
        auto speed = args[1]->GetSpeedAPI();
        auto zone = args[2]->GetZoneAPI();
        auto tool = args[3]->GetToolAPI();
        auto wobj = args[4]->GetWobjAPI();

        CommandExecuteAPI cmd_exec = [=](){
            MotionCmdArgsAPI args_api;
            args_api.SetTargetPoint(point);

            args_api.SetMoveType(MoveTypeAPI::MOVE_L);
            args_api.SetTool(tool);

            args_api.SetWobj(wobj);
            args_api.SetZone(zone);
            args_api.SetSpeed(speed);
            //步退使用visited line，步退是从后往前解释
            args_api.SetUpdatePointer(frame->GetCmdTask(),frame->GetCmdFile(),frame->GetVisitedLine());
            //设置trigger
            TriggerAPI t;
            t.type = TriggerAPI::TriggerType::DISTANCE;
            t.reference_is_from_start = true;
            t.value_from_reference = 0.1;
            t.trigger_callback = [=]{
                LOG_DEBUG <<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetVisitedLine()<<" 100mm trigger callback";
            };
            args_api.SetTriggers({t});
            args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG_INFO<<"movebackl start callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG_INFO<<"movebackl finish callback";});
            args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG_INFO<<"movebackl pause callback";});
            MotionCmdAPI api;
            int ret = api.SendStepBackCmd(args_api);
            LOG_INFO<<"send motion cmd:"<<ret;
            LOG_DEBUG<<"point:"<<point<<" speed:"<<speed<<" zone:"<<zone
                <<" tool:"<<tool<<" wobj:"<<wobj;

            LOG_DEBUG <<":"<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetVisitedLine();
            if(ret == 0){
                return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
            } else {
                return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            }
        };
        return cmd_exec;
    };
    EXECUTE_API(cmd_func)
    REGISTER_COMMAND_API
    
}

void RegPMoveBackC() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovec");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    //cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);
    BEGIN_COMMAND_API(cfg)
    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_SPEED),
        ArgTypeAPI(ValueTypeAPI::VALUE_ZONE),
        ArgTypeAPI(ValueTypeAPI::VALUE_TOOL),
        ArgTypeAPI(ValueTypeAPI::VALUE_WOBJ)
    )
    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        auto aux = args[0]->GetPointAPI();
        auto point = args[1]->GetPointAPI();
        auto speed = args[2]->GetSpeedAPI();
        auto zone = args[3]->GetZoneAPI();
        auto tool = args[4]->GetToolAPI();
        auto wobj = args[5]->GetWobjAPI();

        CommandExecuteAPI cmd_exec = [=](){
            MotionCmdArgsAPI args_api;
            // 设置目标点
            args_api.SetTargetPoint(point);
            // 设置辅助点
            args_api.SetAuxPoint(aux);
            // 设置运动类型为圆弧
            args_api.SetMoveType(MoveTypeAPI::MOVE_C);
            // 设置工具工具速度转弯区域信息
            args_api.SetTool(tool);
            args_api.SetWobj(wobj);
            args_api.SetZone(zone);
            args_api.SetSpeed(speed);
            // 设置解释当前执行位置的指针
            args_api.SetUpdatePointer(frame->GetCmdTask(), frame->GetCmdFile(), frame->GetCmdLine());
            // 设置trigger
            TriggerAPI t;
            t.type = TriggerAPI::TriggerType::TIME;
            t.reference_is_from_start = true;
            t.value_from_reference = 0.1;
            t.trigger_callback = [=]{
                LOG_DEBUG<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine()<<" time trigger callback";
            };
            args_api.SetTriggers({t});
            // 设置路径的回调
            args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG_INFO<<"movec start callback"; });
            args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG_INFO<<"movec finish callback"; });
            args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG_INFO<<"movec pause callback"; });
            MotionCmdAPI api;
            // 发送指令
            int ret = api.SendStepBackCmd(args_api);
            LOG_INFO<<"send motion cmd:"<<ret;
            LOG_DEBUG<<"point:"<<point<<" aux:"<<aux<<" speed:"<<speed<<" zone:"<<zone
                <<" tool:"<<tool<<" wobj:"<<wobj;
            LOG_DEBUG<<":"<<frame->GetCmdTask()<<" "<<frame->GetCmdFile()<<" "<<frame->GetCmdLine();
            if (ret == 0){
                return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
            }
            else
            {
                return CommandProcessResultAPI::CMD_PROCESS_ERROR;
            }
        };
        return cmd_exec;
    };
    EXECUTE_API(cmd_func)
    REGISTER_COMMAND_API
}

void RegPPoseXPose() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pposexpose");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::WAIT_MOVE_PAUSE) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置步退的类型
    //cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);
    BEGIN_COMMAND_API(cfg)

    PARAMS_API(
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET),
        ArgTypeAPI(ValueTypeAPI::VALUE_ROBTARGET)
    )
    RLCmdActionAPI cmd_func = [=](std::shared_ptr<RLCallFrameAPI> frame,
        std::vector<std::shared_ptr<SymbolVarBaseAPI>> args) -> CommandExecuteAPI {
        auto point = args[0]->GetPointAPI();
        auto aux = args[1]->GetPointAPI();
        CommandExecuteAPI cmd_exec = [=](){auto ret = point;
        ret.pose = point.pose * aux.pose;
        SymbolVarBaseAPI var;
        var.ResetRobTarget(ret);
        //设置返回值
        frame->SetReturnValue(var);
        LOG_DEBUG<<"point:"<<point<<" aux:"<<aux<<"ret:"<<ret;
        LOG_DEBUG<<"inverse:"<<point.pose.Inverse()<<" p*-p:"<<point.pose*point.pose.Inverse();
        return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
    };
        return cmd_exec; 
    };
    EXECUTE_API(cmd_func)

    REGISTER_COMMAND_API

}
}


void MotionCmdExampleInit(){
    using namespace motion_cmd;
    RegPMoveAbsj();
    RegPMoveL();
    RegPMoveC();
    RegPMoveCF();
    RegPMoveJ();
    RegPSegMoveL();
    RegPMoveBackC();
    RegPMoveBackL();
    RegPPoseXPose();
}


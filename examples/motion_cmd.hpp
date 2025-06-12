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
#pragma once
#include <g3log/g3log.hpp>
#include "rl_cmd/morden_rl_cmd_api.hpp"
#include "motion_cmd/motion_cmd_api.hpp"

namespace motion_cmd {
using namespace xcore_api::motion_cmd;
using namespace xcore_api::rl_cmd;
using namespace xcore_api::const_data::pose;

/**
 * @brief 实现指令PMoveAbsj
 */
DECLARE_MORDEN_RLCMD_API(PMoveAbsj);

MORDERN_CMD_ARGS_API(PMoveAbsj) {
    std::vector<ArgTypeAPI>v;
    //必选参数rob，可选wobj和string
    v.emplace_back(ValueTypeAPI::VALUE_JOINTTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_SPEED,true);
    v.emplace_back(ValueTypeAPI::VALUE_ZONE,true);
    v.emplace_back(ValueTypeAPI::VALUE_TOOL,true);
    v.emplace_back(ValueTypeAPI::VALUE_WOBJ,false);
    return RequireArgsAPI(v);
}

MORDERN_CMD_EXECUTE_API(PMoveAbsj) {
    cmdExecute_t result = [=] {
        auto args = GetCmdArgs();

        auto point = args[0].GetPointAPI();
        auto speed = args[1].GetSpeedAPI();
        auto zone = args[2].GetZoneAPI();
        auto tool = args[3].GetToolAPI();
        auto wobj = args[4].GetWobjAPI();

        MotionCmdArgsAPI args_api;
        //设置目标点
        args_api.SetTargetPoint(point);

        args_api.SetMoveType(MoveTypeAPI::MOVE_ABSJ);
        //设置工件工具速度转弯区等信息
        args_api.SetTool(tool);
        args_api.SetWobj(wobj);
        args_api.SetZone(zone);
        args_api.SetSpeed(speed);
        //设置指令更新运动指针
        args_api.SetUpdatePointer(GetCmdTask(),GetCmdFile(),GetCmdLine());
        //在轨迹的起始添加回调函数
        args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG(INFO)<<"moveabsj start callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG(INFO)<<"moveabsj finish callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG(INFO)<<"moveabsj pause callback";});
        MotionCmdAPI api;
        //发送指令
        int ret = api.SendCmd(args_api);
        LOG(INFO)<<"send motion cmd:"<<ret;
        DLOG(INFO)<<"point:"<<point<<" speed:"<<speed<<" zone:"<<zone
            <<" tool:"<<tool<<" wobj:"<<wobj;
        if(ret == 0){
            return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
        } else {
            return CommandProcessResultAPI::CMD_PROCESS_ERROR;
        }
    };
    return result;
}


std::shared_ptr<ModernRLCmdAPI> makePMoveAbsj() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmoveabsj");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置指令是否需要括号
    cfg.SetRequireBracket(false);
    //函数的返回值类型
    cfg.SetReturnType(ValueTypeAPI::VALUE_DOUBLE);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);

    return std::make_shared<PMoveAbsj>(cfg);
}

/**
 * @brief 实现指令PMoveL
 */
DECLARE_MORDEN_RLCMD_API(PMoveL);

MORDERN_CMD_ARGS_API(PMoveL) {
    std::vector<ArgTypeAPI>v;
    //必选参数rob，可选wobj和string
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_SPEED,true);
    v.emplace_back(ValueTypeAPI::VALUE_ZONE,true);
    v.emplace_back(ValueTypeAPI::VALUE_TOOL,true);
    v.emplace_back(ValueTypeAPI::VALUE_WOBJ,false);
    return RequireArgsAPI(v);
}

MORDERN_CMD_EXECUTE_API(PMoveL) {
    cmdExecute_t result = [=] {
        auto args = GetCmdArgs();
        //获取参数数据
        auto point = args[0].GetPointAPI();
        auto speed = args[1].GetSpeedAPI();
        auto zone = args[2].GetZoneAPI();
        auto tool = args[3].GetToolAPI();
        auto wobj = args[4].GetWobjAPI();

        MotionCmdArgsAPI args_api;
        //设置目标点
        args_api.SetTargetPoint(point);
        //设置运动类型为直线
        args_api.SetMoveType(MoveTypeAPI::MOVE_L);
        //设置工具工具速度转弯区域信息
        args_api.SetTool(tool);
        args_api.SetWobj(wobj);
        args_api.SetZone(zone);
        args_api.SetSpeed(speed);
        //设置解释当前执行位置的指针
        args_api.SetUpdatePointer(GetCmdTask(),GetCmdFile(),GetCmdLine());
        //设置trigger
        TriggerAPI t;
        t.type = TriggerAPI::TriggerType::DISTANCE;
        t.reference_is_from_start = true;
        t.value_from_reference = 0.1;
        t.trigger_callback = [this]{
            DLOG(INFO) <<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetCmdLine()<<" 100mm trigger callback";
        };
        args_api.SetTriggers({t});
        //设置路径的回调
        args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG(INFO)<<"movel start callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG(INFO)<<"movel finish callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG(INFO)<<"movel pause callback";});
        MotionCmdAPI api;
        //发送指令
        int ret = api.SendCmd(args_api);
        LOG(INFO)<<"send motion cmd:"<<ret;
         DLOG(INFO)<<"point:"<<point<<" speed:"<<speed<<" zone:"<<zone
            <<" tool:"<<tool<<" wobj:"<<wobj;

        DLOG(INFO) <<":"<<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetCmdLine();
        if(ret == 0){
            return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
        } else {
            return CommandProcessResultAPI::CMD_PROCESS_ERROR;
        }
    };
    return result;
}


std::shared_ptr<ModernRLCmdAPI> makePMoveL() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovel");
    //设置指令前瞻方式为运动指令
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置指令不需要括号
    cfg.SetRequireBracket(false);
    //函数的返回值类型
    cfg.SetReturnType(ValueTypeAPI::VALUE_DOUBLE);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_CUSTOM);

    return std::make_shared<PMoveL>(cfg);
}


/**
 * @brief 实现指令PMoveC
 */
DECLARE_MORDEN_RLCMD_API(PMoveC);

MORDERN_CMD_ARGS_API(PMoveC) {
    std::vector<ArgTypeAPI>v;
    //必选参数rob，可选wobj和string
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_SPEED,true);
    v.emplace_back(ValueTypeAPI::VALUE_ZONE,true);
    v.emplace_back(ValueTypeAPI::VALUE_TOOL,true);
    v.emplace_back(ValueTypeAPI::VALUE_WOBJ,false);
    return RequireArgsAPI(v);
}

MORDERN_CMD_EXECUTE_API(PMoveC) {
    cmdExecute_t result = [=] {
        auto args = GetCmdArgs();

        auto aux = args[0].GetPointAPI();
        auto point = args[1].GetPointAPI();
        auto speed = args[2].GetSpeedAPI();
        auto zone = args[3].GetZoneAPI();
        auto tool = args[4].GetToolAPI();
        auto wobj = args[5].GetWobjAPI();

        MotionCmdArgsAPI args_api;
        args_api.SetTargetPoint(point);
        args_api.SetAuxPoint(aux);

        args_api.SetMoveType(MoveTypeAPI::MOVE_C);
        args_api.SetTool(tool);

        args_api.SetWobj(wobj);
        args_api.SetZone(zone);
        args_api.SetSpeed(speed);
        args_api.SetUpdatePointer(GetCmdTask(),GetCmdFile(),GetCmdLine());
        //设置trigger
        TriggerAPI t;
        t.type = TriggerAPI::TriggerType::TIME;
        t.reference_is_from_start = true;
        t.value_from_reference = 0.1;
        t.trigger_callback = [this]{
            DLOG(INFO) <<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetCmdLine()<<" time trigger callback";
        };
        args_api.SetTriggers({t});
        args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG(INFO)<<"movec callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG(INFO)<<"movec finish callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG(INFO)<<"movec pause callback";});
        MotionCmdAPI api;
        int ret = api.SendCmd(args_api);
        LOG(INFO)<<"send motion cmd:"<<ret;
        DLOG(INFO)<<"point:"<<point<<" aux:"<<aux<<" speed:"<<speed<<" zone:"<<zone
            <<" tool:"<<tool<<" wobj:"<<wobj;

        DLOG(INFO) <<":"<<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetCmdLine();
        if(ret == 0){
            return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
        } else {
            return CommandProcessResultAPI::CMD_PROCESS_ERROR;
        }
    };
    return result;
}


std::shared_ptr<ModernRLCmdAPI> makePMoveC() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovec");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置指令是否需要括号
    cfg.SetRequireBracket(false);
    //函数的返回值类型
    cfg.SetReturnType(ValueTypeAPI::VALUE_DOUBLE);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_CUSTOM);

    return std::make_shared<PMoveC>(cfg);
}


/**
 * @brief 实现指令PMoveJ
 */
DECLARE_MORDEN_RLCMD_API(PMoveJ);

MORDERN_CMD_ARGS_API(PMoveJ) {
    std::vector<ArgTypeAPI>v;
    //必选参数rob，可选wobj和string
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_SPEED,true);
    v.emplace_back(ValueTypeAPI::VALUE_ZONE,true);
    v.emplace_back(ValueTypeAPI::VALUE_TOOL,true);
    v.emplace_back(ValueTypeAPI::VALUE_WOBJ,false);
    return RequireArgsAPI(v);
}

MORDERN_CMD_EXECUTE_API(PMoveJ) {
    cmdExecute_t result = [=] {
        auto args = GetCmdArgs();

        auto point = args[0].GetPointAPI();
        auto speed = args[1].GetSpeedAPI();
        auto zone = args[2].GetZoneAPI();
        auto tool = args[3].GetToolAPI();
        auto wobj = args[4].GetWobjAPI();

        MotionCmdArgsAPI args_api;
        args_api.SetTargetPoint(point);

        args_api.SetMoveType(MoveTypeAPI::MOVE_J);
        args_api.SetTool(tool);

        args_api.SetWobj(wobj);
        args_api.SetZone(zone);
        args_api.SetSpeed(speed);
        args_api.SetUpdatePointer(GetCmdTask(),GetCmdFile(),GetCmdLine());
        //设置trigger
        TriggerAPI t;
        t.type = TriggerAPI::TriggerType::DISTANCE;
        t.reference_is_from_start = true;
        t.value_from_reference = 0.01;
        t.trigger_callback = [this]{
            DLOG(INFO) <<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetCmdLine()<<" 10mm trigger callback";
        };
        args_api.SetTriggers({t});
        args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG(INFO)<<"movej start callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG(INFO)<<"movej finish callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG(INFO)<<"movej pause callback";});
        MotionCmdAPI api;
        int ret = api.SendCmd(args_api);
        LOG(INFO)<<"send motion cmd movej:"<<ret;

        DLOG(INFO) <<":"<<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetCmdLine();
        if(ret == 0){
            return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
        } else {
            return CommandProcessResultAPI::CMD_PROCESS_ERROR;
        }
    };
    return result;
}


std::shared_ptr<ModernRLCmdAPI> makePMoveJ() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovej");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置指令是否需要括号
    cfg.SetRequireBracket(false);
    //函数的返回值类型
    cfg.SetReturnType(ValueTypeAPI::VALUE_DOUBLE);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);

    return std::make_shared<PMoveJ>(cfg);
}




/**
 * @brief 实现指令PSegMoveL
 */

DECLARE_MORDEN_RLCMD_API(PSegMoveL);

MORDERN_CMD_ARGS_API(PSegMoveL) {
    std::vector<ArgTypeAPI>v;
    //必选参数rob，可选wobj和string
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_SPEED,true);
    v.emplace_back(ValueTypeAPI::VALUE_ZONE,true);
    v.emplace_back(ValueTypeAPI::VALUE_TOOL,true);
    v.emplace_back(ValueTypeAPI::VALUE_WOBJ,false);
    return RequireArgsAPI(v);
}

MORDERN_CMD_EXECUTE_API(PSegMoveL) {
    cmdExecute_t result = [=] {
        auto args = GetCmdArgs();

        auto point = args[0].GetPointAPI();
        auto speed = args[1].GetSpeedAPI();
        auto zone = args[2].GetZoneAPI();
        auto tool = args[3].GetToolAPI();
        auto wobj = args[4].GetWobjAPI();

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
            args_api.SetUpdatePointer(GetCmdTask(),GetCmdFile(),GetCmdLine());
            //设置trigger
            TriggerAPI t;
            t.type = TriggerAPI::TriggerType::DISTANCE;
            t.reference_is_from_start = true;
            t.value_from_reference = 0.1;
            t.trigger_callback = [this]{
                DLOG(INFO) <<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetCmdLine()<<" 100mm trigger callback";
            };
            args_api.SetTriggers({t});
            args_api.SetCallback(CallBackTypeAPI::MOVE_START,[i]{LOG(INFO)<<"segmovel start callback";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if(i %2 == 0)
                    LOG(INFO)<<"simu test on "<<i;
                else
                    LOG(INFO)<<"simu nothing on "<<i;
            });
            args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[i]{LOG(INFO)<<"segmovel finish callback 1";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if(i %2 == 0)
                    LOG(INFO)<<"simu test off "<<i;
                else
                    LOG(INFO)<<"simu nothing off"<<i;
            });
            args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG(INFO)<<"segmovel pause callback";});
            v.push_back(args_api);
        }
        
        MotionCmdAPI api;
        int ret = api.SendSegmentCmds(v);


         DLOG(INFO)<<"point:"<<point<<" speed:"<<speed<<" zone:"<<zone
            <<" tool:"<<tool<<" wobj:"<<wobj;

        DLOG(INFO) <<":"<<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetCmdLine();
        if(ret == 0){
            return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
        } else {
            return CommandProcessResultAPI::CMD_PROCESS_ERROR;
        }
    };
    return result;
}


std::shared_ptr<ModernRLCmdAPI> makePSegMoveL() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("psegmoveL");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::WAIT_MOVE_PAUSE) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置指令是否需要括号
    cfg.SetRequireBracket(false);
    //函数的返回值类型
    cfg.SetReturnType(ValueTypeAPI::VALUE_DOUBLE);
    //设置步退的类型
    cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);

    return std::make_shared<PSegMoveL>(cfg);
}

/**
 * @brief 实现步退直线指令PMoveBackL
 */

DECLARE_MORDEN_RLCMD_API(PMoveBackL);

MORDERN_CMD_ARGS_API(PMoveBackL) {
    std::vector<ArgTypeAPI>v;
    //必选参数rob，可选wobj和string
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_SPEED,true);
    v.emplace_back(ValueTypeAPI::VALUE_ZONE,true);
    v.emplace_back(ValueTypeAPI::VALUE_TOOL,true);
    v.emplace_back(ValueTypeAPI::VALUE_WOBJ,false);
    return RequireArgsAPI(v);
}

MORDERN_CMD_EXECUTE_API(PMoveBackL) {
    cmdExecute_t result = [=] {
        auto args = GetCmdArgs();

        auto point = args[0].GetPointAPI();
        auto speed = args[1].GetSpeedAPI();
        auto zone = args[2].GetZoneAPI();
        auto tool = args[3].GetToolAPI();
        auto wobj = args[4].GetWobjAPI();

        MotionCmdArgsAPI args_api;
        args_api.SetTargetPoint(point);

        args_api.SetMoveType(MoveTypeAPI::MOVE_L);
        args_api.SetTool(tool);

        args_api.SetWobj(wobj);
        args_api.SetZone(zone);
        args_api.SetSpeed(speed);
        //步退使用visited line，步退是从后往前解释
        args_api.SetUpdatePointer(GetCmdTask(),GetCmdFile(),GetVisitedLine());
        //设置trigger
        TriggerAPI t;
        t.type = TriggerAPI::TriggerType::DISTANCE;
        t.reference_is_from_start = true;
        t.value_from_reference = 0.1;
        t.trigger_callback = [this]{
            DLOG(INFO) <<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetVisitedLine()<<" 100mm trigger callback";
        };
        args_api.SetTriggers({t});
        args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG(INFO)<<"movebackl start callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG(INFO)<<"movebackl finish callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG(INFO)<<"movebackl pause callback";});
        MotionCmdAPI api;
        int ret = api.SendStepBackCmd(args_api);
        LOG(INFO)<<"send motion cmd:"<<ret;
         DLOG(INFO)<<"point:"<<point<<" speed:"<<speed<<" zone:"<<zone
            <<" tool:"<<tool<<" wobj:"<<wobj;

        DLOG(INFO) <<":"<<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetVisitedLine();
        if(ret == 0){
            return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
        } else {
            return CommandProcessResultAPI::CMD_PROCESS_ERROR;
        }
    };
    return result;
}


std::shared_ptr<ModernRLCmdAPI> makePMoveBackL() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovel");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置指令是否需要括号
    cfg.SetRequireBracket(false);
    //函数的返回值类型
    cfg.SetReturnType(ValueTypeAPI::VALUE_DOUBLE);
    //设置步退的类型
    //cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);

    return std::make_shared<PMoveBackL>(cfg);
}


/**
 * @brief 实现步退指令PMoveBackC
 */
DECLARE_MORDEN_RLCMD_API(PMoveBackC);

MORDERN_CMD_ARGS_API(PMoveBackC) {
    std::vector<ArgTypeAPI>v;
    //必选参数rob，可选wobj和string
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_SPEED,true);
    v.emplace_back(ValueTypeAPI::VALUE_ZONE,true);
    v.emplace_back(ValueTypeAPI::VALUE_TOOL,true);
    v.emplace_back(ValueTypeAPI::VALUE_WOBJ,false);
    return RequireArgsAPI(v);
}

MORDERN_CMD_EXECUTE_API(PMoveBackC) {
    cmdExecute_t result = [=] {
        auto args = GetCmdArgs();

        auto aux = args[0].GetPointAPI();
        auto point = args[1].GetPointAPI();
        auto speed = args[2].GetSpeedAPI();
        auto zone = args[3].GetZoneAPI();
        auto tool = args[4].GetToolAPI();
        auto wobj = args[5].GetWobjAPI();

        MotionCmdArgsAPI args_api;
        args_api.SetTargetPoint(point);
        args_api.SetAuxPoint(aux);

        args_api.SetMoveType(MoveTypeAPI::MOVE_C);
        args_api.SetTool(tool);

        args_api.SetWobj(wobj);
        args_api.SetZone(zone);
        args_api.SetSpeed(speed);
        args_api.SetUpdatePointer(GetCmdTask(),GetCmdFile(),GetVisitedLine());
        //设置trigger
        TriggerAPI t;
        t.type = TriggerAPI::TriggerType::TIME;
        t.reference_is_from_start = true;
        t.value_from_reference = 0.1;
        t.trigger_callback = [this]{
            DLOG(INFO) <<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetVisitedLine()<<" time trigger callback";
        };
        args_api.SetTriggers({t});
        args_api.SetCallback(CallBackTypeAPI::MOVE_START,[]{LOG(INFO)<<"movec callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_FINISH,[]{LOG(INFO)<<"movec finish callback";});
        args_api.SetCallback(CallBackTypeAPI::MOVE_PAUSE,[]{LOG(INFO)<<"movec pause callback";});
        MotionCmdAPI api;
        int ret = api.SendStepBackCmd(args_api);
        LOG(INFO)<<"send motion cmd:"<<ret;
        DLOG(INFO)<<"point:"<<point<<" aux:"<<aux<<" speed:"<<speed<<" zone:"<<zone
            <<" tool:"<<tool<<" wobj:"<<wobj;

        DLOG(INFO) <<":"<<GetCmdTask()<<" "<<GetCmdFile()<<" "<<GetVisitedLine();
        if(ret == 0){
            return CommandProcessResultAPI::CMD_PROCESS_EXTRA;
        } else {
            return CommandProcessResultAPI::CMD_PROCESS_ERROR;
        }
    };
    return result;
}


std::shared_ptr<ModernRLCmdAPI> makePMoveBackC() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pmovec");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::MOVEMENT_ITSELF) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置指令是否需要括号
    cfg.SetRequireBracket(false);
    //函数的返回值类型
    cfg.SetReturnType(ValueTypeAPI::VALUE_DOUBLE);
    //设置步退的类型
    //cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);

    return std::make_shared<PMoveBackC>(cfg);
}




/**
 * @brief 实现坐标变换指令PPoseXPose，带返回值
 */
DECLARE_MORDEN_RLCMD_API(PPoseXPose);

MORDERN_CMD_ARGS_API(PPoseXPose) {
    std::vector<ArgTypeAPI>v;
    //必选参数rob，可选wobj和string
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    v.emplace_back(ValueTypeAPI::VALUE_ROBTARGET,true);
    return RequireArgsAPI(v);
}

MORDERN_CMD_EXECUTE_API(PPoseXPose) {
    cmdExecute_t result = [=] {
        auto args = GetCmdArgs();
        auto point = args[0].GetPointAPI();
        auto aux = args[1].GetPointAPI();
        auto ret = point;
        ret.pose = point.pose * aux.pose;
        SymbolVarBaseAPI var;
        var.ResetRobTarget(ret);
        //设置返回值
        SetReturnValue(var);
        DLOG(INFO)<<"point:"<<point<<" aux:"<<aux<<"ret:"<<ret;
        DLOG(INFO)<<"inverse:"<<point.pose.Inverse()<<" p*-p:"<<point.pose*point.pose.Inverse();
        return CommandProcessResultAPI::CMD_PROCESS_SUCCESS;
    };
    return result;
}


std::shared_ptr<ModernRLCmdAPI> makePPoseXPose() {
    RLCmdConfigAPI cfg;
    cfg.SetFuncName("pposexpose");
    //设置指令前瞻方式，默认WAIT_MOVE_PAUSE
    cfg.SetLookAhead(CmdLookAheadImplAPI::WAIT_MOVE_PAUSE) ;
    //设置任务限制类型
    cfg.SetTaskLimit(TaskLimitAPI::TASK_NO_LIMIT);
    //设置指令是否需要括号
    cfg.SetRequireBracket(false);
    //函数的返回值类型
    cfg.SetReturnType(ValueTypeAPI::VALUE_ROBTARGET);
    //设置步退的类型
    //cfg.SetStepBack(StepBackAPI::STEP_BACK_SKIP);
    return std::make_shared<PPoseXPose>(cfg);
}


}
void MotionCmdExample(){
    using namespace motion_cmd;
    xcore_api::rl_cmd::RegPluginCmdsAPI(makePMoveL());
    xcore_api::rl_cmd::RegPluginCmdsAPI(makePMoveAbsj());
    xcore_api::rl_cmd::RegPluginCmdsAPI(makePMoveJ());
    xcore_api::rl_cmd::RegPluginCmdsAPI(makePMoveC());
    xcore_api::rl_cmd::RegPluginCmdsAPI(makePSegMoveL());
    xcore_api::rl_cmd::RegPluginStepBackCmdsAPI(makePMoveBackL());
    xcore_api::rl_cmd::RegPluginStepBackCmdsAPI(makePMoveBackC());
    xcore_api::rl_cmd::RegPluginCmdsAPI(makePPoseXPose());
}


#pragma once
#include <string>
#include <vector>
#include <memory>
#include "const_data/pose_api.hpp"
#include "motion_cmd/motion_cmd_api.hpp"

namespace xcore_api{
namespace sdk_cmd{

enum class Status {
    SUCCESS, ///< 指令执行完毕
    PENDING, ///< 执行中
    ERROR ///< 执行出错，由指令自行负责错误上报
};

/**
 * 可以缓存到指令队列的接口类, 非运动指令
 */
class SDKCmdAPI {
public:
    SDKCmdAPI() = default;
    virtual ~SDKCmdAPI() {};
public:
    virtual void BeforeProcess(){};
    virtual Status DerivedProcess() = 0;
    virtual void AfterProcess(){};
};


/*包含运动指令和非运动指令接口*/

class MordenSDKCmdAPI{
public:
    MordenSDKCmdAPI();
    virtual ~MordenSDKCmdAPI();
public:

/**
 * @brief 发送SDK的单条运动指令
 * @param args 指令的具体参数 
 * @return int 0成功，其他失败。
 */
int SendSDKMotionCmd(const xcore_api::motion_cmd::MotionCmdArgsAPI& args,int cmd_id);

/**
 * @brief 发送SDK的单条普通指令
 * @param args 指令的具体参数 
 * @return int 0成功，其他失败。
 */
int SendSDKCmd(std::shared_ptr<SDKCmdAPI> ptr, int cmd_id);

/**
 * 打断前瞻的指令
 */
void SetFinalSDKCmd();


};









}
}


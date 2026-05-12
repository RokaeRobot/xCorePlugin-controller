#include "io.hpp"

#include "io/analog_api.hpp"
#include "log/log_api.hpp"

using namespace xcore_api::io;
/**
 * @brief IO模块使用示例具体io设备名称和信号名称需根据控制系统实际情况修改
*/
void IOExample() {
    // IO模块使用示例代码

    if(Analog::getInstance()->IsAiExist("VAI_0")) {
        double ai_value;
        if(Analog::getInstance()->GetAIValue("VAI_0", ai_value)) {
            LOG_INFO << "AI signal value: " << ai_value;
        } else {
            LOG_ERROR << "Failed to get AI signal value.";
        }
    } else {
        LOG_WARNING << "AI signal 'VAI_0' does not exist.";
    }
    if(Analog::getInstance()->IsAoExist("VAO_0")) {
        double ao_value;
        if(Analog::getInstance()->GetAOValue("VAO_0", ao_value)) {
            LOG_INFO << "AO signal value: " << ao_value;
            // 修改AO信号值
            if(Analog::getInstance()->SetAOValue("VAO_0", ao_value + 1.0)) {
                LOG_INFO << "AO signal value updated successfully.";
            } else {
                LOG_ERROR << "Failed to update AO signal value.";
            }
        } else {
            LOG_ERROR << "Failed to get AO signal value.";
        }
    } else {
        LOG_WARNING << "AO signal 'VAO_0' does not exist.";
    }
    if(Analog::getInstance()->IsGiExist("signal0")) {
        unsigned int gi_value;
        if(Analog::getInstance()->GetGIValue("signal0", gi_value)) {
            LOG_INFO << "GI signal value: " << gi_value;
        } else {
            LOG_ERROR << "Failed to get GI signal value.";
        }
    } else {
        LOG_WARNING << "GI signal 'signal0' does not exist.";
    }
    if(Analog::getInstance()->IsGoExist("signal1")) {
        unsigned int go_value;
        if(Analog::getInstance()->GetGOValue("signal1", go_value)) {
            LOG_INFO << "GO signal value: " << go_value;
        } else {
            LOG_ERROR << "Failed to get GO signal value.";
        }
    } else {
        LOG_WARNING << "GO signal 'signal1' does not exist.";
    }
    if(Analog::getInstance()->IsDiExist("VDI_0")) {
        bool di_value;
        if(Analog::getInstance()->GetDIValue("VDI_0", di_value)) {
            LOG_INFO << "DI signal value: " << di_value;
        } else {
            LOG_ERROR << "Failed to get DI signal value.";
        }
    } else {
        LOG_WARNING << "DI signal 'VDI_0' does not exist.";
    }
    if(Analog::getInstance()->IsDoExist("VDO_0")) {
        bool do_value;
        if(Analog::getInstance()->GetDOValue("VDO_0", do_value)) {
            LOG_INFO << "DO signal value: " << do_value;
        } else {
            LOG_ERROR << "Failed to get DO signal value.";
        }
    } else {
        LOG_WARNING << "DO signal 'VDO_0' does not exist.";
    }
    
}
#include "ecat_base.hpp"
#include "log/log_api.hpp"

/**
 * @brief 以太网通信基础类使用示例
*/
void EcatExample(){
    // 创建一个从站对象，假设从站ID为10001
    WeldingMachine machine(10001);
    if(machine.Init()){
        LOG_INFO<<"ecat init success";
        int vol = 100;
        while(true){
            machine.SetVol(vol);
            LOG_INFO<<"set vol:"<<vol;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            vol += 10;
        }
    } else {
        LOG_ERROR<<"ecat init failed";
    }
}

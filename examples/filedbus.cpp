#include "fieldbus/fieldbus_api.hpp"
#include "log/log_api.hpp"

using namespace xcore_api::fieldbus;
void FileDbusExample(){
    ModbusCfgAPI cfg(MODBUS_TCP_MASTER);
    cfg.SetName("filedbus_example");
    cfg.SetIp("127.0.0.1");
    cfg.SetPort(502);
    cfg.SetSlaverId(1);
    cfg.SetHoldRegStartAddr(0);
    FieldbusAPI bus(cfg);
    if(bus.Open() == 0){
        LOG_INFO<<"open file dbus success";
        uint16_t data[10];
        while(true){
            if(bus.ReadRegisters(0,data,10) == 0){
                std::string str;
                for(int i = 0;i<10;++i){
                    str += std::to_string(data[i]) + ",";
                }
                LOG_INFO<<"read data:"<<str;
            } else {
                LOG_ERROR<<"read data failed";
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } else {
        LOG_ERROR<<"open file dbus failed";
    }
}
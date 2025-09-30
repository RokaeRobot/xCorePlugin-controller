/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file modbus.cpp
 * @brief modbus master tcp读写寄存器
 *
 */
#include <iostream>
#include <string>

#include "log/log_api.hpp"
#include "fieldbus/fieldbus_api.hpp"

void ModbusExample() {
    std::thread t([](){
        using namespace xcore_api::fieldbus;
        ModbusCfgAPI cfg(DeviceTypeAPI::MODBUS_TCP_MASTER);
        cfg.SetName("plugin_master");
        //设置为自己从站的ip
        cfg.SetIp("192.168.2.213");
        //如果从站不支持读线圈等操作则设置为0，否则可能影响功能
        cfg.SetCoilsNum(0);
        cfg.SetDiscInputNum(0);
        FieldbusAPI api(cfg);
        int i = 0;
        uint16_t src[10] = {0};
        uint16_t dest[10] = {0};
        api.Open();
        while(1){
            ++i;
            int rc = api.ReadRegisters(40000, dest) ;
            LOG_DEBUG<<"read registers:"<<rc<< " read value:"<<dest[0];
            ++src[0];
            rc = api.WriteRegisters(40005, src);
            LOG_DEBUG<<"write registers:"<<rc<<" write value: "<<src[0];
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
        api.Close();
    });
    t.detach();
}











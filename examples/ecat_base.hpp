#pragma once
/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * @file ecat_base.hpp
 * @brief 以太网通信基础类使用示例
 */
#include "ethercat/ecat_base_api.hpp"

class WeldingMachine:public xcore_api::ecat::EcatBaseAPI{
public:
    WeldingMachine(int slave_id):xcore_api::ecat::EcatBaseAPI(slave_id){
        RegisterVolPdo();
    }
    virtual ~WeldingMachine(){}
    bool Init(){
        return InitEcat();
    }
    int RegisterVolPdo(){
        uint16_t index = 0;
        uint16_t byteoffs = 4;
        uint16_t bytelen = 4;
        return RegisterPdo(m_pdo_vol,index,byteoffs,bytelen);
    }
    int SetVol(const int vol){
        int value = vol;
        return SetPdoValue(m_pdo_vol,&value);
    }
private:
    xcore_api::const_data::ecat::PdoAPI m_pdo_vol;
};

void EcatExample();

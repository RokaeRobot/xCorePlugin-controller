/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD.
 * All Rights Reserved.
 *
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 *
 * @file ElectricClawService.cpp
 * @brief 自定义协议
 */
#include "ElectricClawService.h"

std::string json_serialize(const Json::Value &value)
{
    std::string raw = Json::FastWriter().write(value);
    raw[raw.length() - 1] = '\r'; // ending control, instead of \n
    return raw;
}

void ServiceProtocol()
{
    /**
     * @brief 插件名称，插件的key，回调函数
     * 控制器收到json协议就会回调对应的函数
     * 用户收到的协议数据为{"key":"value"}
     */
    xcore_api::service::RegServiceAPI("ElectricClawPlugin", "stop",
                                      [](const Json::Value &in)
                                      {
                                          LOG(INFO) << "receive:" << json_serialize(in);
                                          int slave_id = in["stop"]["slave_id"].asInt();
                                          bool ret = api.stopElectricClaw(slave_id);

                                          Json::Value out;
                                          out["return"] = ret;
                                          LOG(INFO) << "response:" << json_serialize(out);
                                          return out;
                                      });

    xcore_api::service::RegServiceAPI("ElectricClawPlugin", "start",
                                      [](const Json::Value &in)
                                      {
                                          LOG(INFO) << "receive:" << json_serialize(in);

                                          Json::Value out;
                                          int slave_id = in["start"]["slave_id"].asInt();
                                          int width = in["start"]["width"].asInt();
                                          int force = in["start"]["force"].asInt();
                                          int speed = in["start"]["speed"].asInt();
                                          int mode = in["start"]["mode"].asInt();
                                          bool ret = api.startElectricClaw(
                                              slave_id, width, force, speed, mode);

                                          out["return"] = ret;
                                          LOG(INFO) << "response:" << json_serialize(out);
                                          return out;
                                      });

    xcore_api::service::RegServiceAPI("ElectricClawPlugin", "get_status",
                                      [](const Json::Value &in)
                                      {
                                          LOG(INFO) << "receive:" << json_serialize(in);

                                          xcore_api::endtool::ModbusRTUEndtoolAPI api;
                                          Json::Value out;
                                          const int slave_id = in["get_status"]["slave_id"].asInt();

                                          std::vector<uint16_t> data;
                                          bool ret = api.ReadRegister_03(slave_id, 0x0100, 8, data);
                                          if (data.size() < 8 || !ret)
                                          {
                                              LOG(WARNING) << "Failed to read status, data size is less than 8";
                                              out["return"] = false;
                                              return out;
                                          }

                                          out["status"] = data[0];         // 状态
                                          out["external_width"] = data[1]; // 外宽
                                          out["internal_width"] = data[2]; // 内宽
                                          out["force"] = data[7];          // 力
                                          out["return"] = ret;

                                          LOG(INFO) << "response:" << json_serialize(out);
                                          return out;
                                      });
}
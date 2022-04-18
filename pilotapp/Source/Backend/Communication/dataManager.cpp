#include "dataManager.h"
#include <iostream>
//#include <iomanip>

#include <QDebug>

rawDataPack dataManager::deserializeRawBoatData(std::string& raw){
    //raw = dataManager::msgpackDataPrefix + raw + dataManager::msgpackDataSuffix;
    if (raw.empty() || raw[0] != dataManager::msgpackDataPrefix)
        raw = dataManager::msgpackDataPrefix + raw;

    if (raw.empty() || raw[raw.size() - 1] != dataManager::msgpackDataSuffix)
        raw += dataManager::msgpackDataSuffix;

    msgpack::object_handle oh = msgpack::unpack(raw.data(), raw.size());
    msgpack::object obj = oh.get();

    //std::cout << obj << std::endl;

    //

    rawDataPack data;
    obj.convert(data);

    return data;
}

///

boatDataPack::boatDataPack(rawDataPack& raw){
    std::map<std::string, msgpack::type::variant> m = raw.getMap();
    //qInfo() << "before const";

    TP = m["TP"].as_uint64_t();
    DP = m["DP"].as_uint64_t();
    CP = m["CP"].as_double();
    BV = m["BV"].as_double();
    UV = m["UV"].as_bool();
    OV = m["OV"].as_bool();
    SM = m["SM"].as_bool();
    EM = m["EM"].as_bool();

    posLat = m["posLat"].as_double();
    posLon = m["posLon"].as_double();

    speed = m["speed"].as_double();

    timeStamp = m["timeStamp"].as_double();

    //qInfo() << "after const";
}

int boatDataPack::getThrottlePercent(){
    return TP;
}

int boatDataPack::getDutyPercent(){
    return DP;
}

float boatDataPack::getChipTemp(){
    return CP;
}

double boatDataPack::getBatteryVoltage(){
    return BV;
}

bool boatDataPack::getUndervolt(){
    return UV;
}

bool boatDataPack::getOvervolt(){
    return OV;
}

bool boatDataPack::getSolarMode(){
    return SM;
}

bool boatDataPack::getMotorEnabled(){
    return EM;
}

double boatDataPack::getPosLat(){
    return posLat;
}

double boatDataPack::getPosLon(){
    return posLon;
}

double boatDataPack::getSpeed(){
    return speed;
}

double boatDataPack::getTimestamp(){
    return timeStamp;
}
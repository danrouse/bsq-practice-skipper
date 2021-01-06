#include "config.hpp"

Config config;

void SaveConfig() {
    LOG_CALLER;
    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();
    getConfig().config.AddMember("skipDuration", config.skipDuration, allocator);
    getConfig().config.AddMember("timeScaleStep", config.timeScaleStep, allocator);
    getConfig().config.AddMember("fullTiltThreshold", config.fullTiltThreshold, allocator);
    getConfig().config.AddMember("deadZoneThreshold", config.deadZoneThreshold, allocator);
    getConfig().config.AddMember("isRightHand", config.isRightHand, allocator);
    getConfig().Write();
}

bool LoadConfig() {
    LOG_CALLER;
    getConfig().Load();
    bool foundEverything = true;
    if (getConfig().config.HasMember("skipDuration") && getConfig().config["skipDuration"].IsDouble()) { config.skipDuration = getConfig().config["skipDuration"].GetDouble(); } else { foundEverything = false; }
    if (getConfig().config.HasMember("timeScaleStep") && getConfig().config["timeScaleStep"].IsDouble()) { config.timeScaleStep = getConfig().config["timeScaleStep"].GetDouble(); } else { foundEverything = false; }
    if (getConfig().config.HasMember("fullTiltThreshold") && getConfig().config["fullTiltThreshold"].IsDouble()) { config.fullTiltThreshold = getConfig().config["fullTiltThreshold"].GetDouble(); } else { foundEverything = false; }
    if (getConfig().config.HasMember("deadZoneThreshold") && getConfig().config["deadZoneThreshold"].IsDouble()) { config.deadZoneThreshold = getConfig().config["deadZoneThreshold"].GetDouble(); } else { foundEverything = false; }
    if (getConfig().config.HasMember("isRightHand") && getConfig().config["isRightHand"].IsBool()) { config.isRightHand = getConfig().config["isRightHand"].GetBool(); } else { foundEverything = false; }
    return foundEverything;
}

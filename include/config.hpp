#pragma once

#include "logger.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

typedef struct _Config {
    float skipDuration = 5.0f;
    float timeScaleStep = 0.1f;
    float fullTiltThreshold = 0.90f;
    float deadZoneThreshold = 0.05f;
    bool isRightHand = false;
} Config;

Configuration& getConfig();
void SaveConfig();
bool LoadConfig();

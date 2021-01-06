#pragma once

#include <chrono>

#include "config.hpp"
#include "gameplay.hpp"
#include "logger.hpp"

#include "ui/PracticeGameplayView.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "GlobalNamespace/AudioTimeSyncController_InitData.hpp"
#include "GlobalNamespace/CoreGameHUDController.hpp"
#include "GlobalNamespace/GameSongController.hpp"
#include "GlobalNamespace/OVRInput.hpp"
#include "GlobalNamespace/OVRInput_Axis2D.hpp"
#include "UnityEngine/Vector2.hpp"

namespace PracticeSkipper {
    void InstallHooks();
}

struct ThumbstickState {
    std::chrono::time_point<std::chrono::system_clock> lastReset;
    bool isCurrentlyPressed;
    bool isPreviousPressPositive;
};

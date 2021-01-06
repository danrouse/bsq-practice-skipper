#include "hooks.hpp"

using namespace il2cpp_utils;
using namespace GlobalNamespace;

extern Config config;
ThumbstickState thumbstickStates[2];
bool isPracticeMode;

MAKE_HOOK_OFFSETLESS(SinglePlayerLevelSelectionFlowCoordinator_StartLevel, void, Il2CppObject* self, Il2CppObject* beforeSceneSwitchCallback, bool practice) {
    LOG_CALLER;
    SinglePlayerLevelSelectionFlowCoordinator_StartLevel(self, beforeSceneSwitchCallback, practice);
    isPracticeMode = practice;
}

MAKE_HOOK_OFFSETLESS(StandardLevelGameplayManager_OnDestroy, void, Il2CppObject* self) {
    LOG_CALLER;
    StandardLevelGameplayManager_OnDestroy(self);
    isPracticeMode = false;
}

template<typename Callback>
void HandleStickInput(float value, ThumbstickState* thumbstickState, Callback onDoubleTap) {
    if (fabs(value) > config.fullTiltThreshold) {
        auto isPositive = value > 0.0f;
        if (
            !thumbstickState->isCurrentlyPressed &&
            thumbstickState->isPreviousPressPositive == isPositive &&
            std::chrono::system_clock::now() - thumbstickState->lastReset < std::chrono::milliseconds(300)
        ) {
            onDoubleTap(isPositive);
            thumbstickState->lastReset = std::chrono::time_point<std::chrono::system_clock>::min();
        }
        thumbstickState->isCurrentlyPressed = true;
        thumbstickState->isPreviousPressPositive = isPositive;
    } else if (thumbstickState->isCurrentlyPressed && (fabs(value) <= config.deadZoneThreshold)) {
        thumbstickState->isCurrentlyPressed = false;
        thumbstickState->lastReset = std::chrono::system_clock::now();
    }
}

MAKE_HOOK_OFFSETLESS(GameSongController_LateUpdate, void, GameSongController* self) {
    GameSongController_LateUpdate(self);
    if (isPracticeMode) {
        auto controller = config.isRightHand ? OVRInput::Controller::RTouch : OVRInput::Controller::LTouch;
        auto stickValue = OVRInput::Get(OVRInput::Axis2D::_get_PrimaryThumbstick(), controller);
        HandleStickInput(stickValue.x, &thumbstickStates[0], [&](bool isRight) {
            SeekGameplay(self, config.skipDuration * (isRight ? 1.0f : -1.0f));
        });
        HandleStickInput(stickValue.y, &thumbstickStates[1], [&](bool isUp) {
            auto nextTimeScale = OverrideTimeScale(self->audioTimeSyncController, config.timeScaleStep * (isUp ? 1.0f : -1.0f));
            PracticeSkipper::UI::PracticeGameplayView::Update(nextTimeScale);
        });
    }
}

MAKE_HOOK_OFFSETLESS(CoreGameHUDController_Start, void, CoreGameHUDController* self) {
    CoreGameHUDController_Start(self);
    if (isPracticeMode) {
        LOG_CALLER;
        PracticeSkipper::UI::PracticeGameplayView::Install(self->songProgressPanelGO);
        auto audioTimeSyncController = GetFirstEnabledComponent<AudioTimeSyncController*>();
        PracticeSkipper::UI::PracticeGameplayView::Update(audioTimeSyncController->initData->timeScale);
    }
}

namespace PracticeSkipper {
    void InstallHooks() {
        INSTALL_HOOK_OFFSETLESS(GameSongController_LateUpdate, FindMethodUnsafe("", "GameSongController", "LateUpdate", 0));
        INSTALL_HOOK_OFFSETLESS(SinglePlayerLevelSelectionFlowCoordinator_StartLevel, FindMethodUnsafe("", "SinglePlayerLevelSelectionFlowCoordinator", "StartLevel", 2));
        INSTALL_HOOK_OFFSETLESS(StandardLevelGameplayManager_OnDestroy, FindMethodUnsafe("", "StandardLevelGameplayManager", "OnDestroy", 0));
        INSTALL_HOOK_OFFSETLESS(CoreGameHUDController_Start, FindMethodUnsafe("", "CoreGameHUDController", "Start", 0));
    }
}

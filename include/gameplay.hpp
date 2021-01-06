#pragma once

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "logger.hpp"
#include "unity_utils.hpp"

#include "UnityEngine/AudioSource.hpp"
#include "GlobalNamespace/AudioManagerSO.hpp"
#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/BeatmapEventData.hpp"
#include "GlobalNamespace/BeatmapObjectCallbackController.hpp"
#include "GlobalNamespace/BeatmapObjectCallbackController_BeatmapEventCallbackData.hpp"
#include "GlobalNamespace/BeatmapObjectCallbackController_BeatmapObjectCallbackData.hpp"
#include "GlobalNamespace/BeatmapObjectData.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/GameSongController.hpp"
#include "GlobalNamespace/IReadonlyBeatmapData.hpp"
#include "GlobalNamespace/IReadonlyBeatmapLineData.hpp"
#include "GlobalNamespace/NoteCutSoundEffectManager.hpp"
#include "GlobalNamespace/ScoreController.hpp"

void SeekGameplay(GlobalNamespace::GameSongController* gameSongController, float relativeSkipTime);
float OverrideTimeScale(GlobalNamespace::AudioTimeSyncController* audioTimeSyncController, float relChange);

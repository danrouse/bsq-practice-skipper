#include "gameplay.hpp"

void SeekGameplay(GlobalNamespace::GameSongController* gameSongController, float relativeSkipTime) {
    LOG_DEBUG("Seek %.2f", relativeSkipTime);

    // remove all current beatmap objects
    GetFirstEnabledComponent<GlobalNamespace::ScoreController*>()->beatmapObjectManager->DissolveAllObjects();

    const float absTargetTime = std::max(0.0f, relativeSkipTime + gameSongController->audioTimeSyncController->songTime);
    
    // set beatmap object callback indices
    const auto beatmapLinesData = gameSongController->beatmapObjectCallbackController->beatmapData->get_beatmapLinesData();
    const auto linesCount = il2cpp_utils::RunMethod<int>(beatmapLinesData, "System.Collections.ICollection.get_Count").value();
    for (int i = 0; i < linesCount; i++) {
        auto lineData = il2cpp_utils::RunMethod<GlobalNamespace::IReadonlyBeatmapLineData*>(beatmapLinesData, "System.Collections.Generic.IReadOnlyList`1.get_Item", i).value();
        auto beatmapObjectsInLine = lineData->get_beatmapObjectsData();
        for (int j = 0; j < beatmapObjectsInLine->get_Count(); j++) {
            if (beatmapObjectsInLine->System_Collections_Generic_IReadOnlyList_1_get_Item(j)->time >= absTargetTime) {
                for (int k = 0; k < gameSongController->beatmapObjectCallbackController->beatmapObjectCallbackData->get_Count(); k++) {
                    gameSongController->beatmapObjectCallbackController->beatmapObjectCallbackData->get_Item(k)->nextObjectIndexInLine->values[i] = j;
                }
                break;
            }
        }
    }

    // set beatmap event callback indices
    auto events = gameSongController->beatmapObjectCallbackController->beatmapData->get_beatmapEventsData();
    for (int i = 0; i < events->get_Count(); i++) {
        auto event = events->System_Collections_Generic_IReadOnlyList_1_get_Item(i);
        if (event->time >= absTargetTime) {
            for (int j = 0; j < gameSongController->beatmapObjectCallbackController->beatmapEventCallbackData->get_Count(); j++) {
                gameSongController->beatmapObjectCallbackController->beatmapEventCallbackData->get_Item(j)->nextEventIndex = i;
            }
            gameSongController->beatmapObjectCallbackController->nextEventIndex = i;
            break;
        }
    }

    // seek audio
    gameSongController->SeekTo((absTargetTime - gameSongController->audioTimeSyncController->startSongTime) / gameSongController->audioTimeSyncController->timeScale);
    if (relativeSkipTime > 0.0f) gameSongController->audioTimeSyncController->audioSource->Play();
}

float OverrideTimeScale(GlobalNamespace::AudioTimeSyncController* audioTimeSyncController, float relChange) {
    const auto nextTimeScale = std::max(audioTimeSyncController->timeScale + relChange, 0.0001f);
    LOG_DEBUG("Set timeScale to %.2f", nextTimeScale);
    audioTimeSyncController->timeScale = nextTimeScale;
    audioTimeSyncController->audioSource->set_pitch(nextTimeScale);
    GetFirstEnabledComponent<GlobalNamespace::NoteCutSoundEffectManager*>()->audioManager->set_musicPitch(1.0f / nextTimeScale);  
    return nextTimeScale;
}

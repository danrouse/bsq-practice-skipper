#pragma once

#include "logger.hpp"
#include "config.hpp"
#include "custom-types/shared/macros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "HMUI/ViewController.hpp"
#include "System/String.hpp"

DECLARE_CLASS_CODEGEN(PracticeSkipper, ModSettingsViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, skipDurationIncrement);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, timeScaleStepIncrement);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, fullTiltIncrement);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, deadZoneIncrement);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, handToggleIncrement);
    
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 2), bool removedFromHierarchy, bool screenSystemDisabling);

    REGISTER_FUNCTION(ModSettingsViewController,
        REGISTER_FIELD(skipDurationIncrement);
        REGISTER_FIELD(timeScaleStepIncrement);
        REGISTER_FIELD(fullTiltIncrement);
        REGISTER_FIELD(deadZoneIncrement);
        REGISTER_FIELD(handToggleIncrement);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(DidDeactivate);
    )
)

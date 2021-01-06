#include "ui/ModSettingsViewController.hpp"

extern Config config;

DEFINE_CLASS(PracticeSkipper::ModSettingsViewController);

#include "TMPro/TextMeshProUGUI.hpp"

void PracticeSkipper::ModSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation || !addedToHierarchy) {
        LOG_DEBUG("second call");
        return;
    }

    LOG_CALLER;

    auto layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_rectTransform());
    layout->set_spacing(1);
    layout->get_gameObject()->AddComponent<QuestUI::Backgroundable*>()->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
    layout->set_padding(UnityEngine::RectOffset::New_ctor(4, 4, 4, 4));

    handToggleIncrement = QuestUI::BeatSaberUI::CreateIncrementSetting(
        layout->get_transform(),
        "Controller",
        0, 1.0f,
        config.isRightHand ? 1.0f : 0.0f,
        il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
            classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](PracticeSkipper::ModSettingsViewController* self, float val) {
                bool isRightHand = (int)round(val) % 2 != 0;
                self->handToggleIncrement->Text->SetText(il2cpp_utils::createcsstr(
                    isRightHand ? "Right" : "Left"
                ));
                config.isRightHand = isRightHand;
                SaveConfig();
                LOG_DEBUG("Set isRightHand to %d", isRightHand);
            }
        )
    );
    handToggleIncrement->Text->SetText(il2cpp_utils::createcsstr(config.isRightHand ? "Right" : "Left"));
    QuestUI::BeatSaberUI::AddHoverHint(handToggleIncrement->get_gameObject(), "Use the analog stick from this hand to skip or change speed");

    skipDurationIncrement = QuestUI::BeatSaberUI::CreateIncrementSetting(
        layout->get_transform(),
        "Skip length",
        0, 1.0f,
        config.skipDuration,
        true, false,
        1.0f, 30.0f,
        UnityEngine::Vector2(0.0f, 0.0f),
        il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
            classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](PracticeSkipper::ModSettingsViewController* self, float val) {
                self->skipDurationIncrement->Text->SetText(il2cpp_utils::createcsstr(
                    to_utf8(csstrtostr(self->skipDurationIncrement->GetRoundedString())) + " sec"
                ));
                config.skipDuration = val;
                SaveConfig();
                LOG_DEBUG("Set skipDurationIncrement to %.2f", val);
            }
        )
    );
    skipDurationIncrement->Text->SetText(il2cpp_utils::createcsstr(to_utf8(csstrtostr(skipDurationIncrement->GetRoundedString())) + " sec"));
    QuestUI::BeatSaberUI::AddHoverHint(skipDurationIncrement->get_gameObject(), "How much time to skip when triggered");

    timeScaleStepIncrement = QuestUI::BeatSaberUI::CreateIncrementSetting(
        layout->get_transform(),
        "Speed change increment",
        2, 0.05f,
        config.timeScaleStep,
        0.05f, 10.0f,
        il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
            classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](PracticeSkipper::ModSettingsViewController* self, float val) {
                self->timeScaleStepIncrement->Text->SetText(il2cpp_utils::createcsstr(std::to_string((int)(val * 100.0f)) + "%"));
                config.timeScaleStep = val;
                SaveConfig();
                LOG_DEBUG("Set timeScaleStepIncrement to %.2f", val);
            }
        )
    );
    timeScaleStepIncrement->Text->SetText(il2cpp_utils::createcsstr(std::to_string((int)(config.timeScaleStep * 100.0f)) + "%"));
    QuestUI::BeatSaberUI::AddHoverHint(timeScaleStepIncrement->get_gameObject(), "How much to increase or decrease song speed when triggered");

    fullTiltIncrement = QuestUI::BeatSaberUI::CreateIncrementSetting(
        layout->get_transform(),
        "Full tilt angle",
        2, 0.01f,
        // 0.5f, 1.0f,
        config.fullTiltThreshold,
        il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
            classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](PracticeSkipper::ModSettingsViewController* self, float val) {
                config.fullTiltThreshold = val;
                SaveConfig();
                LOG_DEBUG("Set fullTiltThreshold to %.2f", val);
            }
        )
    );
    QuestUI::BeatSaberUI::AddHoverHint(fullTiltIncrement->get_gameObject(), "How far the stick needs to be pressed to trigger");

    deadZoneIncrement = QuestUI::BeatSaberUI::CreateIncrementSetting(
        layout->get_transform(),
        "Minimum tilt angle",
        2, 0.01f,
        // 0.01f, 0.5f,
        config.deadZoneThreshold,
        il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
            classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](PracticeSkipper::ModSettingsViewController* self, float val) {
                config.deadZoneThreshold = val;
                SaveConfig();
                LOG_DEBUG("Set deadZoneThreshold to %.2f", val);
            }
        )
    );
    QuestUI::BeatSaberUI::AddHoverHint(deadZoneIncrement->get_gameObject(), "How far the trigger needs to return to trigger");
}

void PracticeSkipper::ModSettingsViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {

}

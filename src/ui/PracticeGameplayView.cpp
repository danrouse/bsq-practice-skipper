#include "ui/PracticeGameplayView.hpp"

TMPro::TextMeshProUGUI* songSpeedText;

void PracticeSkipper::UI::PracticeGameplayView::Install(UnityEngine::GameObject* songProgressPanel) {
    songSpeedText = QuestUI::BeatSaberUI::CreateText(songProgressPanel->get_transform(), "<i>100%</i>");
    songSpeedText->set_fontSize(12.0f);
    songSpeedText->set_alignment(TMPro::TextAlignmentOptions::Center);
    songSpeedText->get_rectTransform()->set_localPosition(UnityEngine::Vector3(3.0f, -20.0f, 0.0f));

    auto songSpeedIconGo = UnityEngine::GameObject::New_ctor(il2cpp_utils::createcsstr("PracticeSkipperSongSpeedIcon"));
    songSpeedIconGo->get_transform()->SetParent(songProgressPanel->get_transform(), false);
    auto songSpeedIconRect = songSpeedIconGo->AddComponent<UnityEngine::RectTransform*>();
    songSpeedIconRect->set_sizeDelta(UnityEngine::Vector2(8.0f, 8.0f));
    songSpeedIconRect->set_localPosition(UnityEngine::Vector3(-14.0f, -18.0f, 0.0f));
    auto songSpeedIconImage = songSpeedIconGo->AddComponent<HMUI::ImageView*>();
    songSpeedIconImage->set_type(UnityEngine::UI::Image::Type::Sliced);
    songSpeedIconImage->set_sprite(FindObjectByName<UnityEngine::Sprite*>("FasterSongIcon"));
}

void PracticeSkipper::UI::PracticeGameplayView::Update(float timeScale) {
    songSpeedText->SetText(il2cpp_utils::createcsstr("<i>" + std::to_string((int)round(timeScale * 100.0f)) + "%</i>"));
}

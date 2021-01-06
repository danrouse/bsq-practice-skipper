#pragma once

#include "unity_utils.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "HMUI/ImageView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

namespace PracticeSkipper {
    namespace UI {
        namespace PracticeGameplayView {
            void Install(UnityEngine::GameObject* songProgressPanel);
            void Update(float timeScale);
        }
    }
}

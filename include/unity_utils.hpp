#pragma once

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "questui/shared/ArrayUtil.hpp"

template<typename ObjT>
ObjT FindObject() {
    return QuestUI::ArrayUtil::First(UnityEngine::Resources::FindObjectsOfTypeAll<ObjT>());
}

template<typename ObjT, typename Predicate>
ObjT FindObject(Predicate p) {
    return QuestUI::ArrayUtil::First(UnityEngine::Resources::FindObjectsOfTypeAll<ObjT>(), p);
}

template<typename ObjT>
ObjT FindObjectByName(std::string searchName) {
    return FindObject<ObjT>([searchName](ObjT obj) {
        auto name = to_utf8(csstrtostr(obj->get_name()));
        return name == searchName;
    });
}

template<typename ObjT>
ObjT GetFirstEnabledComponent() {
    return FindObject<ObjT>([](ObjT obj) {
        return obj->get_enabled();
    });
}

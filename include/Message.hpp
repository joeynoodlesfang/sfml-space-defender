#pragma once

#include "GameMessageManager.hpp"
#include <string>

inline void postMessage(const std::string& text, float duration = 2.0f) {
    GameMessageManager::getInstance().addMessage(text, duration);
}
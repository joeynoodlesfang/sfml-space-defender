#pragma once

#include <unordered_map>
#include <type_index>
#include <vector>

class EventDispatcher {
    std::unordered_map<std::type_index, std::vector<EventHandler>> handlers;
}
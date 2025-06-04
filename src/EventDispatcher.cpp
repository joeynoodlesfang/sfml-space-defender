#include "EventDispatcher.hpp"

void EventDispatcher::subscribe (EventHandler handler) {
    handlers[std::type_index(typeid(EventType))].push_back(handler);
}

void EventDispatcher::publish (const Event& event) {
    auto it = handlers.find(std::type_index(typeid(event)));
    if (it != handlers.end()) {
        for (auto& handler : it->second) {
            handler(event);
        }
    }
}
// EntityUtils.hpp
#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <SFML/Graphics.hpp>

template<typename T>
void updateEntities(std::vector<std::unique_ptr<T>>& entities, float deltaTime) {
    for (auto& entity : entities) {
        entity->update(deltaTime);
    }
}

template<typename T, typename Predicate>
void removeEntitiesIf(std::vector<std::unique_ptr<T>>& entities, Predicate predicate) {
    entities.erase(
        std::remove_if(entities.begin(), entities.end(), predicate),
        entities.end()
    );
}

template<typename T>
void drawEntities(std::vector<std::unique_ptr<T>>& entities, sf::RenderWindow& window) {
    for (auto& entity : entities) {
        entity->draw(window);
    }
}

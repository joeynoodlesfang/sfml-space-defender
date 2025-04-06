// EnemySpawner.cpp
#include "EnemySpawner.hpp"
#include <cstdlib>

EnemySpawner::EnemySpawner(float spawnInterval, unsigned int screenWidth)
    : spawnInterval(spawnInterval), screenWidth(screenWidth) {}

void EnemySpawner::update(std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
        float x = randomX();
        enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(x, -40.f)));
        spawnClock.restart();
    }
}

float EnemySpawner::randomX() {
    return static_cast<float>(std::rand() % static_cast<int>(screenWidth - 40)) + 20.f;
}

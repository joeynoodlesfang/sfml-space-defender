#pragma once

#include <vector>
#include <memory>
#include <SFML/System/Clock.hpp>
#include "Enemy.hpp"

class EnemySpawner {
public:
    EnemySpawner(float spawnInterval, unsigned int screenWidth);

    void update(std::vector<std::unique_ptr<Enemy>>& enemies);

private:
    float spawnInterval;
    sf::Clock spawnClock;
    unsigned int screenWidth;

    float randomX();
};

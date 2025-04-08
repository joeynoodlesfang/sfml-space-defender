// EnemySpawner.cpp
#include "EnemySpawner.hpp"
#include <cstdlib>
#include <iostream>

#include "Message.hpp"

//Legacy UNUSED
EnemySpawner::EnemySpawner(float spawnInterval, unsigned int screenWidth)
    : spawnInterval(spawnInterval), screenWidth(screenWidth) {}

EnemySpawner::EnemySpawner(unsigned int screenWidth)
    : screenWidth(screenWidth)
{
    waves.push_back(Wave{ 5, 2.0f });   // 5 enemies, 2s apart
    waves.push_back(Wave{ 8, 1.5f });
    waves.push_back(Wave{ 12, 1.0f });
    postMessage("[WaveSpawner] Starting Wave 1\n");
    spawnClock.restart();
}

void EnemySpawner::spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemies) {
    float x = randomX();
    enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(x, -40.f)));
    enemiesSpawnedInWave++;
    spawnClock.restart();
}

void EnemySpawner::update(std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (spawnInterval == 0) { // Not legacy check
        if (currentWaveIndex >= waves.size()) {
            return; // No more waves
        }

        const Wave& currentWave = waves[currentWaveIndex];
    
        if (enemiesSpawnedInWave < currentWave.totalEnemies) {
            if (spawnClock.getElapsedTime().asSeconds() > currentWave.spawnInterval) {
                spawnEnemy(enemies);
            }
        } else if (!waveComplete) {
            postMessage("[WaveSpawner] Wave " + std::to_string(currentWaveIndex + 1) + " complete.\n");
            waveComplete = true;
        }
    } else { // Legacy random spawner
        if (spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
            float x = randomX();
            enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(x, -40.f)));
            spawnClock.restart();
        }
    }
}


void EnemySpawner::startNextWave() {
    if (currentWaveIndex + 1 < waves.size()) {
        currentWaveIndex++;
        enemiesSpawnedInWave = 0;
        waveComplete = false;
        spawnClock.restart();
        postMessage("[WaveSpawner] Starting Wave " + std::to_string(currentWaveIndex + 1) + "\n");
    } else {
        if (!spawnerEmpty) {
            spawnerEmpty = true;
            postMessage("[WaveSpawner] No more waves!\n");
        }
    }
}

bool EnemySpawner::isWaveComplete() const {
    return waveComplete;
}

float EnemySpawner::randomX() {
    return static_cast<float>(std::rand() % static_cast<int>(screenWidth - 40)) + 20.f;
}
#pragma once

#include <vector>
#include <memory>
#include <SFML/System/Clock.hpp>
#include "Enemy.hpp"

struct Wave {
    int totalEnemies;
    float spawnInterval; // seconds
};

enum class WaveState {
    Idle,
    StartingWave,
    Spawning,
    EndingWave
};

class EnemySpawner {
public:
    EnemySpawner(unsigned int screenWidth);
    EnemySpawner(float spawnInterval, unsigned int screenWidth);    // legacy UNUSED
    
    void update(std::vector<std::unique_ptr<Enemy>>& enemies);
    void startNextWave();
    void reset();
    bool isWaveComplete() const;
    bool isAllWavesComplete() const;
    int getCurrentWaveIndex() const;

private:
    unsigned int screenWidth;

    std::vector<Wave> waves; // stores all wave data
    int currentWaveIndex = 0; // current wave
    int enemiesSpawnedInWave = 0;
    bool waveComplete = false;
    bool allWavesComplete = false;
    float spawnInterval = 0;    // legacy UNUSED
    float waveDelayDuration = 0.f;
    sf::Clock spawnClock;
    sf::Clock waveDelayClock;
    WaveState waveState = WaveState::Idle;

    float randomX();
    void spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemies);

};

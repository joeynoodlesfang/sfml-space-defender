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
    WaveState getWaveState() const;
    void startNextWave();
    bool isFirstWaveSpawned() const;
    bool isWaveComplete() const;
    bool isAllWavesComplete() const;

private:
    unsigned int screenWidth;

    std::vector<Wave> waves; // stores all wave data
    int currentWaveIndex = 0; // current wave
    int enemiesSpawnedInWave = 0;
    bool firstWaveSpawned = false;
    bool waveComplete = false;
    bool allWavesComplete = false;
    bool promptedAllWavesComplete = false;
    float spawnInterval = 0;    // legacy UNUSED
    sf::Clock spawnClock;

    float randomX();
    void spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemies);

    WaveState waveState = WaveState::Idle;
    sf::Clock waveDelayClock;
    float waveDelayDuration = 0.f;
    int currentWaveIndex = 0;

};

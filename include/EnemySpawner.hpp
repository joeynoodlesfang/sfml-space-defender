#pragma once

#include <vector>
#include <memory>
#include <SFML/System/Clock.hpp>
#include "Enemy.hpp"

// put all wave information in this struct
struct Wave {
    int totalEnemies;
    float spawnInterval; // seconds
};

// Spawner's update FSM
enum class WaveState {
    Idle,
    StartingWave,
    Spawning,
    EndingWave,
    EndingAllWaves
};

class EnemySpawner {
public:
    EnemySpawner(unsigned int screenWidth);
    EnemySpawner(float spawnInterval, unsigned int screenWidth);    // legacy UNUSED
    
    void update(std::vector<std::unique_ptr<Enemy>>& enemies);
    void startNextWave(); // legacy
    void reset();
    void startSpawn();
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
    WaveState previousWaveState = WaveState::Idle;
    
    void handleStateEnter(WaveState state);
    void onEnterIdle();
    void onEnterStartingWave();
    void onEnterSpawning();
    void onEnterEndingWave();
    void onEnterEndingAllWaves();
    float randomX();
    void spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemies);
};

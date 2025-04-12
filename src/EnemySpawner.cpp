// Enemy Spawn Manager
#include "EnemySpawner.hpp"
#include <cstdlib>
#include <iostream>

#include "Message.hpp"


//Legacy UNUSED
EnemySpawner::EnemySpawner(float spawnInterval, unsigned int screenWidth)
    : spawnInterval(spawnInterval), screenWidth(screenWidth) {}

EnemySpawner::EnemySpawner(unsigned int screenWidth)
    : screenWidth(screenWidth), currentWaveIndex(-1), enemiesSpawnedInWave(0),
      waveComplete(false), allWavesComplete(false), waveDelayDuration(0.f), waveState(WaveState::Idle) {
    reset();
}

void EnemySpawner::reset() 
{
    currentWaveIndex = -1;
    enemiesSpawnedInWave = 0;
    waveComplete = false;
    allWavesComplete = false;
    spawnClock.restart();
    waveDelayClock.restart();
    waves.clear();

    waves.push_back(Wave{ 5, 2.0f });
    waves.push_back(Wave{ 8, 1.5f });
    waves.push_back(Wave{ 12, 1.0f });

    waveState = WaveState::Idle;

    postMessage("[WaveSpawner] Waves reset. Ready to start.");
}


void EnemySpawner::startNextWave() 
{
    currentWaveIndex++;
    enemiesSpawnedInWave = 0;
    waveComplete = false;
    waveState = WaveState::StartingWave;
    spawnClock.restart();
    waveDelayClock.restart();
    waveDelayDuration = 3.0f;
    postMessage("Wave " + std::to_string(currentWaveIndex + 1));
}


void EnemySpawner::update(std::vector<std::unique_ptr<Enemy>>& enemies) 
{
    switch (waveState) {
        case WaveState::Idle:
            break;
    
        case WaveState::StartingWave:
            if (waveDelayClock.getElapsedTime().asSeconds() >= waveDelayDuration) {
                waveState = WaveState::Spawning;
                spawnClock.restart();
            }
            break;
    
        case WaveState::Spawning:
            const Wave& currentWave = waves[currentWaveIndex];

            if (enemiesSpawnedInWave < currentWave.totalEnemies) {
                if (spawnClock.getElapsedTime().asSeconds() > currentWave.spawnInterval) {
                    spawnEnemy(enemies);
                }
            } else if (!waveComplete) {
                postMessage("[WaveSpawner] Wave " + std::to_string(currentWaveIndex + 1) + " complete.\n");
                waveComplete = true;
            }
            
            if (waveDelayClock.getElapsedTime().asSeconds() >= waveDelayDuration) {
                currentWaveIndex++;
                waveState = WaveState::Spawning;
                postMessage("Wave " + std::to_string(currentWaveIndex + 1) + " starting!");
                spawnWave(currentWaveIndex);
            }
            break;
        
        case WaveState::EndingWave:
            break;
        
        default:
            break;
    }
}

WaveState EnemySpawner::getWaveState() const
{
    return waveState;
}

bool EnemySpawner::isFirstWaveSpawned() const {
    return firstWaveSpawned;
}

bool EnemySpawner::isWaveComplete() const {
    return waveComplete;
}

bool EnemySpawner::isAllWavesComplete() const {
    return allWavesComplete;
}

//PRIVATE

float EnemySpawner::randomX() {
    return static_cast<float>(std::rand() % static_cast<int>(screenWidth - 40)) + 20.f;
}


void EnemySpawner::spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemies) {
    float x = randomX();
    enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(x, -40.f)));
    enemiesSpawnedInWave++;
    spawnClock.restart();
}
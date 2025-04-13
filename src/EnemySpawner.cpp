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
}


void EnemySpawner::update(std::vector<std::unique_ptr<Enemy>>& enemies) 
{
    switch (waveState) {
        case WaveState::Idle:
            break;
    
        case WaveState::StartingWave:
            postMessage("Wave " + std::to_string(currentWaveIndex + 1));
            if (waveDelayClock.getElapsedTime().asSeconds() >= waveDelayDuration) {
                waveState = WaveState::Spawning;
                spawnClock.restart();
            }
            break;
    
        case WaveState::Spawning:
            if (enemiesSpawnedInWave < waves[currentWaveIndex].totalEnemies) {
                if (spawnClock.getElapsedTime().asSeconds() > waves[currentWaveIndex].spawnInterval) {
                    spawnEnemy(enemies);
                    spawnClock.restart();
                }
            } else if (enemies.empty()) {
                waveState = WaveState::EndingWave;
                waveDelayClock.restart();
                waveDelayDuration = 5.0f;
                postMessage("Wave " + std::to_string(currentWaveIndex + 1) + " complete!");
            }
            break;
        
        case WaveState::EndingWave:
            if (waveDelayClock.getElapsedTime().asSeconds() >= waveDelayDuration) {
                waveState = WaveState::Idle;
                if (currentWaveIndex + 1 >= waves.size()) {
                    allWavesComplete = true;
                }
            }
            break;
        
        default:
            break;
    }
}

bool EnemySpawner::isWaveComplete() const {
    return waveComplete;
}

bool EnemySpawner::isAllWavesComplete() const {
    return allWavesComplete;
}

int EnemySpawner::getCurrentWaveIndex() const {
    return currentWaveIndex;
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
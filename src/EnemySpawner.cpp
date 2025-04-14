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
    waveState = WaveState::Idle;

    postMessage("[WaveSpawner] Waves reset."); // TODO: add DEBUG MESSAGE in game
}

//LEGACY for author's minimal reference only, DO NOT USE
void EnemySpawner::startNextWave() 
{
    currentWaveIndex++;
    enemiesSpawnedInWave = 0;
    waveComplete = false;
}

void EnemySpawner::startSpawn()
{
//may need to guard some buggy stuff here; check for wave length first
// Entry point for adding in different kinds of waves
// Potentially add in another function for loadingWaves
    waves.push_back(Wave{ 5, 2.0f });
    waves.push_back(Wave{ 8, 1.5f });
    waves.push_back(Wave{ 12, 1.0f });
    currentWaveIndex = -1;
// TODO: Catch for if not at Idle state
    waveState = WaveState::StartingWave;
}

void EnemySpawner::update(std::vector<std::unique_ptr<Enemy>>& enemies) 
{
    if (waveState != previousWaveState) {
        handleStateEnter(waveState);
        previousWaveState = waveState;
    }
    switch (waveState) {
        case WaveState::Idle:
            break;
    
        case WaveState::StartingWave:        
            if (waveDelayClock.getElapsedTime().asSeconds() >= waveDelayDuration) {
                waveState = WaveState::Spawning;
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
            }
            break;
        
        case WaveState::EndingWave:
            if (waveDelayClock.getElapsedTime().asSeconds() >= waveDelayDuration) {
                if (currentWaveIndex + 1 >= waves.size()) {
                    waveState = WaveState::EndingAllWaves;
                } else {
                    waveState = WaveState::StartingWave;
                }
            }
            break;
        
        case WaveState::EndingAllWaves:
            if (waveDelayClock.getElapsedTime().asSeconds() >= waveDelayDuration) {
                waveState = WaveState::Idle;
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

void EnemySpawner::handleStateEnter(WaveState state) 
{
    switch(state) {
        case WaveState::Idle: onEnterIdle(); break;
        case WaveState::StartingWave: onEnterStartingWave(); break;
        case WaveState::Spawning: onEnterSpawning(); break;
        case WaveState::EndingWave: onEnterEndingWave(); break;
        case WaveState::EndingAllWaves: onEnterEndingAllWaves(); break;
        default: break;
    }
}

void EnemySpawner::onEnterIdle()
{
}

void EnemySpawner::onEnterStartingWave()
{
    currentWaveIndex++;
    enemiesSpawnedInWave = 0;
    waveComplete = false;
    postMessage("Wave " + std::to_string(currentWaveIndex + 1));
    waveDelayClock.restart();
    waveDelayDuration = 5.0f;
}

void EnemySpawner::onEnterSpawning()
{
    spawnClock.restart();
}

void EnemySpawner::onEnterEndingWave()
{
    postMessage("Wave " + std::to_string(currentWaveIndex + 1) + " complete!");
    waveDelayClock.restart();
    waveDelayDuration = 5.0f;
}

void EnemySpawner::onEnterEndingAllWaves()
{
    allWavesComplete = true;
    postMessage("All Waves Complete");
    waveDelayClock.restart();
    waveDelayDuration = 5.0f;
}


float EnemySpawner::randomX() {
    return static_cast<float>(std::rand() % static_cast<int>(screenWidth - 40)) + 20.f;
}

void EnemySpawner::spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemies) {
    float x = randomX();
    enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(x, -40.f)));
    enemiesSpawnedInWave++;
    spawnClock.restart();
}
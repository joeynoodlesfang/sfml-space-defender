#pragma once

/////////////////////////////////////////////
// Handles all changes to game state
/////////////////////////////////////////////

#include <vector>
#include <memory>

#include "IEnemyObserver.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

class GameManager : public IEnemyObserver {
public:
    // Singleton pattern
    static GameManager& getInstance() {
        static GameManager instance;
        return instance;
    }
    
    void handleInput();
    void update(float deltaTime, std::vector<std::unique_ptr<Enemy>>& enemies);
    void onEnemyEscaped() override;
private:
    Player player;
    std::vector<std::unique_ptr<Bullet>> bullets;
    sf::Clock bulletSpawnCDClock; 
    
    void spawnBullet();
    void updateBullets(float deltaTime);
    void handleBulletEnemyCollisions(std::vector<std::unique_ptr<Enemy>>& enemies);
    void removeOffscreenBullets();
};
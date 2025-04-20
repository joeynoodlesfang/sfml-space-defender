#pragma once

/////////////////////////////////////////////
// Handles all changes to game state
/////////////////////////////////////////////


#include "IEnemyObserver.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

class GameManager : public IEnemyObserver {
public:
    void handleInput();
    void update(float deltaTime);
    void onEnemyEscaped() override;
private:
    Player player;
    std::vector<std::unique_ptr<Bullet>> bullets;
    sf::Clock bulletSpawnCDClock; 
    
    void spawnBullet();
    void updateBullets(float deltaTime);
};
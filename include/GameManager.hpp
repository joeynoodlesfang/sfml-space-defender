#pragma once

/////////////////////////////////////////////
// Handles all changes to game state
/////////////////////////////////////////////

#include <vector>
#include <memory>

#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "EnemySpawner.hpp"


class GameManager {
public:
    // Singleton pattern
    static GameManager& getInstance() {
        static GameManager instance;
        return instance;
    }
    
    #warning understand how this works!
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    GameManager(GameManager&&) = delete;
    GameManager& operator=(GameManager&&) = delete;

    void init(sf::Font& font); //
    void handleInput();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isGameOver() const; //

    void onEnemyEscaped() override;

    void addPlayerObserver(std::shared_ptr<IPlayerObserver> observer);
    void addBulletObserver(std::shared_ptr<IBulletObserver> observer);
    void addEnemyObserver(std::shared_ptr<IEnemyObserver> observer);
private:
    GameManager(); // ? private because singleton?
    Player player;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Enemy>> enemies;
    EnemySpawner spawner;

    sf::Clock bulletSpawnCDClock; 
    sf::Text debugText;

    // Observer lists
    std::vector<std::shared_ptr<IPlayerObserver>> playerObservers;
    std::vector<std::shared_ptr<IBulletObserver>> bulletObservers;
    std::vector<std::shared_ptr<IEnemyObserver>> enemyObservers;


    bool waitingForPlayerToStartSpawningEnemies;
    bool gameInitialized;
    
    void spawnBullet();
    void updateBullets(float deltaTime);
    void handleBulletEnemyCollisions(std::vector<std::unique_ptr<Enemy>>& enemies);
    void removeOffscreenBullets();

    void updateDebugText();
    bool setupDebugText(sf::Font& font);
};
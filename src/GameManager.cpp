#include "GameManager.hpp"
#include "EntityUtils.hpp" //TODO should this be here or in hpp?
#include "GameConfig.hpp"

//TODO
//Make sure GameManager is singleton as well (does that make sense)
//Handling bullet collision

GameManager::GameManager() : waitingForPlayerToStartSpawningEnemies(true)
    , spawner(GameConfig::get().getScreenWidth())
    , gameInitialized(false)
{
}

void GameManager::init(sf::Font& font)
{
    if (!gameInitialized) {
        setupDebugText(font);
        gameInitialized = true;
    }
}

void GameManager::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        spawnBullet();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        bullets.clear();
    }
}

void GameManager::update(float deltaTime, std::vector<std::unique_ptr<Enemy>>& enemies) 
{
    player.update(deltaTime);
    updateBullets(deltaTime);
    handleBulletEnemyCollisions(enemies);
    removeOffscreenBullets();
}

void GameManager::onEnemyEscaped()
{
    //TODO Should not be health damage, but some count reduction
    player.takeDamage(10);
}


//PRIVATE

void GameManager::spawnBullet()
{
    if (bulletSpawnCDClock.getElapsedTime().asSeconds() > 0.2f) {
        bullets.push_back(std::make_unique<Bullet>(player.getPosition()));
        bulletSpawnCDClock.restart();
    }
}

void GameManager::updateBullets(float deltaTime)
{
    updateEntities(bullets, deltaTime);
}

//TODO try removing the ampersand to make it pass by value
void GameManager::handleBulletEnemyCollisions(std::vector<std::unique_ptr<Enemy>>& enemies)
{
    for (auto& bullet : bullets) {
        sf::FloatRect bulletBounds = bullet->getBounds();
        for (auto& enemy : enemies) {
            if (bulletBounds.findIntersection(enemy->getBounds())) {
                bullet->markForDeletion();
                enemy->markForDeletion();
                break;
            }
        }
    }
}

void GameManager::removeOffscreenBullets()
{
    int screenHeight = GameConfig::get().getScreenHeight();
    removeEntitiesIf(bullets, [&config](const std::unique_ptr<Bullet>& bullet) {
        return bullet->isOffScreen(config.getScreenHeight()) || bullet->isMarkedForDeletion();
    });
}

bool GameManager::setupDebugText(sf::Font& font)
{
    debugText.setFont(font);
    debugText.setCharacterSize(16);
    debugText.setFillColor(sf::Color::White);
    debugText.setPosition({10.f, 10.f});
    return true;
}

void GameManager::updateDebugText()
{
    debugText.setString(
        "Enemies: " + std::to_string(enemies.size()) +
        "\nBullets: " + std::to_string(bullets.size()) + 
        "\nHealth: " + std::to_string(player.getHealth()));
}
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <memory>

#include "GameConfig.hpp"
#include "EntityUtils.hpp"

#include "Player.hpp"

#include "Bullet.hpp"
#include <vector>
#include <algorithm>

#include "Enemy.hpp"
#include "EnemySpawner.hpp"
#include <cstdlib> // rand
#include <ctime> // srand

#include <filesystem>

#include "Message.hpp"

static const unsigned int defaultScreenWidth = 1200u;
static const unsigned int defaultScreenHeight = 1000u;

std::filesystem::path exePath = std::filesystem::canonical("/proc/self/exe");

static bool loadFonts(sf::Font& font) 
{
    std::filesystem::path fontPath = exePath.parent_path().parent_path().parent_path()
        / "assets" / "fonts" / "arial.ttf";

    if (!font.openFromFile(fontPath.string())) {
        std::cout << "Failed to load font!" << std::endl;
        return false;
    }
    std::cout << "[DEBUG] Loaded font from: " << fontPath << "\n";
    return true;
}

static bool setupDebugText(sf::Text& debugText)
{
    // debugText.setCharacterSize(16);
    debugText.setFillColor(sf::Color::White);
    debugText.setPosition({10.f, 10.f});
    return true;
}

static void updateDebugText(sf::Text& debugText,
    const std::vector<std::unique_ptr<Bullet>>& bullets,
    const std::vector<std::unique_ptr<Enemy>>& enemies,
    const int playerHealth)
{
    debugText.setString(
        "Enemies: " + std::to_string(enemies.size()) +
        "\nBullets: " + std::to_string(bullets.size()) + 
        "\nHealth: " + std::to_string(playerHealth));
}

int main()
{
    std::cout << "Starting Space Defender v-1.3" << std::endl;

    sf::Font font;
    if (!loadFonts(font)) return 1;
    sf::Text debugText(font, "", 16);
    if (!setupDebugText(debugText)) return 1;
    GameMessageManager::init(font);
    GameMessageManager& messageManager = GameMessageManager::getInstance();

    GameConfig& config = GameConfig::get();
    config.setScreenWidth(defaultScreenWidth);
    config.setScreenHeight(defaultScreenHeight);

    auto window = sf::RenderWindow(sf::VideoMode({config.getScreenWidth(), config.getScreenHeight()}), "Space Defender");
    window.setFramerateLimit(144);
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed RNG

    Player player;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Enemy>> enemies;
    EnemySpawner spawner(config.getScreenWidth());

    sf::Clock clock;
    sf::Clock fireCooldownClock; 

    bool waitingForPlayerToStartSpawningEnemies = true;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    
        // Handle bullet spawn
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (fireCooldownClock.getElapsedTime().asSeconds() > 0.2f) {
                sf::Vector2f spawnPos = player.getPosition();
                bullets.push_back(std::make_unique<Bullet>(spawnPos));
                fireCooldownClock.restart();
            }
        }

        // Handle enemy spawn
        //TODO: fix edge spawning (current player too big)

        // Reset 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
            bullets.clear();
            enemies.clear();
            spawner.reset();
            waitingForPlayerToStartSpawningEnemies = true;
        }
        
        
        // Updates
        spawner.update(enemies);
        player.update(deltaTime);
        updateEntities(bullets, deltaTime);
        updateEntities(enemies, deltaTime);
        messageManager.update();
                
        // Spawn
        if (waitingForPlayerToStartSpawningEnemies && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            spawner.startSpawn();
            waitingForPlayerToStartSpawningEnemies = false;
        }

        // Collision detection (bullets vs enemies)
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

        // Collision detection (enemies vs player)
        for (auto& enemy : enemies) {
            if (enemy->getBounds().findIntersection(player.getBounds())) {
                enemy->markForDeletion();
                player.takeDamage(1);
                std::cout << "Player Hit!";
            
                if (player.isDead()) {
                    window.close();
                }
            }
        }

        removeEntitiesIf(bullets, [&config](const std::unique_ptr<Bullet>& bullet) {
                return bullet->isOffScreen(config.getScreenHeight()) || bullet->isMarkedForDeletion();
            });

        removeEntitiesIf(enemies, [&config](const std::unique_ptr<Enemy>& enemy) {
                return enemy->isOffScreen(config.getScreenHeight()) || enemy->isMarkedForDeletion();
            });

        updateDebugText(debugText, bullets, enemies, player.getHealth());
        
        window.clear();

        // Draw 
        player.draw(window);
        drawEntities(bullets, window);
        drawEntities(enemies, window);
        window.draw(debugText);
        messageManager.draw(window);

        window.display();
    }

    return 0;
}
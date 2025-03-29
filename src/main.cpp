#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "Player.hpp"

#include "Bullet.hpp"
#include <vector>
#include <algorithm>

#include "Enemy.hpp"
#include <cstdlib> // rand
#include <ctime> // srand

#include <filesystem>

static const unsigned int screenWidth = 1200u;
static const unsigned int screenHeight = 1000u;

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
    const std::vector<Bullet>& bullets,
    const std::vector<Enemy>& enemies)
{
    debugText.setString(
    "Enemies: " + std::to_string(enemies.size()) +
    "\nBullets: " + std::to_string(bullets.size()));
}

int main()
{
    sf::Font font;
    if (!loadFonts(font)) return 1;
    sf::Text debugText(font, "", 16);
    if (!setupDebugText(debugText)) return 1;

    auto window = sf::RenderWindow(sf::VideoMode({screenWidth, 1000u}), "Space Defender");
    window.setFramerateLimit(144);
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed RNG

    Player player;

    std::vector<Bullet> bullets;
    sf::Clock clock;
    sf::Clock fireCooldownClock; 
    
    std::vector<Enemy> enemies;
    sf::Clock enemySpawnClock;
    float enemySpawnInterval = 3.0f;

    std::cout << "Starting Space Defender v-1.2" << std::endl;



    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    
        // Handle shooting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (fireCooldownClock.getElapsedTime().asSeconds() > 0.2f) {
                sf::Vector2f spawnPos = player.getPosition();
                bullets.emplace_back(spawnPos);
                fireCooldownClock.restart();
            }
        }

        // Handle enemy spawn
        //TODO: fix edge spawning (current player too big)
        if (enemySpawnClock.getElapsedTime().asSeconds() > enemySpawnInterval) {
            float x = static_cast<float>(std::rand() % static_cast<int>(screenWidth - 40)) + 20.f;
            enemies.emplace_back(sf::Vector2f(x, -40.f));
            enemySpawnClock.restart();
        }

        // Updates
        player.update(deltaTime);
        
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].update(deltaTime);
        }
        auto bulletNewEnd = std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) {
            return b.isOffScreen(screenHeight);
        });
        bullets.erase(bulletNewEnd, bullets.end());

        for (size_t i = 0; i < enemies.size(); i++) {
            enemies[i].update(deltaTime);
        }
        auto enemiesNewEnd = std::remove_if(enemies.begin(), enemies.end(),
        [] (const Enemy& e) {
            return e.isOffScreen(screenHeight);
        });
        enemies.erase(enemiesNewEnd, enemies.end());

        updateDebugText(debugText, bullets, enemies);
        
        window.clear();

        // Draw
        player.draw(window);
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].draw(window);
        }
        for (size_t i = 0; i < enemies.size(); i++) {
            enemies[i].draw(window);
        }
        window.draw(debugText);
        window.display();
    }

    return 0;
}
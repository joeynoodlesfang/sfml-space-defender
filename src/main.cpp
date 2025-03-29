#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <memory>
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
    const std::vector<std::unique_ptr<GameObject>>& gameObjects)
{
    int bulletCount = 0;
    int enemyCount = 0;

    for (const auto& obj : gameObjects) {
        if (dynamic_cast<const Bullet*>(obj.get()))
            ++bulletCount;
        else if (dynamic_cast<const Enemy*>(obj.get()))
            ++enemyCount;
    }

    debugText.setString(
        "Enemies: " + std::to_string(enemyCount) +
        "\nBullets: " + std::to_string(bulletCount));
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
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    sf::Clock clock;
    sf::Clock fireCooldownClock; 
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
    
        // Handle bullet spawn
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (fireCooldownClock.getElapsedTime().asSeconds() > 0.2f) {
                sf::Vector2f spawnPos = player.getPosition();
                gameObjects.push_back(std::make_unique<Bullet>(spawnPos));
                fireCooldownClock.restart();
            }
        }

        // Handle enemy spawn
        //TODO: fix edge spawning (current player too big)
        if (enemySpawnClock.getElapsedTime().asSeconds() > enemySpawnInterval) {
            float x = static_cast<float>(std::rand() % static_cast<int>(screenWidth - 40)) + 20.f;
            gameObjects.push_back(std::make_unique<Enemy>(sf::Vector2f(x, -40.f)));
            enemySpawnClock.restart();
        }

        // Updates
        player.update(deltaTime);
        
        for (auto& obj : gameObjects) {
            obj->update(deltaTime);
        }
        
        // Erases
        gameObjects.erase(
            std::remove_if(gameObjects.begin(), gameObjects.end(),
                [](const std::unique_ptr<GameObject>& obj) {
                    auto* bounded = dynamic_cast<ScreenBounded*>(obj.get());
                    return bounded && bounded->isOffScreen(screenHeight);
                }),
            gameObjects.end());
    

        updateDebugText(debugText, gameObjects);
        
        window.clear();

        // Draw
        player.draw(window);
        for (auto& obj : gameObjects) {
            obj->draw(window);
        }        
        window.draw(debugText);
        window.display();
    }

    return 0;
}
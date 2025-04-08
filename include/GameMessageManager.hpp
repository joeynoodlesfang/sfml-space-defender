#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>

struct GameMessage {
    std::string text;
    sf::Clock timer;
    float duration;
};

class GameMessageManager {
public:
    static void init(sf::Font& font);
    static GameMessageManager& getInstance();

    void addMessage(const std::string& message, float duration = 2.0f);
    void update();
    void draw(sf::RenderWindow& window);

private:
    GameMessageManager(sf::Font& font);
    sf::Font& font;
    std::vector<GameMessage> messages;
};

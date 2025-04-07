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
    GameMessageManager(sf::Font& font);

    void addMessage(const std::string& message, float duration = 2.0f);
    void update();
    void draw(sf::RenderWindow& window);

private:
    sf::Font& font;
    std::vector<GameMessage> messages;
};

#include "GameMessageManager.hpp"

static GameMessageManager* instance = nullptr;

void GameMessageManager::init(sf::Font& font) {
    if (!instance)
        instance = new GameMessageManager(font);
}

GameMessageManager::GameMessageManager(sf::Font& font) : font(font) {}

GameMessageManager& GameMessageManager::getInstance() {
    if (!instance) {
        throw std::runtime_error("GameMessageManager::init() must be called before getInstance()");
    }
    return *instance;
}

void GameMessageManager::addMessage(const std::string& message, float duration) {
    messages.push_back({ message, sf::Clock(), duration });
}

void GameMessageManager::update() {
    messages.erase(
        std::remove_if(messages.begin(), messages.end(),
            [](const GameMessage& msg) {
                return msg.timer.getElapsedTime().asSeconds() > msg.duration;
            }),
        messages.end()
    );
}

void GameMessageManager::draw(sf::RenderWindow& window) {
    float y = 30.f;
    for (const GameMessage& msg : messages) {
        sf::Text text(font, msg.text, 24);
        text.setFillColor(sf::Color::Yellow);
        text.setPosition({20.f, y});
        window.draw(text);
        y += 30.f;
    }
}

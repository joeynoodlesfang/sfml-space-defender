#pragma once

struct GameConfig {
    int screenWidth = 800;
    int screenHeight = 600;
    bool fullscreen = false;

    static GameConfig& get() {
        static GameConfig instance;
        return instance;
    }

private:
    GameConfig() = default;
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;
};

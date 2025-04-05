#pragma once

struct GameConfig {
    unsigned int screenWidth = 800;
    int screenHeight = 600;
    bool fullscreen = false;

    static GameConfig& get() {
        static GameConfig instance;
        return instance;
    }

    unsigned int getScreenWidth() const { return screenWidth; }
    void setScreenWidth(unsigned int width) { screenWidth = width; }

    unsigned int getScreenHeight() const { return screenHeight; }
    void setScreenHeight(unsigned int height) { screenHeight = height; }

    bool isFullscreen() const { return fullscreen; }
    void setFullscreen(bool enable) { fullscreen = enable; }

private:
    GameConfig() = default;
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;
};

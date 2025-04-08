#pragma once

struct GameConfig {
    unsigned int screenWidth = 800;
    int screenHeight = 600;
    bool fullscreen = false;

    static GameConfig& get() {
        static GameConfig instance;
        return instance;
    }

    void setScreenWidth(unsigned int width) { screenWidth = width; }
    void setScreenHeight(unsigned int height) { screenHeight = height; }
    void setFullscreen(bool enable) { fullscreen = enable; }
    
    unsigned int getScreenWidth() const { return screenWidth; }
    unsigned int getScreenHeight() const { return screenHeight; }
    bool isFullscreen() const { return fullscreen; }

private:
    GameConfig() = default;
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;
};

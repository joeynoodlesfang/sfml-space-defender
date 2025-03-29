#pragma once

class ScreenBounded {
public:
    virtual bool isOffScreen(unsigned int screenHeight) const = 0;
    virtual ~ScreenBounded() = default;
};
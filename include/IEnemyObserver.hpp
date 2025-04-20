#pragma once

class IEnemyObserver {
public:
    virtual void onEnemyEscaped() = 0;
    virtual ~IEnemyObserver() = default;
};

//TODO: why is only destructor in here
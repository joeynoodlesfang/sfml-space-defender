## SFML Space Defender
<em>
A 2D space shooter game built with SFML, demonstrating Object-Oriented Programming (OOP) and design patterns like Observer, Factory, and State.
</em>

<br>
<br>

## Game Features
<ul>
  <li>Player-controlled spaceship</li>
  <li>Enemy waves with different attack behaviors</li>
  <li>Shooting mechanics with bullets and collisions</li>
  <li>Score tracking and UI updates (Observer Pattern)</li>
  <li>Game state management (Menu, Playing, Game Over) (State Pattern)</li>
  <li>Sound and effects using SFML’s Audio module</li>
</ul>

<br>
<br>

## Proposed Structure
```
SFML-Space-Defender
├── src/                        # Source files
│   ├── main.cpp                # Entry point
│   ├── Game.cpp                # Game loop & state manager
│   ├── Player.cpp              # Player spaceship class
│   ├── Enemy.cpp               # Enemy class (Observer pattern)
│   ├── Bullet.cpp              # Bullet mechanics
│   ├── ScoreManager.cpp        # Observer that tracks score
│   ├── SoundManager.cpp        # Observer that plays sounds
│   ├── EnemyFactory.cpp        # Factory for creating enemies
│   ├── GameState.cpp           # State Pattern for game states
│   ├── Config.cpp              # Singleton for game settings
└── include/                    # Header files
│   ├── Game.h
│   ├── Player.h
│   ├── Enemy.h
│   ├── Bullet.h
│   ├── ScoreManager.h
│   ├── SoundManager.h
│   ├── EnemyFactory.h
│   ├── GameState.h
│   ├── Config.h
└── assets/                     # Graphics & sounds
│   ├── spaceship.png
│   ├── enemy.png
│   ├── laser.wav
└── CMakeLists.txt              # CMake build configuration
└── README.md                   # Project description & setup instructions
└── .gitignore                   # Ignore build files
```

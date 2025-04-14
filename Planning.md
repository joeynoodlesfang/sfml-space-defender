
## TODO
### Major Features and Critical Bugs
<ol>
  <li>Add health mechanic</li>
  <li>Add enemy touch / reach bottom mechanic</li>
  <li>Move Wave display text to below debug text</li>
  <li>Add basic sprites for player and enemy</li>
  <li>Add background</li>
  <li>Add sound</li>
  <li>Add instructions for play and install</li>
</ol>

### Minor Features and Bugfixes
<ol>
  <li>Reduce game width without changing screen width</li>
  <li>Fix wave reset spam (potentially adding wave reset state to update)</li>
</ol>


## Proposed Structure
```
SFML-Space-Defender
├── src/                        
│   ├── main.cpp                # Entry point
│   ├── Game.cpp                # Game loop & state manager (yet to decide to keep or not)
│   ├── Player.cpp              # Player spaceship
│   ├── Enemy.cpp               # Enemy class (Observer pattern)
│   ├── EnemySpawner.cpp        # Handles waves and enemy spawning
│   ├── Bullet.cpp              # Bullet mechanics
│   ├── ScoreManager.cpp        # Observer that tracks score
│   ├── SoundManager.cpp        # Observer that plays sounds
│   ├── EnemyFactory.cpp        # Factory for creating enemies
│   ├── GameState.cpp           # State Pattern for game states
│   ├── (GameConfig.cpp)        # Singleton for game settings (currently all in hpp)
│   ├── GameMessageManager.cpp  # Manages game messages
└── include/                    # Header files
│   ├── Game.h
│   ├── GameObject.hpp          # Abstract for all interacting game objects
│   ├── ScreenObject.h          # Mixin for objects exiting/(entering) screen
│   ├── Player.hpp
│   ├── Enemy.hpp
│   ├── EnemySpawner.hpp        
│   ├── Bullet.hpp
│   ├── ScoreManager.h
│   ├── SoundManager.h
│   ├── EnemyFactory.h
│   ├── GameState.h
│   ├── GameConfig.hpp          # Singleton for game settings (currently all in hpp)
│   ├── EntityUtils.hpp         # Helper template fxns for iterating object lists in main/game loop
│   ├── GameMessageManager.hpp  
│   ├── Message.hpp             # Message Helper (Debug will be added here(?))
└── assets/                     # Graphics & sounds
│   ├── fonts/
│   |   ├── arial.ttf           # For debug texts
│   ├── spaceship.png
│   ├── enemy.png
│   ├── laser.wav
└── CMakeLists.txt             
└── README.md                   

cmake_minimum_required(VERSION 3.28)
project(SpaceDefender LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(include)

add_executable(SpaceDefender 
    src/main.cpp
    src/Player.cpp
    src/Bullet.cpp
    src/Enemy.cpp
    src/EnemySpawner.cpp
    src/GameMessageManager.cpp
    src/GameManager.cpp
    src/EventDispatcher.cpp
)
target_compile_features(SpaceDefender PRIVATE cxx_std_17)
target_link_libraries(SpaceDefender PRIVATE SFML::Graphics)
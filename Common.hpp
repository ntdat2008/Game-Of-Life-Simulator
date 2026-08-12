#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

enum class Scene {
    MainMenu,
    HowToPlay,
    Settings,
    Credits,
    Simulation,
};

struct GameData {
    std::string gameVersion = "1.0";

    sf::RenderWindow window;

    AssetManager assets;

    Scene previousScene = Scene::MainMenu;
    Scene currentScene = Scene::MainMenu;

    void setScene(const Scene& scene);

    int timeIntervalMultipiler = 10;
    float timeInterval = 0.50f;
};
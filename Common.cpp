#include "Common.hpp"

void GameData::setScene(const Scene &scene) {
    previousScene = currentScene;
    currentScene = scene;
}
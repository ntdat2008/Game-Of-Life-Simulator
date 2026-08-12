#include "AssetManager.hpp"
#include <iostream>

void AssetManager::loadFont(const std::string& name, const std::string& filename) {
    sf::Font font;
    if (!font.openFromFile(filename)) {
        std::cout << "[AssetManager] ERROR: Failed to load < " << filename << " > !\n";
        return;
    }
    fonts[name] = font;
}

const sf::Font& AssetManager::getFont(const std::string& name) const {
    return fonts.at(name);
}
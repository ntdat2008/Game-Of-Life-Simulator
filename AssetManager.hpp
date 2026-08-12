#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager {
private:
    std::map<std::string, sf::Font> fonts;

public:
    AssetManager() = default;

    void loadFont(const std::string& name, const std::string& filename);

    const sf::Font& getFont(const std::string& fontName) const;
};
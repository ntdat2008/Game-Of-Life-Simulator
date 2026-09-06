#include "Common.hpp"
#include "MainMenu.hpp"
#include "HowToPlay.hpp"
#include "Settings.hpp"
#include "Credits.hpp"
#include "Simulation.hpp"

int main() {
    GameData data;
    
    #pragma region //! Window
    data.window.create(sf::VideoMode({1200, 800}), "Game Of Life Simulator", sf::Style::Titlebar | sf::Style::Close);
    data.window.setFramerateLimit(60);

    sf::Image windowLogo;
    if (windowLogo.loadFromFile("assets/logo/logo.png")) {
        data.window.setIcon(windowLogo.getSize(), windowLogo.getPixelsPtr());
    }
    #pragma endregion

    #pragma region //! Assets
    data.assets.loadFont("orbitron_regular", "assets/fonts/Orbitron-Regular.ttf");
    data.assets.loadFont("orbitron_bold", "assets/fonts/Orbitron-Bold.ttf");
    #pragma endregion

    #pragma region //! Game loop
    while (data.window.isOpen()) {
        switch(data.currentScene) {
            case Scene::MainMenu:
                run_MainMenu(data);
                break;

            case Scene::HowToPlay:
                run_HowToPlay(data);
                break;

            case Scene::Settings:
                run_Settings(data);
                break;

            case Scene::Credits:
                run_Credits(data);
                break;

            case Scene::Simulation:
                run_Simulation(data);
                break;
        }
    }
    #pragma endregion

    return 0;
}

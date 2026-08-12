#include "MainMenu.hpp"

void run_MainMenu(GameData& data) {
    #pragma region //! Define
    data.window.setView(data.window.getDefaultView());

    static bool isInitialized = false;
    
    static std::optional<sf::Text> gameVersionText;

    static std::optional<sf::Text> titleText;

    static sf::RectangleShape startButton;
    static std::optional<sf::Text> startButtonText;

    static sf::RectangleShape howToPlayButton;
    static std::optional<sf::Text> howToPlayButtonText;

    static sf::RectangleShape settingsButton;
    static std::optional<sf::Text> settingsButtonText;

    static sf::RectangleShape creditsButton;
    static std::optional<sf::Text> creditsButtonText;

    static sf::RectangleShape exitButton;
    static std::optional<sf::Text> exitButtonText;

    static bool isPressingStart = false;
    static bool isPressingHowToPlay = false;
    static bool isPressingSettings = false;
    static bool isPressingCredits = false;
    static bool isPressingExit = false;
    
    if (!isInitialized) {
        isInitialized = true;

        #pragma region //! Assets
        const sf::Font& orbitron_regular = data.assets.getFont("orbitron_regular");
        #pragma endregion

        #pragma region //! Initialize title
        titleText.emplace(orbitron_regular, "Game Of Life\nSIMULATOR", 75.0f);
        titleText->setFillColor(sf::Color::White);
        titleText->setOrigin({
            titleText->getLocalBounds().position.x + titleText->getLocalBounds().size.x / 2.0f,
            titleText->getLocalBounds().position.y + titleText->getLocalBounds().size.y / 2.0f
        });
        titleText->setPosition({600.0f, 200.0f});
        #pragma endregion

        #pragma region
        gameVersionText.emplace(orbitron_regular, "Version: " + data.gameVersion, 30.0f);
        gameVersionText->setOrigin({
            gameVersionText->getGlobalBounds().position.x + gameVersionText->getGlobalBounds().size.x / 2.0f,
            gameVersionText->getGlobalBounds().position.y + gameVersionText->getGlobalBounds().size.y / 2.0f,
        });
        gameVersionText->setPosition({110.0f, 770.0f});
        gameVersionText->setFillColor(sf::Color::White);
        #pragma endregion

        #pragma region //! Initialize [Start]
        startButton.setSize({300.0f, 50.0f});
        startButton.setOrigin(startButton.getSize() / 2.0f);
        startButton.setPosition({600.0f, 400.0f});
        startButton.setFillColor(sf::Color::White);

        startButtonText.emplace(orbitron_regular, "Start", 40.0f);
        startButtonText->setFillColor(sf::Color::Black);
        startButtonText->setOrigin({
            startButtonText->getLocalBounds().position.x + startButtonText->getLocalBounds().size.x / 2.0f,
            startButtonText->getLocalBounds().position.y + startButtonText->getLocalBounds().size.y / 2.0f
        });
        startButtonText->setPosition({600.0f, 400.0f});
        #pragma endregion

        #pragma region //! Initialize [How to play?]
        howToPlayButton.setSize({300.0f, 50.0f});
        howToPlayButton.setOrigin(howToPlayButton.getSize() / 2.0f);
        howToPlayButton.setPosition({600.0f, 460.0f});
        howToPlayButton.setFillColor(sf::Color::White);

        howToPlayButtonText.emplace(orbitron_regular, "How to play?", 35.0f);
        howToPlayButtonText->setFillColor(sf::Color::Black);
        howToPlayButtonText->setOrigin({
            howToPlayButtonText->getLocalBounds().position.x + howToPlayButtonText->getLocalBounds().size.x / 2.0f,
            howToPlayButtonText->getLocalBounds().position.y + howToPlayButtonText->getLocalBounds().size.y / 2.0f
        });
        howToPlayButtonText->setPosition({600.0f, 460.0f});
        #pragma endregion

        #pragma region //! Initialize [Settings]
        settingsButton.setSize({300.0f, 50.0f});
        settingsButton.setOrigin(settingsButton.getSize() / 2.0f);
        settingsButton.setPosition({600.0f, 520.0f});
        settingsButton.setFillColor(sf::Color::White);

        settingsButtonText.emplace(orbitron_regular, "Settings", 40.0f);
        settingsButtonText->setFillColor(sf::Color::Black);
        settingsButtonText->setOrigin({
            settingsButtonText->getLocalBounds().position.x + settingsButtonText->getLocalBounds().size.x / 2.0f,
            settingsButtonText->getLocalBounds().position.y + settingsButtonText->getLocalBounds().size.y / 2.0f
        });
        settingsButtonText->setPosition({600.0f, 520.0f});
        #pragma endregion

        #pragma region //! Initialize [Credits]
        creditsButton.setSize({300.0f, 50.0f});
        creditsButton.setOrigin(creditsButton.getSize() / 2.0f);
        creditsButton.setPosition({600.0f, 580.0f});
        creditsButton.setFillColor(sf::Color::White);

        creditsButtonText.emplace(orbitron_regular, "Credits", 40.0f);
        creditsButtonText->setFillColor(sf::Color::Black);
        creditsButtonText->setOrigin({
            creditsButtonText->getLocalBounds().position.x + creditsButtonText->getLocalBounds().size.x / 2.0f,
            creditsButtonText->getLocalBounds().position.y + creditsButtonText->getLocalBounds().size.y / 2.0f
        });
        creditsButtonText->setPosition({600.0f, 580.0f});
        #pragma endregion

        #pragma region //! Initialize [Exit]
        exitButton.setSize({300.0f, 50.0f});
        exitButton.setOrigin(exitButton.getSize() / 2.0f);
        exitButton.setPosition({600.0f, 640.0f});
        exitButton.setFillColor(sf::Color::White);

        exitButtonText.emplace(orbitron_regular, "Exit", 40.0f);
        exitButtonText->setFillColor(sf::Color::Black);
        exitButtonText->setOrigin({
            exitButtonText->getLocalBounds().position.x + exitButtonText->getLocalBounds().size.x / 2.0f,
            exitButtonText->getLocalBounds().position.y + exitButtonText->getLocalBounds().size.y / 2.0f
        });
        exitButtonText->setPosition({600.0f, 640.0f});
        #pragma endregion
    }
    #pragma endregion

    while (const std::optional event = data.window.pollEvent()) { //! Handle events
        if (event->is<sf::Event::Closed>()) {
            data.window.close();
        }

        if (const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                const sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(data.window));

                if (startButton.getGlobalBounds().contains(mousePos)) {
                    isPressingStart = true;
                    startButton.setFillColor(sf::Color::Black);
                    startButton.setOutlineThickness(2.0f);
                    startButton.setOutlineColor(sf::Color::White);
                    startButtonText->setFillColor(sf::Color::White);
                }
                else if (howToPlayButton.getGlobalBounds().contains(mousePos)) {
                    isPressingHowToPlay = true;
                    howToPlayButton.setFillColor(sf::Color::Black);
                    howToPlayButton.setOutlineThickness(2.0f);
                    howToPlayButton.setOutlineColor(sf::Color::White);
                    howToPlayButtonText->setFillColor(sf::Color::White);
                }
                else if (settingsButton.getGlobalBounds().contains(mousePos)) {
                    isPressingSettings = true;
                    settingsButton.setFillColor(sf::Color::Black);
                    settingsButton.setOutlineThickness(2.0f);
                    settingsButton.setOutlineColor(sf::Color::White);
                    settingsButtonText->setFillColor(sf::Color::White);
                }
                else if (creditsButton.getGlobalBounds().contains(mousePos)) {
                    isPressingCredits = true;
                    creditsButton.setFillColor(sf::Color::Black);
                    creditsButton.setOutlineThickness(2.0f);
                    creditsButton.setOutlineColor(sf::Color::White);
                    creditsButtonText->setFillColor(sf::Color::White);
                }
                else if (exitButton.getGlobalBounds().contains(mousePos)) {
                    isPressingExit = true;
                    exitButton.setFillColor(sf::Color::Black);
                    exitButton.setOutlineThickness(2.0f);
                    exitButton.setOutlineColor(sf::Color::White);
                    exitButtonText->setFillColor(sf::Color::White);
                }
            }
        }
        else if (const auto *mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseReleased->button == sf::Mouse::Button::Left) {
                const sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(data.window));

                if (startButton.getGlobalBounds().contains(mousePos) && isPressingStart) {
                    data.setScene(Scene::Simulation);
                }
                else if (howToPlayButton.getGlobalBounds().contains(mousePos) && isPressingHowToPlay) {
                    data.setScene(Scene::HowToPlay);
                }
                else if (settingsButton.getGlobalBounds().contains(mousePos) && isPressingSettings) {
                    data.setScene(Scene::Settings);
                }
                else if (creditsButton.getGlobalBounds().contains(mousePos) && isPressingCredits) {
                    data.setScene(Scene::Credits);
                }
                else if (exitButton.getGlobalBounds().contains(mousePos) && isPressingExit) { 
                    data.window.close();
                }
            }
            
            #pragma region //! Default
            isPressingStart = false;
            isPressingHowToPlay = false;
            isPressingSettings = false;
            isPressingCredits = false;
            isPressingExit = false;

            startButton.setFillColor(sf::Color::White);
            startButton.setOutlineThickness(0.0f);
            startButtonText->setFillColor(sf::Color::Black);

            howToPlayButton.setFillColor(sf::Color::White);
            howToPlayButton.setOutlineThickness(0.0f);
            howToPlayButtonText->setFillColor(sf::Color::Black);

            settingsButton.setFillColor(sf::Color::White);
            settingsButton.setOutlineThickness(0.0f);
            settingsButtonText->setFillColor(sf::Color::Black);

            creditsButton.setFillColor(sf::Color::White);
            creditsButton.setOutlineThickness(0.0f);
            creditsButtonText->setFillColor(sf::Color::Black);

            exitButton.setFillColor(sf::Color::White);
            exitButton.setOutlineThickness(0.0f);
            exitButtonText->setFillColor(sf::Color::Black);
            #pragma endregion
        }
    }

    #pragma region //! Draw and display
    data.window.clear(sf::Color::Black);

    data.window.draw(*titleText);

    data.window.draw(*gameVersionText);

    data.window.draw(startButton);
    data.window.draw(*startButtonText);

    data.window.draw(howToPlayButton);
    data.window.draw(*howToPlayButtonText);

    data.window.draw(settingsButton);
    data.window.draw(*settingsButtonText);

    data.window.draw(creditsButton);
    data.window.draw(*creditsButtonText);

    data.window.draw(exitButton);
    data.window.draw(*exitButtonText);

    data.window.display();
    #pragma endregion
}
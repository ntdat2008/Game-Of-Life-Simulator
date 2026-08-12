#include "Settings.hpp"

void run_Settings(GameData& data) {
    #pragma region //! Define
    data.window.setView(data.window.getDefaultView());

    std::ostringstream roundedTimeInterval;

    static bool isIntialized = false;

    static sf::View settingsView;

    static sf::RectangleShape titleOverlap1;
    static sf::RectangleShape titleOverlap2;
    static std::optional<sf::Text> mainText;

    static sf::RectangleShape goBackButton;
    static std::optional<sf::Text> goBackButtonText;
    static bool isPressingGoBack = false;

    static std::optional<sf::Text> generationTime_MainText;
    static sf::RectangleShape generationTime_Box;
    static std::optional<sf::Text> generationTime_DisplayedTime;
    static sf::RectangleShape generationTime_IncreaseTimeButton;
    static sf::RectangleShape generationTime_DecreaseTimeButton;
    static sf::CircleShape generationTime_upArrow;
    static sf::CircleShape generationTime_downArrow;
    static std::optional<sf::Text> generationTime_Description;
    static bool generationTime_isPressingUp = false;
    static bool generationTime_isPressingDown = false;
    #pragma endregion

    #pragma region //! Initialize
    if (!isIntialized) {
        isIntialized = true;

        settingsView.setSize(data.window.getDefaultView().getSize());
        settingsView.setCenter({data.window.getDefaultView().getCenter().x, 400.0f});

        #pragma region //! Assets
        const sf::Font &orbitron_regular = data.assets.getFont("orbitron_regular");
        #pragma endregion

        #pragma region //! Main title
        titleOverlap1.setSize({1200.0f, 115.0f});
        titleOverlap1.setFillColor(sf::Color::Black);

        titleOverlap2.setSize({1200.0f, 90.0f});
        titleOverlap2.setPosition({0.0f, 25.0f});
        titleOverlap2.setFillColor(sf::Color::White);

        mainText.emplace(orbitron_regular, "Settings", 65.0f);
        mainText->setFillColor(sf::Color::Black);
        mainText->setOrigin({
            mainText->getGlobalBounds().position.x + mainText->getGlobalBounds().size.x / 2.0f,
            mainText->getGlobalBounds().position.y + mainText->getGlobalBounds().size.y / 2.0f
        });
        mainText->setPosition({600.0f, 75.0f});
        #pragma endregion

        #pragma region //! [Return]
        goBackButton.setSize({180.0f, 60.0f});
        goBackButton.setPosition({10.0f, 730.0f});
        goBackButton.setFillColor(sf::Color::White);

        goBackButtonText.emplace(orbitron_regular, "Return", 35.0f);
        goBackButtonText->setOrigin({
            goBackButtonText->getGlobalBounds().position.x + goBackButtonText->getGlobalBounds().size.x / 2.0f,
            goBackButtonText->getGlobalBounds().position.y + goBackButtonText->getGlobalBounds().size.y / 2.0f
        });
        goBackButtonText->setPosition({100.0f, 760.0f});
        goBackButtonText->setFillColor(sf::Color::Black);
        #pragma endregion
        
        #pragma region //! {Generation Time}
        generationTime_MainText.emplace(orbitron_regular, "Generation time:                              (seconds)", 25.0f);
        generationTime_MainText->setFillColor(sf::Color::Cyan);
        generationTime_MainText->setPosition({50.0f, 200.0f});

        generationTime_Description.emplace(orbitron_regular, "Time interval between two generations.", 15.0f);
        generationTime_Description->setFillColor(sf::Color::White);
        generationTime_Description->setPosition({50.0f, 250.0f});

        generationTime_Box.setSize({110.0f, 40.0f});
        generationTime_Box.setFillColor(sf::Color::White);
        generationTime_Box.setPosition({300.0f, 200.0f});

        generationTime_DisplayedTime.emplace(orbitron_regular, "-", 30.0f);
        generationTime_DisplayedTime->setFillColor(sf::Color::Black); 
        generationTime_DisplayedTime->setPosition({305.0f, 202.0f});

        generationTime_IncreaseTimeButton.setSize({30.0f, 18.0f});
        generationTime_IncreaseTimeButton.setFillColor(sf::Color::White);
        generationTime_IncreaseTimeButton.setPosition({415.0f, 200.0f});

        generationTime_upArrow.setRadius(10.0f);
        generationTime_upArrow.setPointCount(3);
        generationTime_upArrow.setFillColor(sf::Color::Black);
        generationTime_upArrow.setPosition({420.0f, 202.0f});

        generationTime_DecreaseTimeButton.setSize({30.0f, 18.0f});
        generationTime_DecreaseTimeButton.setFillColor(sf::Color::White);
        generationTime_DecreaseTimeButton.setPosition({415.0f, 222.0f});

        generationTime_downArrow.setRadius(10.0f);
        generationTime_downArrow.setPointCount(3);
        generationTime_downArrow.setRotation(sf::degrees(180.0f));
        generationTime_downArrow.setFillColor(sf::Color::Black);
        generationTime_downArrow.setPosition({440.0f, 238.0f});
        #pragma endregion
    }
    #pragma endregion

    while (const std::optional event = data.window.pollEvent()) { //! Handle events
        if (event->is<sf::Event::Closed>()) {
            data.window.close();
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                const sf::Vector2i pixelPos = sf::Mouse::getPosition(data.window);
                const sf::Vector2f fixedMousePos = data.window.mapPixelToCoords(pixelPos, data.window.getDefaultView());

                if (goBackButton.getGlobalBounds().contains(fixedMousePos)) {
                    isPressingGoBack = true;
                    goBackButton.setFillColor(sf::Color::Black);
                    goBackButton.setOutlineThickness(2.0f);
                    goBackButton.setOutlineColor(sf::Color::White);
                    goBackButtonText->setFillColor(sf::Color::White);
                }
                else if (generationTime_IncreaseTimeButton.getGlobalBounds().contains(fixedMousePos)) {
                    data.timeIntervalMultipiler = std::min(data.timeIntervalMultipiler + 1, 20);
                    data.timeInterval = data.timeIntervalMultipiler * 0.05f;

                    generationTime_isPressingUp = true;

                    generationTime_IncreaseTimeButton.setFillColor(sf::Color::Black);
                    generationTime_IncreaseTimeButton.setOutlineThickness(2.0f);
                    generationTime_IncreaseTimeButton.setOutlineColor(sf::Color::White);
                    generationTime_upArrow.setFillColor(sf::Color::White);
                }
                else if (generationTime_DecreaseTimeButton.getGlobalBounds().contains(fixedMousePos)) {
                    data.timeIntervalMultipiler = std::max(data.timeIntervalMultipiler - 1, 1);
                    data.timeInterval = data.timeIntervalMultipiler * 0.05f;

                    generationTime_isPressingDown = true;

                    generationTime_DecreaseTimeButton.setFillColor(sf::Color::Black);
                    generationTime_DecreaseTimeButton.setOutlineThickness(2.0f);
                    generationTime_DecreaseTimeButton.setOutlineColor(sf::Color::White);
                    generationTime_downArrow.setFillColor(sf::Color::White);
                }
            }
        }
        if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseReleased->button == sf::Mouse::Button::Left) {
                const sf::Vector2i pixelPos = sf::Mouse::getPosition(data.window);
                const sf::Vector2f fixedMousePos = data.window.mapPixelToCoords(pixelPos, data.window.getDefaultView());

                if (goBackButton.getGlobalBounds().contains(fixedMousePos) && isPressingGoBack) {
                    data.setScene(Scene::MainMenu);
                }
                else if (generationTime_IncreaseTimeButton.getGlobalBounds().contains(fixedMousePos) && generationTime_isPressingUp) {
                    generationTime_isPressingUp = false;
                }
                else if (generationTime_DecreaseTimeButton.getGlobalBounds().contains(fixedMousePos) && generationTime_isPressingDown) {
                    generationTime_isPressingDown = false;
                }
            }

            #pragma region //! Default values
            isPressingGoBack = false;

            goBackButton.setFillColor(sf::Color::White);
            goBackButton.setOutlineThickness(0.0f);
            goBackButtonText->setFillColor(sf::Color::Black);

            generationTime_IncreaseTimeButton.setFillColor(sf::Color::White);
            generationTime_IncreaseTimeButton.setOutlineThickness(0.0f);
            generationTime_upArrow.setFillColor(sf::Color::Black);

            generationTime_DecreaseTimeButton.setFillColor(sf::Color::White);
            generationTime_DecreaseTimeButton.setOutlineThickness(0.0f);
            generationTime_downArrow.setFillColor(sf::Color::Black);
            #pragma endregion
        }
    }

    #pragma region //! Update
    roundedTimeInterval << std::fixed << std::setprecision(2) << data.timeInterval;
    generationTime_DisplayedTime->setString(roundedTimeInterval.str());
    #pragma endregion

    #pragma region //! Draw and display
    data.window.clear(sf::Color::Black);
        #pragma region //* Fixed
    data.window.setView(data.window.getDefaultView());

    data.window.draw(titleOverlap1);
    data.window.draw(titleOverlap2);
    data.window.draw(*mainText);

    data.window.draw(goBackButton);
    data.window.draw(*goBackButtonText);

    data.window.draw(*generationTime_MainText);
    data.window.draw(*generationTime_Description);
    data.window.draw(generationTime_Box);
    data.window.draw(*generationTime_DisplayedTime);
    data.window.draw(generationTime_IncreaseTimeButton);
    data.window.draw(generationTime_upArrow);
    data.window.draw(generationTime_DecreaseTimeButton);
    data.window.draw(generationTime_downArrow);
        #pragma endregion
    data.window.display();
    #pragma endregion
}
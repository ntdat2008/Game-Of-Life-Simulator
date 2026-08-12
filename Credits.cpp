#include "Credits.hpp"

void run_Credits(GameData& data) {
    #pragma region //! Define
    data.window.setView(data.window.getDefaultView());

    static bool isInitialized = false;

    static sf::View creditsView;

    static float currentScrollY = 400.0f;
    static const float minScrollY = 400.0f;
    static const float maxScrollY = 2500.0f;
    static const float scrollSpeed = 30.0f;

    static sf::RectangleShape mainTitleBackground1;
    static sf::RectangleShape mainTitleBackground2;
    static std::optional<sf::Text> mainTitleText;

    static bool isPressingReturn = false;
    static sf::RectangleShape returnButton;
    static std::optional<sf::Text> returnButtonText;

    static std::optional<sf::Text> originalConcept_Title;
    static std::optional<sf::Text> originalConcept_Name;

    static std::optional<sf::Text> leadDeveloper_Title;
    static std::optional<sf::Text> leadDeveloper_Name;

    static std::optional<sf::Text> programmer_Title;
    static std::optional<sf::Text> programmer_Name;

    static std::optional<sf::Text> UIDesigner_Title;
    static std::optional<sf::Text> UIDesigner_Name;

    static std::optional<sf::Text> gameplayDesigner_Title;
    static std::optional<sf::Text> gameplayDesigner_Name;

    static std::optional<sf::Text> tester_Title;
    static std::optional<sf::Text> tester_Name;

    static std::optional<sf::Text> gameBuiltWith_Title;
    static std::optional<sf::Text> gameBuiltWith_Name;

    static std::optional<sf::Text> assets_Title;
    static std::optional<sf::Text> assets_orbitronFont;
    #pragma endregion

    #pragma region //! Initialize
    if (!isInitialized) {
        isInitialized = true;

        creditsView.setSize(data.window.getDefaultView().getSize());
        creditsView.setCenter(data.window.getDefaultView().getCenter());

        #pragma region //! Assets
        const sf::Font& orbitron_regular = data.assets.getFont("orbitron_regular");
        const sf::Font& orbitron_bold = data.assets.getFont("orbitron_bold");
        #pragma endregion

        #pragma region //! Main title
        mainTitleBackground1.setSize({1200.0f, 120.0f});
        mainTitleBackground1.setFillColor(sf::Color::Black);

        mainTitleBackground2.setSize({1200.0f, 110.0f});
        mainTitleBackground2.setPosition({0.0f, 10.0f});
        mainTitleBackground2.setFillColor(sf::Color::White);

        mainTitleText.emplace(orbitron_regular, "Credits", 50.0f);
        mainTitleText->setOrigin({
            mainTitleText->getGlobalBounds().position.x + mainTitleText->getGlobalBounds().size.x / 2.0f,
            mainTitleText->getGlobalBounds().position.y + mainTitleText->getGlobalBounds().size.y / 2.0f
        });
        mainTitleText->setPosition({600.0f, 60.0f});
        mainTitleText->setFillColor(sf::Color::Black);
        #pragma endregion

        #pragma region //! [Return]
        returnButton.setSize({180.0f, 60.0f});
        returnButton.setPosition({10.0f, 730.0f});
        returnButton.setFillColor(sf::Color::White);

        returnButtonText.emplace(orbitron_regular, "Return", 35.0f);
        returnButtonText->setOrigin({
            returnButtonText->getGlobalBounds().position.x + returnButtonText->getGlobalBounds().size.x / 2.0f,
            returnButtonText->getGlobalBounds().position.y + returnButtonText->getGlobalBounds().size.y / 2.0f
        });
        returnButtonText->setPosition({100.0f, 760.0f});
        returnButtonText->setFillColor(sf::Color::Black);
        #pragma endregion

        #pragma region //! {Original concept}
        originalConcept_Title.emplace(orbitron_bold, "Original Concept", 45.0f);
        originalConcept_Title->setOrigin({
            originalConcept_Title->getGlobalBounds().position.x + originalConcept_Title->getGlobalBounds().size.x / 2.0f,
            originalConcept_Title->getGlobalBounds().position.y + originalConcept_Title->getGlobalBounds().size.y / 2.0f
        });
        originalConcept_Title->setPosition({600.0f, 260.0f});
        originalConcept_Title->setFillColor(sf::Color::White);

        originalConcept_Name.emplace(orbitron_regular, "John Horton Conway", 40.0f);
        originalConcept_Name->setOrigin({
            originalConcept_Name->getGlobalBounds().position.x + originalConcept_Name->getGlobalBounds().size.x / 2.0f,
            originalConcept_Name->getGlobalBounds().position.y + originalConcept_Name->getGlobalBounds().size.y / 2.0f
        });
        originalConcept_Name->setPosition({600.0f, 360.0f});
        originalConcept_Name->setFillColor(sf::Color::Yellow);
        #pragma endregion

        #pragma region //! {Lead Developer}
        leadDeveloper_Title.emplace(orbitron_bold, "Lead Developer", 45.0f);
        leadDeveloper_Title->setOrigin({
            leadDeveloper_Title->getGlobalBounds().position.x + leadDeveloper_Title->getGlobalBounds().size.x / 2.0f,
            leadDeveloper_Title->getGlobalBounds().position.y + leadDeveloper_Title->getGlobalBounds().size.y / 2.0f
        });
        leadDeveloper_Title->setPosition({600.0f, 560.0f});
        leadDeveloper_Title->setFillColor(sf::Color::White);

        leadDeveloper_Name.emplace(orbitron_regular, "ntdat2008", 40.0f);
        leadDeveloper_Name->setOrigin({
            leadDeveloper_Name->getGlobalBounds().position.x + leadDeveloper_Name->getGlobalBounds().size.x / 2.0f,
            leadDeveloper_Name->getGlobalBounds().position.y + leadDeveloper_Name->getGlobalBounds().size.y / 2.0f
        });
        leadDeveloper_Name->setPosition({600.0f, 660.0f});
        leadDeveloper_Name->setFillColor(sf::Color::Yellow);
        #pragma endregion

        #pragma region //! {Programmer}
        programmer_Title.emplace(orbitron_bold, "Programmer", 45.0f);
        programmer_Title->setOrigin({
            programmer_Title->getGlobalBounds().position.x + programmer_Title->getGlobalBounds().size.x / 2.0f,
            programmer_Title->getGlobalBounds().position.y + programmer_Title->getGlobalBounds().size.y / 2.0f
        });
        programmer_Title->setPosition({600.0f, 860.0f});
        programmer_Title->setFillColor(sf::Color::White);

        programmer_Name.emplace(orbitron_regular, "ntdat2008", 40.0f);
        programmer_Name->setOrigin({
            programmer_Name->getGlobalBounds().position.x + programmer_Name->getGlobalBounds().size.x / 2.0f,
            programmer_Name->getGlobalBounds().position.y + programmer_Name->getGlobalBounds().size.y / 2.0f
        });
        programmer_Name->setPosition({600.0f, 960.0f});
        programmer_Name->setFillColor(sf::Color::Yellow);
        #pragma endregion

        #pragma region //! {UI Designer}
        UIDesigner_Title.emplace(orbitron_bold, "UI Designer", 45.0f);
        UIDesigner_Title->setOrigin({
            UIDesigner_Title->getGlobalBounds().position.x + UIDesigner_Title->getGlobalBounds().size.x / 2.0f,
            UIDesigner_Title->getGlobalBounds().position.y + UIDesigner_Title->getGlobalBounds().size.y / 2.0f
        });
        UIDesigner_Title->setPosition({600.0f, 1160.0f});
        UIDesigner_Title->setFillColor(sf::Color::White);

        UIDesigner_Name.emplace(orbitron_regular, "ntdat2008", 40.0f);
        UIDesigner_Name->setOrigin({
            UIDesigner_Name->getGlobalBounds().position.x + UIDesigner_Name->getGlobalBounds().size.x / 2.0f,
            UIDesigner_Name->getGlobalBounds().position.y + UIDesigner_Name->getGlobalBounds().size.y / 2.0f
        });
        UIDesigner_Name->setPosition({600.0f, 1260.0f});
        UIDesigner_Name->setFillColor(sf::Color::Yellow);
        #pragma endregion

        #pragma region //! {Gameplay Designer}
        gameplayDesigner_Title.emplace(orbitron_bold, "Gameplay Designer", 45.0f);
        gameplayDesigner_Title->setOrigin({
            gameplayDesigner_Title->getGlobalBounds().position.x + gameplayDesigner_Title->getGlobalBounds().size.x / 2.0f,
            gameplayDesigner_Title->getGlobalBounds().position.y + gameplayDesigner_Title->getGlobalBounds().size.y / 2.0f
        });
        gameplayDesigner_Title->setPosition({600.0f, 1460.0f});
        gameplayDesigner_Title->setFillColor(sf::Color::White);

        gameplayDesigner_Name.emplace(orbitron_regular, "ntdat2008", 40.0f);
        gameplayDesigner_Name->setOrigin({
            gameplayDesigner_Name->getGlobalBounds().position.x + gameplayDesigner_Name->getGlobalBounds().size.x / 2.0f,
            gameplayDesigner_Name->getGlobalBounds().position.y + gameplayDesigner_Name->getGlobalBounds().size.y / 2.0f
        });
        gameplayDesigner_Name->setPosition({600.0f, 1560.0f});
        gameplayDesigner_Name->setFillColor(sf::Color::Yellow);
        #pragma endregion

        #pragma region //! {Tester}
        tester_Title.emplace(orbitron_bold, "Tester", 45.0f);
        tester_Title->setOrigin({
            tester_Title->getGlobalBounds().position.x + tester_Title->getGlobalBounds().size.x / 2.0f,
            tester_Title->getGlobalBounds().position.y + tester_Title->getGlobalBounds().size.y / 2.0f
        });
        tester_Title->setPosition({600.0f, 1760.0f});
        tester_Title->setFillColor(sf::Color::White);

        tester_Name.emplace(orbitron_regular, "ntdat2008", 40.0f);
        tester_Name->setOrigin({
            tester_Name->getGlobalBounds().position.x + tester_Name->getGlobalBounds().size.x / 2.0f,
            tester_Name->getGlobalBounds().position.y + tester_Name->getGlobalBounds().size.y / 2.0f
        });
        tester_Name->setPosition({600.0f, 1860.0f});
        tester_Name->setFillColor(sf::Color::Yellow);
        #pragma endregion

        #pragma region //! {Game built with}
        gameBuiltWith_Title.emplace(orbitron_bold, "Game built with:", 45.0f);
        gameBuiltWith_Title->setOrigin({
            gameBuiltWith_Title->getGlobalBounds().position.x + gameBuiltWith_Title->getGlobalBounds().size.x / 2.0f,
            gameBuiltWith_Title->getGlobalBounds().position.y + gameBuiltWith_Title->getGlobalBounds().size.y / 2.0f
        });
        gameBuiltWith_Title->setPosition({600.0f, 2060.0f});
        gameBuiltWith_Title->setFillColor(sf::Color::White);

        gameBuiltWith_Name.emplace(orbitron_regular, "C++ and SFML 3", 40.0f);
        gameBuiltWith_Name->setOrigin({
            gameBuiltWith_Name->getGlobalBounds().position.x + gameBuiltWith_Name->getGlobalBounds().size.x / 2.0f,
            gameBuiltWith_Name->getGlobalBounds().position.y + gameBuiltWith_Name->getGlobalBounds().size.y / 2.0f
        });
        gameBuiltWith_Name->setPosition({600.0f, 2160.0f});
        gameBuiltWith_Name->setFillColor(sf::Color::Yellow);
        #pragma endregion

        #pragma region //! {Assets}
        assets_Title.emplace(orbitron_bold, "Assets", 45.0f);
        assets_Title->setOrigin({
            assets_Title->getGlobalBounds().position.x + assets_Title->getGlobalBounds().size.x / 2.0f,
            assets_Title->getGlobalBounds().position.y + assets_Title->getGlobalBounds().size.y / 2.0f
        });
        assets_Title->setPosition({600.0f, 2360.0f});
        assets_Title->setFillColor(sf::Color::White);

        assets_orbitronFont.emplace(orbitron_regular, "Orbitron font - Matt McInerney", 45.0f);
        assets_orbitronFont->setOrigin({
            assets_orbitronFont->getGlobalBounds().position.x + assets_orbitronFont->getGlobalBounds().size.x / 2.0f,
            assets_orbitronFont->getGlobalBounds().position.y + assets_orbitronFont->getGlobalBounds().size.y / 2.0f
        });
        assets_orbitronFont->setPosition({600.0f, 2460.0f});
        assets_orbitronFont->setFillColor(sf::Color::Yellow);
        #pragma endregion
    }
    if (data.previousScene == Scene::MainMenu) {
        data.setScene(Scene::Credits);
        creditsView.setCenter({data.window.getDefaultView().getCenter().x, 400.0f});
        currentScrollY = 400.0f;
    }
    #pragma endregion

    while (const std::optional event = data.window.pollEvent()) { //! Handle events
        if (event->is<sf::Event::Closed>()) {
            data.window.close();
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                const sf::Vector2i pixelPos = mousePressed->position;
                const sf::Vector2f fixedPos = data.window.mapPixelToCoords(pixelPos, data.window.getDefaultView());
                
                if (returnButton.getGlobalBounds().contains(fixedPos)) {
                    isPressingReturn = true;
                    returnButton.setFillColor(sf::Color::Black);
                    returnButton.setOutlineThickness(2.0f);
                    returnButton.setOutlineColor(sf::Color::White);
                    returnButtonText->setFillColor(sf::Color::White);
                }
            }
        }
        if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseReleased->button == sf::Mouse::Button::Left) {
                const sf::Vector2i pixelPos = mouseReleased->position;
                const sf::Vector2f fixedPos = data.window.mapPixelToCoords(pixelPos, data.window.getDefaultView());
                
                if (returnButton.getGlobalBounds().contains(fixedPos) && isPressingReturn) {
                    data.setScene(Scene::MainMenu);
                }
            }

            #pragma region //! Default
            returnButton.setFillColor(sf::Color::White);
            returnButton.setOutlineThickness(0.0f);
            returnButtonText->setFillColor(sf::Color::Black);
            #pragma endregion
        }
        if (const auto* mouseScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
            if (mouseScrolled->wheel == sf::Mouse::Wheel::Vertical) {
                const int delta = mouseScrolled->delta;

                currentScrollY -= delta * scrollSpeed;
                currentScrollY = std::clamp(currentScrollY, minScrollY, maxScrollY);

                creditsView.setCenter({creditsView.getCenter().x, currentScrollY});
            }
        }
    }

    #pragma region //! Draw and display
    data.window.clear(sf::Color::Black);

        #pragma region //* Not fixed
    data.window.setView(creditsView);
    
    data.window.draw(*originalConcept_Title);
    data.window.draw(*originalConcept_Name);

    data.window.draw(*leadDeveloper_Title);
    data.window.draw(*leadDeveloper_Name);

    data.window.draw(*programmer_Title);
    data.window.draw(*programmer_Name);

    data.window.draw(*UIDesigner_Title);
    data.window.draw(*UIDesigner_Name);

    data.window.draw(*gameplayDesigner_Title);
    data.window.draw(*gameplayDesigner_Name);

    data.window.draw(*tester_Title);
    data.window.draw(*tester_Name);

    data.window.draw(*gameBuiltWith_Title);
    data.window.draw(*gameBuiltWith_Name);

    data.window.draw(*assets_Title);
    data.window.draw(*assets_orbitronFont);
        #pragma endregion

        #pragma region //* Fixed
    data.window.setView(data.window.getDefaultView());

    data.window.draw(mainTitleBackground1);
    data.window.draw(mainTitleBackground2);
    data.window.draw(*mainTitleText);

    data.window.draw(returnButton);
    data.window.draw(*returnButtonText);
        #pragma endregion

    data.window.display();
    #pragma endregion
}
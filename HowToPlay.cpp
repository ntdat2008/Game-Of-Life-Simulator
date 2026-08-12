#include "HowToPlay.hpp"

void run_HowToPlay(GameData& data) {
    #pragma region //! Define
    data.window.setView(data.window.getDefaultView());

    static bool isIntialized = false;

    static sf::View howToPlayView;

    static float currentScrollY = 400.f;
    static const float minScrollY = 400.0f;
    static const float maxScrollY = 3000.0f;
    static const float scrollSpeed = 30.0f;

    static sf::RectangleShape mainTitleOverlap1;
    static sf::RectangleShape mainTitleOverlap2;
    static std::optional<sf::Text> mainTitleText;

    static std::optional<sf::Text> introductionTitle;
    static std::optional<sf::Text> introductionDescription;

    static std::optional<sf::Text> rulesTitle;
    static std::optional<sf::Text> rulesDescription;

    static std::optional<sf::Text> gameplayTitle;
    static std::optional<sf::Text> gameplayDescription;

    static sf::RectangleShape goBackButton;
    static std::optional<sf::Text> goBackButtonText;

    static bool isPressingGoBack = false;
    #pragma endregion

    #pragma region //! Intialize
    if (!isIntialized) {
        isIntialized = true;

        howToPlayView.setSize(data.window.getDefaultView().getSize());
        howToPlayView.setCenter(data.window.getDefaultView().getCenter());

        #pragma region //! Assets
        const sf::Font& orbitron_regular = data.assets.getFont("orbitron_regular");
        const sf::Font& orbitron_bold = data.assets.getFont("orbitron_bold");
        #pragma endregion

        #pragma region //! Main title
        mainTitleOverlap1.setSize({1200.0f, 110.0f});
        mainTitleOverlap1.setFillColor(sf::Color::Black);

        mainTitleOverlap2.setSize({1200.0f, 100.0f});
        mainTitleOverlap2.setPosition({0.0f, 10.0f});
        mainTitleOverlap2.setFillColor(sf::Color::White);

        mainTitleText.emplace(orbitron_regular, "How to play?", 55.0f);
        mainTitleText->setOrigin({
            mainTitleText->getGlobalBounds().position.x + mainTitleText->getGlobalBounds().size.x / 2.0f,
            mainTitleText->getGlobalBounds().position.y + mainTitleText->getGlobalBounds().size.y / 2.0f
        });
        mainTitleText->setPosition({600.0f, 60.0f});
        mainTitleText->setFillColor(sf::Color::Black);
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

        #pragma region //! === Introduction ===
        introductionTitle.emplace(orbitron_bold, "INTRODUCTION", 60.0f);
        introductionTitle->setOrigin({
            introductionTitle->getGlobalBounds().position.x + introductionTitle->getGlobalBounds().size.x / 2.0f,
            introductionTitle->getGlobalBounds().position.y + introductionTitle->getGlobalBounds().size.y / 2.0f
        });
        introductionTitle->setPosition({600.0f, 200.0f});
        introductionTitle->setFillColor(sf::Color::Magenta);
        introductionDescription.emplace(orbitron_regular,
        R"(
   This game is a variant of "Conway's Game of Life", which is 
a cellular automaton devised by the British mathematician 
John Horton Conway in 1970.

   "Conway's Game of Life" is a zero-player game, meaning
that its evolution is determined by its initial state, requiring
no further input.

   One interacts by creating an initial configuration (pattern)
and observing how it evolves in discrete time steps
called generations.

   Each unit square in the grid is a cell.

   Each cell's state in the next generation depends on its
eight neighbors, which are the cells that are horizontally,
vertically, and diagonally adjacent to it. This applies to
all cells in the grid simultaneously.
        )", 
        35.0f);
        introductionDescription->setFillColor(sf::Color::White);
        introductionDescription->setPosition({10.0f, 250.0f});
        #pragma endregion

        #pragma region //! === Rules ===
        rulesTitle.emplace(orbitron_bold, "RULES", 60.0f);
        rulesTitle->setOrigin({
            rulesTitle->getGlobalBounds().position.x + rulesTitle->getGlobalBounds().size.x / 2.0f,
            rulesTitle->getGlobalBounds().position.y + rulesTitle->getGlobalBounds().size.y / 2.0f
        });
        rulesTitle->setPosition({600.0f, 1200.0f});
        rulesTitle->setFillColor(sf::Color::Magenta);
        rulesDescription.emplace(orbitron_regular,
        R"(
   "Game of Life" follows these simple rules:

- Any live cell with fewer than two live neighbors
dies in the next generation.

- Any live cell with two or three live neighbors
lives in the next generation.

- Any live cell with more than three live neighbors
dies in the next generation.

- Any dead cell with exactly three live neighbors
becomes a live cell in the next generation.

   Unlike the original "Game of Life", you can freely 
add or remove cells at any point during the simulation.
        )", 
        35.0f);
        rulesDescription->setFillColor(sf::Color::White);
        rulesDescription->setPosition({10.0f, 1250.0f});
        #pragma endregion
    
        #pragma region //! === Gameplay ===
        gameplayTitle.emplace(orbitron_bold, "GAMEPLAY", 60.0f);
        gameplayTitle->setOrigin({
            gameplayTitle->getGlobalBounds().position.x + gameplayTitle->getGlobalBounds().size.x / 2.0f,
            gameplayTitle->getGlobalBounds().position.y + gameplayTitle->getGlobalBounds().size.y / 2.0f
        });
        gameplayTitle->setPosition({600.0f, 2100.0f});
        gameplayTitle->setFillColor(sf::Color::Magenta);
        gameplayDescription.emplace(orbitron_regular,
        R"(
   There are tools that you can use:

- Set: Add live cells into the grid.

- Erase: Erase live cells from existence.

- Reset: Erases everthing.

   To run a simulation, choose the Run option:

- Start: Runs the simulation automically.
 *You can change the speed of the simulation 
  in Settings

- Next: Go to the next generation.

- Previous: Go back to the previous generation.

- Pause: Pause the simulation.

   Hold and drag Right mouse button to move around.

   Scroll to zoom in/out.
        )", 
        35.0f);
        gameplayDescription->setFillColor(sf::Color::White);
        gameplayDescription->setPosition({10.0f, 2150.0f});
        #pragma endregion
    }
    if (data.previousScene == Scene::MainMenu) {
        data.setScene(Scene::HowToPlay);
        howToPlayView.setCenter(data.window.getDefaultView().getCenter());
        currentScrollY = 400.0f;
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
            }
        }
        if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseReleased->button == sf::Mouse::Button::Left) {
                const sf::Vector2i pixelPos = sf::Mouse::getPosition(data.window);
                const sf::Vector2f fixedMousePos = data.window.mapPixelToCoords(pixelPos, data.window.getDefaultView());

                if (goBackButton.getGlobalBounds().contains(fixedMousePos) && isPressingGoBack) {
                    isPressingGoBack = false;
                    data.setScene(Scene::MainMenu);
                }
            }

            #pragma region //! Default
            goBackButton.setFillColor(sf::Color::White);
            goBackButton.setOutlineThickness(0.0f);
            goBackButtonText->setFillColor(sf::Color::Black);
            #pragma endregion
        }
        if (const auto* mouseScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
            if (mouseScrolled->wheel == sf::Mouse::Wheel::Vertical) {
                float delta = mouseScrolled->delta;

                currentScrollY -= scrollSpeed * delta;
                currentScrollY = std::clamp(currentScrollY, minScrollY, maxScrollY);

                howToPlayView.setCenter({howToPlayView.getCenter().x, currentScrollY});
            }
        }
    }

    #pragma region //! Draw and display
    data.window.clear(sf::Color::Black);

        #pragma region //* Not fixed
    data.window.setView(howToPlayView);
    data.window.draw(*introductionTitle);
    data.window.draw(*introductionDescription);
    data.window.draw(*rulesTitle);
    data.window.draw(*rulesDescription);
    data.window.draw(*gameplayTitle);
    data.window.draw(*gameplayDescription);
        #pragma endregion
        
        #pragma region //* Fixed
    data.window.setView(data.window.getDefaultView());
    data.window.draw(mainTitleOverlap1);
    data.window.draw(mainTitleOverlap2);
    data.window.draw(*mainTitleText);
    data.window.draw(goBackButton);
    data.window.draw(*goBackButtonText);
        #pragma endregion
    
    data.window.display();
    #pragma endregion
}

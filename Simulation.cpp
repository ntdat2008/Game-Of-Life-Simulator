#include "Simulation.hpp"

CellDelta calculateNextGeneration(const std::unordered_set<int64_t> &liveCells) {
    std::unordered_map<int64_t, int> neighborCount;
    CellDelta nextGeneration;

    for (int64_t key : liveCells) {
        int x = static_cast<int>(key >> 32);
        int y = static_cast<int>(static_cast<int32_t>(key & 0xFFFFFFFF));

        for (int i = 0; i < 8; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            int64_t newKey = (static_cast<int64_t>(newX) << 32) | (static_cast<uint32_t>(newY));
            ++neighborCount[newKey];
        }
    }

    for (int64_t key : liveCells) {
        int count = 0;
        auto it = neighborCount.find(key);
        if (it != neighborCount.end()) {
            count = it->second;
        }

        if (count < 2 || count > 3) {
            nextGeneration.deadCells.push_back(key);
        }
    }

    for (const auto &[key, count] : neighborCount) {
        if (liveCells.find(key) == liveCells.end()) {
            if (count == 3) {
                nextGeneration.liveCells.push_back(key);
            }
        }
    }

    return nextGeneration;
}

void run_Simulation(GameData& data) {
    #pragma region //! Define
    data.window.setView(data.window.getDefaultView());

    static bool isIntialized = false;

    static sf::View simulationView;
    static float currentZoom = 1.0f;
    static const float minZoom = 0.3f;
    static const float maxZoom = 3.0f;

    static bool isDragging = false;
    static sf::Vector2i lastMousePos({0, 0});
    static const float gridWidth = 6000000.0f;
    static const float gridHeight = 6000000.0f;

    static const float gridStep = 30.0f;
    static const sf::Color backgroundColor(11, 15, 20);
    static const sf::Color gridColor(26, 36, 48);
    static const sf::Color cellColor = sf::Color::White;

    static sf::Clock simulationClock;
    static float timeAccumulator = 0.0f;

    static int64_t generationCounter = 0;
    static std::optional<sf::Text> generationCounterText;

    static Simulation_Tool currentTool = Simulation_Tool::Set;
    static Simulation_RunState currentRunState = Simulation_RunState::Pause;

    static std::unordered_set<int64_t> liveCells;
    static std::vector<CellDelta> historyStack;
    static size_t historyIndex = 0;

    static sf::RectangleShape runButton;
    static std::optional<sf::Text> runButtonText;

    static sf::RectangleShape Run_startButton;
    static std::optional<sf::Text> Run_startButtonText;

    static sf::RectangleShape Run_pauseButton;
    static std::optional<sf::Text> Run_pauseButtonText;

    static sf::RectangleShape Run_nextButton;
    static std::optional<sf::Text> Run_nextButtonText;

    static sf::RectangleShape Run_previousButton;
    static std::optional<sf::Text> Run_previousButtonText;

    static sf::RectangleShape setButton;
    static std::optional<sf::Text> setButtonText;

    static sf::RectangleShape eraseButton;
    static std::optional<sf::Text> eraseButtonText;

    static sf::RectangleShape resetButton;
    static std::optional<sf::Text> resetButtonText;

    static sf::RectangleShape goBackButton;
    static std::optional<sf::Text> goBackButtonText;

    static bool isPressingRun = false;
    static bool isPressingSet = false;
    static bool isPressingErase = false;
    static bool isPressingReset = false;
    static bool isPressingGoBack = false;
    static bool isPressingRun_Start = false;
    static bool isPressingRun_Pause = false;
    static bool isPressingRun_Next = false;
    static bool isPressingRun_Previous = false;
    static bool isPainting = false;
    #pragma endregion

    #pragma region //! Initialize
    if (!isIntialized) {
        isIntialized = true;

        #pragma region //* Assets
        const sf::Font &orbitron_regular = data.assets.getFont("orbitron_regular");
        #pragma endregion

        currentTool = Simulation_Tool::Set;
        currentRunState = Simulation_RunState::Pause;

        simulationView = data.window.getDefaultView();
        simulationView.setCenter({0.0f, 0.0f});

        #pragma region //* Generation counter
        generationCounterText.emplace(orbitron_regular, "Generation #0", 20.0f);
        generationCounterText->setFillColor(sf::Color::White);
        generationCounterText->setPosition({15.0f, 10.0f});
        #pragma endregion

        #pragma region //* [Run]
        runButton.setSize({180.0f, 60.0f});
        runButton.setOrigin(runButton.getSize() / 2.0f);
        runButton.setPosition({100.0f, 480.0f});
        runButtonText.emplace(orbitron_regular, "Run", 30.0f);
        runButtonText->setOrigin({
            runButtonText->getGlobalBounds().position.x + runButtonText->getGlobalBounds().size.x / 2.0f,
            runButtonText->getGlobalBounds().position.y + runButtonText->getGlobalBounds().size.y / 2.0f
        });
        runButtonText->setPosition({100.0f, 480.0f});
        #pragma endregion
        #pragma region //* [Set]
        setButton.setSize({180.0f, 60.0f});
        setButton.setOrigin(setButton.getSize() / 2.0f);
        setButton.setPosition({100.0f, 550.0f});
        setButtonText.emplace(orbitron_regular, "Set", 30.0f);
        setButtonText->setOrigin({
            setButtonText->getGlobalBounds().position.x + setButtonText->getGlobalBounds().size.x / 2.0f,
            setButtonText->getGlobalBounds().position.y + setButtonText->getGlobalBounds().size.y / 2.0f
        });
        setButtonText->setPosition({100.0f, 550.0f});
        #pragma endregion
        #pragma region //* [Erase]
        eraseButton.setSize({180.0f, 60.0f});
        eraseButton.setOrigin(eraseButton.getSize() / 2.0f);
        eraseButton.setPosition({100.0f, 620.0f});
        eraseButtonText.emplace(orbitron_regular, "Erase", 30.0f);
        eraseButtonText->setOrigin({
            eraseButtonText->getGlobalBounds().position.x + eraseButtonText->getGlobalBounds().size.x / 2.0f,
            eraseButtonText->getGlobalBounds().position.y + eraseButtonText->getGlobalBounds().size.y / 2.0f
        });
        eraseButtonText->setPosition({100.0f, 620.0f});
        #pragma endregion
        #pragma region //* [Reset]
        resetButton.setSize({180.0f, 60.0f});
        resetButton.setOrigin(resetButton.getSize() / 2.0f);
        resetButton.setPosition({100.0f, 690.0f});
        resetButton.setFillColor(sf::Color::White);
        resetButtonText.emplace(orbitron_regular, "Reset", 30.0f);
        resetButtonText->setFillColor(sf::Color::Black);
        resetButtonText->setOrigin({
            resetButtonText->getGlobalBounds().position.x + resetButtonText->getGlobalBounds().size.x / 2.0f,
            resetButtonText->getGlobalBounds().position.y + resetButtonText->getGlobalBounds().size.y / 2.0f
        });
        resetButtonText->setPosition({100.0f, 690.0f});
        #pragma endregion
        #pragma region //* [Main menu]
        goBackButton.setSize({180.0f, 60.0f});
        goBackButton.setOrigin(goBackButton.getSize() / 2.0f);
        goBackButton.setPosition({100.0f, 760.0f});
        goBackButton.setFillColor(sf::Color::White);
        goBackButtonText.emplace(orbitron_regular, "Main menu", 25.0f);
        goBackButtonText->setFillColor(sf::Color::Black);
        goBackButtonText->setOrigin({
            goBackButtonText->getGlobalBounds().position.x + goBackButtonText->getGlobalBounds().size.x / 2.0f,
            goBackButtonText->getGlobalBounds().position.y + goBackButtonText->getGlobalBounds().size.y / 2.0f
        });
        goBackButtonText->setPosition({100.0f, 760.0f});
        #pragma endregion

        #pragma region //* [Start]
        Run_startButton.setSize({180.0f, 60.0f});
        Run_startButton.setOrigin(Run_startButton.getSize() / 2.0f);
        Run_startButton.setPosition({400.0f, 690.0f});
        Run_startButtonText.emplace(orbitron_regular, "Start", 30.0f);
        Run_startButtonText->setOrigin({
            Run_startButtonText->getGlobalBounds().position.x + Run_startButtonText->getGlobalBounds().size.x / 2.0f,
            Run_startButtonText->getGlobalBounds().position.y + Run_startButtonText->getGlobalBounds().size.y / 2.0f
        });
        Run_startButtonText->setPosition({400.0f, 690.0f});
        #pragma endregion
        #pragma region //* [Pause]
        Run_pauseButton.setSize({180.0f, 60.0f});
        Run_pauseButton.setOrigin(Run_pauseButton.getSize() / 2.0f);
        Run_pauseButton.setPosition({400.0f, 760.0f});
        Run_pauseButtonText.emplace(orbitron_regular, "Pause", 30.0f);
        Run_pauseButtonText->setOrigin({
            Run_pauseButtonText->getGlobalBounds().position.x + Run_pauseButtonText->getGlobalBounds().size.x / 2.0f,
            Run_pauseButtonText->getGlobalBounds().position.y + Run_pauseButtonText->getGlobalBounds().size.y / 2.0f
        });
        Run_pauseButtonText->setPosition({400.0f, 760.0f});
        #pragma endregion
        #pragma region //* [Next]
        Run_nextButton.setSize({180.0f, 60.0f});
        Run_nextButton.setOrigin(Run_nextButton.getSize() / 2.0f);
        Run_nextButton.setPosition({590.0f, 690.0f});
        Run_nextButtonText.emplace(orbitron_regular, "Next", 30.0f);
        Run_nextButtonText->setFillColor(sf::Color::Black);
        Run_nextButtonText->setOrigin({
            Run_nextButtonText->getGlobalBounds().position.x + Run_nextButtonText->getGlobalBounds().size.x / 2.0f,
            Run_nextButtonText->getGlobalBounds().position.y + Run_nextButtonText->getGlobalBounds().size.y / 2.0f
        });
        Run_nextButtonText->setPosition({590.0f, 690.0f});
        #pragma endregion
        #pragma region //* [Previous]
        Run_previousButton.setSize({180.0f, 60.0f});
        Run_previousButton.setOrigin(Run_previousButton.getSize() / 2.0f);
        Run_previousButton.setPosition({590.0f, 760.0f});
        Run_previousButtonText.emplace(orbitron_regular, "Previous", 30.0f);
        Run_previousButtonText->setFillColor(sf::Color::Black);
        Run_previousButtonText->setOrigin({
            Run_previousButtonText->getGlobalBounds().position.x + Run_previousButtonText->getGlobalBounds().size.x / 2.0f,
            Run_previousButtonText->getGlobalBounds().position.y + Run_previousButtonText->getGlobalBounds().size.y / 2.0f
        });
        Run_previousButtonText->setPosition({590.0f, 760.0f});
        #pragma endregion
    }
    if (data.previousScene == Scene::MainMenu) {
        simulationView.setCenter({0.0f, 0.0f});
        data.setScene(Scene::Simulation);
        currentZoom = 1.0f;
        lastMousePos = sf::Vector2i({0, 0});
    }
    #pragma endregion

    while (const std::optional event = data.window.pollEvent()) { //! Handle events
        if (event->is<sf::Event::Closed>()) {
            data.window.close();
        }

        if (const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                const sf::Vector2i pixelPos = mousePressed->position;
                const sf::Vector2f scrollMousePos = data.window.mapPixelToCoords(pixelPos, simulationView);
                const sf::Vector2f fixedMousePos = data.window.mapPixelToCoords(pixelPos, data.window.getDefaultView());

                if (runButton.getGlobalBounds().contains(fixedMousePos)) {
                    isPressingRun = true;
                }
                else if (setButton.getGlobalBounds().contains(fixedMousePos)) {
                    isPressingSet = true;
                }
                else if (eraseButton.getGlobalBounds().contains(fixedMousePos)) {
                    isPressingErase = true;
                }
                else if (resetButton.getGlobalBounds().contains(fixedMousePos)) {
                    isPressingReset = true;
                    resetButton.setFillColor(sf::Color::Black);
                    resetButton.setOutlineThickness(2.0f);
                    resetButtonText->setFillColor(sf::Color::White);
                }
                else if (goBackButton.getGlobalBounds().contains(fixedMousePos)) {
                    isPressingGoBack = true;
                    goBackButton.setFillColor(sf::Color::Black);
                    goBackButton.setOutlineThickness(2.0f);
                    goBackButtonText->setFillColor(sf::Color::White);
                }
                else if (currentTool == Simulation_Tool::Run) {
                    if (Run_startButton.getGlobalBounds().contains(fixedMousePos)) {
                        isPressingRun_Start = true;
                    }
                    else if (Run_pauseButton.getGlobalBounds().contains(fixedMousePos)) {
                        isPressingRun_Pause = true;
                    }
                    else if (Run_nextButton.getGlobalBounds().contains(fixedMousePos)) {
                        isPressingRun_Next = true;
                        Run_nextButton.setFillColor(sf::Color::Black);
                        Run_nextButton.setOutlineThickness(2.0f);
                        Run_nextButton.setOutlineColor(sf::Color::White);
                        Run_nextButtonText->setFillColor(sf::Color::White);
                    }
                    else if (Run_previousButton.getGlobalBounds().contains(fixedMousePos)) {
                        isPressingRun_Previous = true;
                        Run_previousButton.setFillColor(sf::Color::Black);
                        Run_previousButton.setOutlineThickness(2.0f);
                        Run_previousButton.setOutlineColor(sf::Color::White);
                        Run_previousButtonText->setFillColor(sf::Color::White);
                    }
                }
                else {
                    isPainting = true;
                    int gridX = static_cast<int>(std::floor(scrollMousePos.x / 30.0f));
                    int gridY = static_cast<int>(std::floor(scrollMousePos.y / 30.0f));
                    int64_t cellKey = ((static_cast<int64_t>(gridX) & 0xFFFFFFFF) << 32) | (static_cast<int64_t>(gridY) & 0xFFFFFFFF);

                    if (currentTool == Simulation_Tool::Set) {
                        liveCells.insert(cellKey);
                        if (historyIndex < historyStack.size()) {
                            historyStack.resize(historyIndex);
                        }
                    }
                    else if (currentTool == Simulation_Tool::Erase) {
                        liveCells.erase(cellKey);
                        if (historyIndex < historyStack.size()) {
                            historyStack.resize(historyIndex);
                        }
                    }

                    historyStack.clear();
                    historyIndex = 0;
                }
            }
            else if (mousePressed->button == sf::Mouse::Button::Right) {
                isDragging = true;
                lastMousePos = mousePressed->position;
            }
        }
        if (const auto *mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            if (isDragging) {
                sf::Vector2i currentMousePos = mouseMoved->position;
                sf::Vector2i pixelDelta = currentMousePos - lastMousePos;
                sf::Vector2f worldDelta(
                    static_cast<float>(pixelDelta.x) * (simulationView.getSize().x / data.window.getSize().x),
                    static_cast<float>(pixelDelta.y) * (simulationView.getSize().y / data.window.getSize().y)
                );
                sf::Vector2f newCenter = simulationView.getCenter() - worldDelta;
                sf::Vector2f viewHalfSize = simulationView.getSize() / 2.0f;

                float minX = -(gridWidth * 0.5f) + viewHalfSize.x;
                float maxX =  gridWidth * 0.5f - viewHalfSize.x;
                float minY = -(gridHeight * 0.5f) + viewHalfSize.y;
                float maxY =  gridHeight * 0.5f - viewHalfSize.y;

                newCenter.x = std::clamp(newCenter.x, minX, maxX);
                newCenter.y = std::clamp(newCenter.y, minY, maxY);
                simulationView.setCenter(newCenter);
                lastMousePos = currentMousePos;
            }

            if (isPainting && (currentTool == Simulation_Tool::Set || currentTool == Simulation_Tool::Erase)) {
                sf::Vector2i currentMousePos = mouseMoved->position;
                sf::Vector2f scrollMousePos = data.window.mapPixelToCoords(currentMousePos, simulationView);

                int gridX = static_cast<int>(std::floor(scrollMousePos.x / 30.0f));
                int gridY = static_cast<int>(std::floor(scrollMousePos.y / 30.0f));
                int64_t cellKey = (static_cast<int64_t>(gridX) << 32) | (static_cast<uint32_t>(gridY));

                if (currentTool == Simulation_Tool::Set) {
                    liveCells.insert(cellKey);
                }
                else if (currentTool == Simulation_Tool::Erase) {
                    liveCells.erase(cellKey);
                }
                if (historyIndex < historyStack.size()) {
                    historyStack.resize(historyIndex);
                }

                historyStack.clear();
                historyIndex = 0;
            }
        }
        if (const auto *mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseReleased->button == sf::Mouse::Button::Left) {
                const sf::Vector2i pixelPos = mouseReleased->position;
                const sf::Vector2f scrollMousePos = data.window.mapPixelToCoords(pixelPos, simulationView);
                const sf::Vector2f fixedMousePos = data.window.mapPixelToCoords(pixelPos, data.window.getDefaultView());

                if (runButton.getGlobalBounds().contains(fixedMousePos) && currentTool != Simulation_Tool::Run && isPressingRun) {
                    currentTool = Simulation_Tool::Run;
                }
                else if (setButton.getGlobalBounds().contains(fixedMousePos) && currentTool != Simulation_Tool::Set && isPressingSet) {
                    currentTool = Simulation_Tool::Set;
                    currentRunState = Simulation_RunState::Pause;
                }
                else if (eraseButton.getGlobalBounds().contains(fixedMousePos) && currentTool != Simulation_Tool::Erase && isPressingErase) {
                    currentTool = Simulation_Tool::Erase;
                    currentRunState = Simulation_RunState::Pause;
                }
                else if (resetButton.getGlobalBounds().contains(fixedMousePos) && isPressingReset) {
                    currentRunState = Simulation_RunState::Pause;
                    liveCells.clear();
                    historyStack.clear();
                    historyIndex = 0;
                    generationCounter = 0;
                }
                else if (goBackButton.getGlobalBounds().contains(fixedMousePos) && isPressingGoBack) {
                    data.setScene(Scene::MainMenu);
                    currentRunState = Simulation_RunState::Pause;
                }
                else if (currentTool == Simulation_Tool::Run) {
                    if (Run_startButton.getGlobalBounds().contains(fixedMousePos) && currentRunState != Simulation_RunState::Start && isPressingRun_Start) {
                        currentRunState = Simulation_RunState::Start;
                    }
                    else if (Run_pauseButton.getGlobalBounds().contains(fixedMousePos) && currentRunState != Simulation_RunState::Pause && isPressingRun_Pause) {
                        currentRunState = Simulation_RunState::Pause;
                    }            
                    else if (Run_nextButton.getGlobalBounds().contains(fixedMousePos) && currentRunState == Simulation_RunState::Pause && isPressingRun_Next) {
                        if (historyIndex < historyStack.size()) {
                            const auto &delta = historyStack[historyIndex];

                            for (int64_t cell : delta.liveCells) {
                                liveCells.insert(cell);
                            }
                            for (int64_t cell : delta.deadCells) {
                                liveCells.erase(cell);
                            }
                        }
                        else {
                            CellDelta newDelta = calculateNextGeneration(liveCells);
                            for (int64_t cell : newDelta.liveCells) {
                                liveCells.insert(cell);
                            }
                            for (int64_t cell : newDelta.deadCells) {
                                liveCells.erase(cell);
                            }
                            historyStack.push_back(newDelta);
                        }
                        ++historyIndex;
                        ++generationCounter;
                    }
                    else if (Run_previousButton.getGlobalBounds().contains(fixedMousePos) && currentRunState == Simulation_RunState::Pause && isPressingRun_Previous) {
                        if (historyIndex > 0) {
                            --historyIndex;
                            --generationCounter;
                            const auto &delta = historyStack[historyIndex];
                            
                            for (int64_t cell : delta.liveCells) {
                                liveCells.erase(cell);
                            }
                            for (int64_t cell : delta.deadCells) {
                                liveCells.insert(cell);
                            }
                        }
                    }
                }
            }
            else if (mouseReleased->button == sf::Mouse::Button::Right) {
                isDragging = false;
            }
            
            #pragma region //! Default values
            isPressingRun = false;
            isPressingSet = false;
            isPressingErase = false;
            isPressingReset = false;
            isPressingGoBack = false;
            isPressingRun_Start = false;
            isPressingRun_Pause = false;
            isPressingRun_Next = false;
            isPressingRun_Previous = false;
            isPainting = false;

            resetButton.setFillColor(sf::Color::White);
            resetButton.setOutlineThickness(0.0f);
            resetButtonText->setFillColor(sf::Color::Black);

            goBackButton.setFillColor(sf::Color::White);
            goBackButton.setOutlineThickness(0.0f);
            goBackButtonText->setFillColor(sf::Color::Black);

            Run_nextButton.setFillColor(sf::Color::White);
            Run_nextButton.setOutlineThickness(0.0f);
            Run_nextButtonText->setFillColor(sf::Color::Black);

            Run_previousButton.setFillColor(sf::Color::White);
            Run_previousButton.setOutlineThickness(0.0f);
            Run_previousButtonText->setFillColor(sf::Color::Black);
            #pragma endregion   
        }
        if (event->is<sf::Event::MouseLeft>() || event->is<sf::Event::FocusLost>()) {
            isDragging = false;
            isPainting = false;
        }
        if (const auto *mouseWheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
            if (mouseWheel->wheel == sf::Mouse::Wheel::Vertical) {
                float factor = (mouseWheel->delta > 0) ? 0.9f : 1.1f;
                float nextZoom = currentZoom * factor;

                if (nextZoom >= minZoom && nextZoom <= maxZoom) {
                    currentZoom = nextZoom;
                    simulationView.zoom(factor);
                }
            }
        }
    }

    #pragma region //! Update
    if (currentRunState == Simulation_RunState::Start) {
        timeAccumulator += simulationClock.restart().asSeconds();

        while (timeAccumulator >= data.timeInterval) {
            timeAccumulator -= data.timeInterval;

            if (historyIndex < historyStack.size()) {
                const auto &delta = historyStack[historyIndex];
                for (int64_t cell : delta.liveCells) {
                    liveCells.insert(cell);
                }
                for (int64_t cell : delta.deadCells) {
                    liveCells.erase(cell);
                }
            }
            else {
                CellDelta newDelta = calculateNextGeneration(liveCells);
                for (int64_t cell : newDelta.liveCells) {
                    liveCells.insert(cell);
                }
                for (int64_t cell : newDelta.deadCells) {
                    liveCells.erase(cell);
                }
                historyStack.push_back(newDelta);
            }
            ++historyIndex;
            ++generationCounter;
        }
    } 
    else {
        simulationClock.restart(); 
    }
        //* Generation counter
    generationCounterText->setString("Generation #" + std::to_string(generationCounter));
        //* [Run]
    if (currentTool == Simulation_Tool::Run) {
        runButton.setFillColor(sf::Color::Black);
        runButton.setOutlineThickness(2.0f);
        runButton.setOutlineColor(sf::Color::White);
        runButtonText->setFillColor(sf::Color::White);
            //* [Start]
        if (currentRunState == Simulation_RunState::Start) {
            Run_startButton.setFillColor(sf::Color::Black);
            Run_startButton.setOutlineThickness(2.0f);
            Run_startButton.setOutlineColor(sf::Color::White);
            Run_startButtonText->setFillColor(sf::Color::White);
        }
        else {
            Run_startButton.setFillColor(sf::Color::White);
            Run_startButton.setOutlineThickness(0.0f);
            Run_startButtonText->setFillColor(sf::Color::Black);
        }
            //* [Pause]
        if (currentRunState == Simulation_RunState::Pause) {
            Run_pauseButton.setFillColor(sf::Color::Black);
            Run_pauseButton.setOutlineThickness(2.0f);
            Run_pauseButton.setOutlineColor(sf::Color::White);
            Run_pauseButtonText->setFillColor(sf::Color::White);
        }
        else {
            Run_pauseButton.setFillColor(sf::Color::White);
            Run_pauseButton.setOutlineThickness(0.0f);
            Run_pauseButtonText->setFillColor(sf::Color::Black);
        }
    }
    else {
        runButton.setFillColor(sf::Color::White);
        runButton.setOutlineThickness(0.0f);
        runButtonText->setFillColor(sf::Color::Black);
    }
        //* [Set]
    if (currentTool == Simulation_Tool::Set) {
        setButton.setFillColor(sf::Color::Black);
        setButton.setOutlineThickness(2.0f);
        setButton.setOutlineColor(sf::Color::White);
        setButtonText->setFillColor(sf::Color::White);
    }
    else {
        setButton.setFillColor(sf::Color::White);
        setButton.setOutlineThickness(0.0f);
        setButtonText->setFillColor(sf::Color::Black);
    }
        //* [Erase]
    if (currentTool == Simulation_Tool::Erase) {
        eraseButton.setFillColor(sf::Color::Black);
        eraseButton.setOutlineThickness(2.0f);
        eraseButton.setOutlineColor(sf::Color::White);
        eraseButtonText->setFillColor(sf::Color::White);
    }
    else {
        eraseButton.setFillColor(sf::Color::White);
        eraseButton.setOutlineThickness(0.0f);
        eraseButtonText->setFillColor(sf::Color::Black);
    }
    #pragma endregion

    #pragma region //! Initialize grid
    sf::Vector2f viewCenter = simulationView.getCenter();
    sf::Vector2f viewSize = simulationView.getSize();

    float left = viewCenter.x - viewSize.x / 2.0f;
    float right = viewCenter.x + viewSize.x / 2.0f;
    float top = viewCenter.y - viewSize.y / 2.0f;
    float bottom = viewCenter.y + viewSize.y / 2.0f;

    float startX = std::floor(left / gridStep) * gridStep;
    float endX = std::ceil(right / gridStep) * gridStep;
    float startY = std::floor(top / gridStep) * gridStep;
    float endY = std::ceil(bottom / gridStep) * gridStep;

    sf::VertexArray lines(sf::PrimitiveType::Lines);
    for (float x = startX; x <= endX; x += gridStep) {
        lines.append({{x, top}, gridColor});
        lines.append({{x, bottom}, gridColor});
    }
    for (float y = startY; y <= endY; y += gridStep) {
        lines.append({{left, y}, gridColor});
        lines.append({{right, y}, gridColor});
    }
    #pragma endregion

    #pragma region //! Draw and display
    data.window.clear(backgroundColor);
        #pragma region //* Not fixed
    data.window.setView(simulationView);

    data.window.draw(lines);

    sf::VertexArray cellVA(sf::PrimitiveType::Triangles);
    for (int64_t key : liveCells) {
        int x = static_cast<int>(static_cast<int32_t>((key >> 32) & 0xFFFFFFFF));
        int y = static_cast<int>(static_cast<int32_t>(key & 0xFFFFFFFF));
        
        float posX = x * 30.0f;
        float posY = y * 30.0f;

        if (posX + 30.0f < left || posX > right || posY + 30.0f < top || posY > bottom) {
            continue;
        }

        cellVA.append({sf::Vector2f(posX, posY), cellColor});
        cellVA.append({sf::Vector2f(posX + 30.0f, posY), cellColor});
        cellVA.append({sf::Vector2f(posX, posY + 30.0f), cellColor});

        cellVA.append({sf::Vector2f(posX + 30.0f, posY), cellColor});
        cellVA.append({sf::Vector2f(posX + 30.0f, posY + 30.0f), cellColor});
        cellVA.append({sf::Vector2f(posX, posY + 30.0f), cellColor});
    }
    data.window.draw(cellVA);
        #pragma endregion
        #pragma region //* Fixed
    data.window.setView(data.window.getDefaultView());

    data.window.draw(runButton);
    data.window.draw(*runButtonText);
    data.window.draw(setButton);
    data.window.draw(*setButtonText);
    data.window.draw(eraseButton);
    data.window.draw(*eraseButtonText);
    data.window.draw(resetButton);
    data.window.draw(*resetButtonText);
    data.window.draw(goBackButton);
    data.window.draw(*goBackButtonText);
    data.window.draw(*generationCounterText);
    if (currentTool == Simulation_Tool::Run) {
        data.window.draw(Run_startButton);
        data.window.draw(*Run_startButtonText);
        data.window.draw(Run_pauseButton);
        data.window.draw(*Run_pauseButtonText);
        if (currentRunState == Simulation_RunState::Pause) {
            data.window.draw(Run_nextButton);
            data.window.draw(*Run_nextButtonText);
            data.window.draw(Run_previousButton);
            data.window.draw(*Run_previousButtonText);
        }
    }

    data.window.display();
        #pragma endregion;
    #pragma endregion
}
#include "Interface.h"

void Interface::checkloadingImage(Texture& my_Texture, Image my_Image) {
    try {
        if (!my_Texture.loadFromImage(my_Image)) {
            throw std::runtime_error("Failed to load image!");
        }
    }
    catch (const std::exception& e) {
        handleException(e);
    }
}

void Interface::checkloadingFile(Texture& my_Texture, string my_path) {
    try {
        if (!my_Texture.loadFromFile(my_path)) {
            throw std::runtime_error("Failed to load file!");
        }
    }
    catch (const std::exception& e) {
        handleException(e);
    }
}

void Interface::checkloadingImage(Image& my_Image, string my_path) {
    try {
        if (!my_Image.loadFromFile(my_path)) {
            throw std::runtime_error("Failed to load file!");
        }
    }
    catch (const std::exception& e) {
        handleException(e);
    }
}

void Interface::handleException(const std::exception& e) const {
    sf::RenderWindow errorWindow(sf::VideoMode(400, 200), "Error");

    Label errorLabel(50, 50, e.what());
    errorLabel.setFontSize(24);
    errorLabel.setColor(sf::Color::Red);

    while (errorWindow.isOpen()) {
        sf::Event event;
        while (errorWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                errorWindow.close();
            }
        }

        errorWindow.clear(sf::Color::White);
        errorWindow.draw(errorLabel.displayText());
        errorWindow.display();
    }
    exit(errno);
}

void Interface::resizeObjects() {
    sf::Vector2u windowSize = window.getSize();

    double scaleX_buttons = windowSize.x / BOARD_SIZE_WIDTH;
    double scaleY_buttons = windowSize.y / BOARD_SIZE_HEIGHT;

    random_generation.setPosition(button_xCoordinate * scaleX_buttons, RandGenerate_button_yCoordinate * scaleY_buttons);
    random_generation.setSize(button_width * scaleX_buttons, button_height * scaleY_buttons);

    A_star_button.setPosition(button_xCoordinate * scaleX_buttons, A_star_button_yCoordinate * scaleY_buttons);
    A_star_button.setSize(button_width * scaleX_buttons, button_height * scaleY_buttons);

    RBFS_button.setPosition(button_xCoordinate * scaleX_buttons, RBFS_button_yCoordinate * scaleY_buttons);
    RBFS_button.setSize(button_width * scaleX_buttons, button_height * scaleY_buttons);
}

void Interface::setInitial(vector<int>& queens) const {
    for (int i = 0; i < QUEENS_SIZE; i++) {
        sf::Vector2f position = queenses[i].getPosition();
        float x = position.x;
        queens[i] = int(x / constants::CELL_SIZE + 2);
    }
}

Interface::Interface() : window(sf::VideoMode(BOARD_SIZE_WIDTH, BOARD_SIZE_HEIGHT), "Chess board"),
random_generation(button_xCoordinate, RandGenerate_button_yCoordinate, button_width, button_height, "    Generate\n      board"),
A_star_button(button_xCoordinate, A_star_button_yCoordinate, button_width, button_height, "     A*    \n     algorithm"),
RBFS_button(button_xCoordinate, RBFS_button_yCoordinate, button_width, button_height, "    RBFS    \n    algorithm"),
roots(roots_xCoordinate, roots_yCoordinate) {
    checkloadingFile(boardTexture,"board.png");
    checkloadingImage(queenImage,"queen2.png");
    queenImage.createMaskFromColor(Color(209, 139, 71));
    checkloadingImage(queenTexture, queenImage);
    checkloadingFile(menuTexture,"wallpaper.jpg");
    checkloadingFile(buttonTexture,"button.png");
    checkloadingFile(buttonTexture2, "button2.png");

    menuSprite.setTexture(menuTexture);
    menuSprite.setScale(menu_xScale, menu_yScale);
    menuSprite.setPosition(menu_xPosition, menu_yPosition);

    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition(button_sprite_xCoordinate, RandGenerate_button_sprite_yCoordinate);
    buttonSprite.setScale(button_xScale, button_yScale);

    A_star_Sprite.setTexture(buttonTexture);
    A_star_Sprite.setPosition(button_sprite_xCoordinate, A_star_button_sprite_yCoordinate);
    A_star_Sprite.setScale(button_xScale, button_yScale);

    RBFSSprite.setTexture(buttonTexture);
    RBFSSprite.setPosition(button_sprite_xCoordinate, RBFS_button_sprite_yCoordinate);
    RBFSSprite.setScale(button_xScale, button_yScale);

    Roots_Sprite.setTexture(buttonTexture2);
    Roots_Sprite.setPosition(button_sprite_xCoordinate, Roots_sprite_yCoordinate);
    Roots_Sprite.setScale(Roots_xScale, Roots_yScale);

    boardSprite.setTexture(boardTexture);

    const sf::Vector2u textureSize = queenTexture.getSize();

    const double scaleX = DESIRED_WIDTH / textureSize.x;
    const double scaleY = DESIRED_HEIGHT / textureSize.y;

    for (int i = 0; i < QUEENS_SIZE; i++) {
        queenses[i].setTexture(queenTexture);
        queenses[i].setScale(scaleX, scaleY);
    }
}

void Interface::run(File& my_file) {
    srand(time(NULL));
    bool flag = false, flag2 = false;
    vector<int> initialQueens(8);
    BoardStateBase boardStateCheck(initialQueens);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                resizeObjects();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (random_generation.select(mousePos))
                {
                    flag = true;
                    generateRandomQueens(initialQueens);
                    boardStateCheck.setQueens(initialQueens);
                }
                else if (A_star_button.select(mousePos) && !boardStateCheck.isGoalState() && flag) {
                    flag2 = true;
                    runAStarAlgorithm(initialQueens, my_file, boardStateCheck);
                }
                else if (RBFS_button.select(mousePos) && !boardStateCheck.isGoalState() && flag) {
                    flag2 = true;
                    runRBFSAlgorithm(initialQueens, my_file, boardStateCheck);
                }
                else if (mousePos.x < 480 && mousePos.y < 480){
                    ReplaceQueens(initialQueens,mousePos,boardStateCheck);
                }
            }
        }
        draw(flag, flag2);
    }
}

void Interface::generateRandomQueens(vector<int>& initialQueens) {
    for (int i = 0; i < QUEENS_SIZE; i++) {
        initialQueens[i] = rand() % 8;
        queenses[i].setPosition(CELL_SIZE * initialQueens[i] - 2, i * CELL_SIZE);
    }
}

void Interface::ReplaceQueens(vector<int>& initialQueens, Vector2i Mousepos,BoardStateBase& boardStateCheck) {
       int col = Mousepos.x / CELL_SIZE;
       int row = Mousepos.y / CELL_SIZE;

       queenses[row].setPosition(CELL_SIZE * col - 2, CELL_SIZE * row);
       initialQueens[row] = col;
       boardStateCheck.setQueens(initialQueens);
}

void Interface::runAStarAlgorithm(vector<int>& initialQueens, File& my_file, BoardStateBase& boardStateCheck) {
    A_star initialState(initialQueens);
    my_file.write(initialQueens, "The initial state of the board(A*):");

    initialState.resetTotalNodesVisited();
    vector<BoardStateBase> solution = solve(initialState);
    if (!solution.empty()) {
        my_file.write(solution[0].getQueens(), "The final state of the board(A*):");
        roots.setText("   Root`s\n   amount:", initialState.getTotalNodesVisited());
        for (int i = solution.size() - 1; i >= 0; i--) {
            BoardStateBase state = solution[i];
            for (int j = 0; j < QUEENS_SIZE; j++) {
                queenses[j].setPosition(CELL_SIZE * state.getQueens()[j] - 2, j * CELL_SIZE);
            }
            draw(true);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        setInitial(initialQueens);
        boardStateCheck.setQueens(initialQueens);
    }
    else {
        roots.setText("\tSolution\ndoes not exist:");
    }
}

void Interface::runRBFSAlgorithm(vector<int>& initialQueens, File& my_file, BoardStateBase& boardStateCheck) {
    RBFS_alg initialState(initialQueens);
    my_file.write(initialQueens, "The initial state of the board(RBFS):");
    std::vector<BoardStateBase> solution;
    std::unordered_set<BoardStateBase> visitedStates;

    initialState.resetTotalNodesVisited();
    bool foundSolution = RBFS(initialState, 0, initialState.calculateHeuristic(), 0, solution, visitedStates);

    if (foundSolution) {
        my_file.write(solution.back().getQueens(), "The final state of the board(RBFS):");
        roots.setText("\tRoot`s\n\tamount:", initialState.getTotalNodesVisited());
        for (int i = 0; i < solution.size(); i++) {
            BoardStateBase state = solution[i];
            for (int j = 0; j < QUEENS_SIZE; j++) {
                queenses[j].setPosition(CELL_SIZE * state.getQueens()[j] - 2, j * CELL_SIZE);
            }
            draw(true);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        setInitial(initialQueens);
        boardStateCheck.setQueens(initialQueens);
    }
    else {
        roots.setText("\tSolution\ndoes not exist:");
    }
}

void Interface::draw(bool flag, bool flag2) {
    window.clear();
    window.draw(boardSprite);
    window.draw(menuSprite);
    window.draw(buttonSprite);
    window.draw(A_star_Sprite);
    window.draw(RBFSSprite);
    window.draw(random_generation.displayText());
    window.draw(A_star_button.displayText());
    window.draw(RBFS_button.displayText());
    if (flag) {
        drawQueens();
    }
    if (flag2) {
        drawRoots();
    }
    window.display();
}

void Interface::drawQueens() {
    for (int i = 0; i < QUEENS_SIZE; i++) {
        window.draw(queenses[i]);
    }
}

void Interface::drawRoots() {
    window.draw(Roots_Sprite);
    window.draw(roots.displayText());
}
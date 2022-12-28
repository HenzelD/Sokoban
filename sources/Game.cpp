#include "Game.h"

Game::Game(int gameMode) {
    this->resourcesLoaded = false;
    this->gameActive = false;
    this->victory = false;
    this->gameMode = gameMode;
    this->player.setGameMode(gameMode);
    if (gameMode == 1) {
        this->boxesNumber = 3;
        this->maxX = 10;
        this->maxY = 6;
    }
    else {
        this->boxesNumber = 5;
        this->maxX = 20;
        this->maxY = 12;
    }
}

void Game::generateWalls() {
    Wall* wall;
    for (int i = 0; i < maxX; i++) {
        wall = new Wall(gameMode);
        wall->setPosition(Position(i, 0));
        wall->setTexture(wallTexture);
        walls.push_back(wall);
        wall = new Wall(gameMode);
        wall->setPosition(Position(i, maxY - 1));
        wall->setTexture(wallTexture);
        walls.push_back(wall);
    }
    for (int i = 1; i < maxY - 1; i++) {
        wall = new Wall(gameMode);
        wall->setPosition(Position(0, i));
        wall->setTexture(wallTexture);
        walls.push_back(wall);
        wall = new Wall(gameMode);
        wall->setPosition(Position(maxX - 1, i));
        wall->setTexture(wallTexture);
        walls.push_back(wall);
    }
    if (gameMode == 2) {
        for (int i = 0; i < 15; i++) {
            Position position = randomPosition();
            while (isPositionOfWall(position)) {
                position = randomPosition();
            }
            wall = new Wall(gameMode);
            wall->setPosition(position);
            wall->setTexture(wallTexture);
            walls.push_back(wall);
        }
    }
}

void Game::generateTargets() {
    for (int i = 0; i < boxesNumber; i++) {
        Position position = randomPosition();
        while (isPositionOfWall(position) || isPositionOfTarget(position)) {
            position = randomPosition();
        }
        Target* target = new Target(gameMode);
        target->setPosition(position);
        target->setTexture(targetTexture);
        targets.push_back(target);
    }
}

void Game::generateBoxes() {
    for (int i = 0; i < boxesNumber; i++) {
        Position position = randomPosition();
        while (isPositionOfWall(position) 
            || isPositionOfTarget(position) 
            || isPositionOfBox(position)
            || isNextToWall(position)) {
            position = randomPosition();
        }
        Box* box = new Box(gameMode);
        box->setPosition(position);
        box->setTexture(boxTexture);
        boxes.push_back(box);
    }
}

Position Game::randomPosition() {
    int x = rand() % (maxX - 3) + 1;
    int y = rand() % (maxY - 3) + 1;
    return Position(x, y);
}

bool Game::isPositionOfWall(Position position) {
    bool isPositionOfWall = false;
    for (Wall* wall : walls) {
        if (position == wall->getPosition()) {
            isPositionOfWall = true;
        }
    }
    return isPositionOfWall;
}

bool Game::isPositionOfTarget(Position position) {
    bool isPositionOfTarget = false;
    for (Target* target : targets) {
        if (position == target->getPosition()) {
            isPositionOfTarget = true;
        }
    }
    return isPositionOfTarget;
}

bool Game::isPositionOfBox(Position position) {
    bool isPositionOfBox = false;
    for (Box* box : boxes) {
        if (position == box->getPosition()) {
            isPositionOfBox = true;
        }
    }
    return isPositionOfBox;
}

bool Game::isNextToWall(Position position) {
    bool isNextToWall = false;
    Position up = position;
    Position down = position;
    Position right = position;
    Position left = position;
    up.goUp();
    down.goDown();
    right.goRight();
    left.goLeft();
    for (Wall* wall : walls) {
        if (up == wall->getPosition()
            || down == wall->getPosition()
            || right == wall->getPosition()
            || left == wall->getPosition()) {
            isNextToWall = true;
        }
    }
    return isNextToWall;
}

void Game::displayWalls(RenderWindow& renderWindow) {
    for (Wall* wall : walls) {
        wall->display(renderWindow);
    }
}

void Game::displayTargets(RenderWindow& renderWindow) {
    for (Target* target : targets) {
        target->display(renderWindow);
    }
}

void Game::displayBoxes(RenderWindow& renderWindow) {
    for (Box* box : boxes) {
        box->display(renderWindow);
    }
}

void Game::displayGame(RenderWindow& renderWindow) {
    renderWindow.clear(Color::White);
    background.display(renderWindow);
    displayWalls(renderWindow);
    displayTargets(renderWindow);
    displayBoxes(renderWindow);
    player.display(renderWindow);
    handleVictory(renderWindow);
    renderWindow.display();
}

int Game::handleKeyEvent(RenderWindow& renderWindow, Event& event) {
    int direction = 0;
    while (renderWindow.pollEvent(event)) {
        if (event.type == Event::Closed
            || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
            renderWindow.close();
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
            prepareBoard();
        }
        else if (event.type == Event::KeyPressed && gameActive) {
            switch (event.key.code) {
            case Keyboard::Right:
                direction = 1;
                break;
            case Keyboard::Left:
                direction = 2;
                break;
            case Keyboard::Up:
                direction = 3;
                break;
            case Keyboard::Down:
                direction = 4;
                break;
            }
        }
    }
    return direction;
}

bool Game::areAllBoxesOnTargets() {
    bool allBoxesOnTargets = true;
    for (Box* box : boxes) {
        if (!isPositionOfTarget(box->getPosition())) {
            allBoxesOnTargets = false;
        }
    }
    return allBoxesOnTargets;
}

void Game::handleDirection(int direction) {
    if (direction != 0 && player.canMove(direction, walls, boxes)) {
        player.move(direction, boxes);
        if (areAllBoxesOnTargets()) {
            victory = true;
            gameActive = false;
        }
    }
}

void Game::handleVictory(RenderWindow& renderWindow) {
    if (victory) {
        renderWindow.draw(victorySprite);
    }
}

bool Game::loadResources() {
    std::string textureVersion = "120";
    if (gameMode == 2) {
        textureVersion = "60";
    }
    try {
        Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("textures/background.png")) {
            throw (std::string) "Wystapil blad przy wczytywaniu tekstury tla ze sciezki " 
                + "\x1B[31mtextures/background.png\033[0m\t\t";
        }
        background.setTexture(backgroundTexture);
        if (!victoryTexture.loadFromFile("textures/victory.png")) {
            throw (std::string) "Wystapil blad przy wczytywaniu tekstury ekranu zwyciestwa ze sciezki "
                + "\x1B[31mtextures/victory.png\033[0m\t\t";
        }
        victorySprite.setTexture(victoryTexture);
        victorySprite.setPosition(Vector2f(300, 113));
        Texture playerRightTexture, playerLeftTexture;
        if (!playerRightTexture.loadFromFile("textures/" + textureVersion + "/playerRight.png") \
            || !playerLeftTexture.loadFromFile("textures/" + textureVersion + "/playerLeft.png")) {
            throw (std::string) "Wystapil blad przy wczytywaniu tekstur postaci gracza ze sciezki "
                + "\x1B[31mtextures/" + textureVersion + "/playerRight.png\033[0m\t\t"
                + " lub "
                + "\x1B[31mtextures/" + textureVersion + "/playerLeft.png\033[0m\t\t";
        }
        player.setTexture(playerRightTexture, playerLeftTexture);
        if (!wallTexture.loadFromFile("textures/" + textureVersion + "/wall.png")) {
            throw (std::string) "Wystapil blad przy wczytywaniu tekstury sciany ze sciezki "
                + "\x1B[31mtextures/" + textureVersion + "/wall.png\033[0m\t\t";
        }
        if (!targetTexture.loadFromFile("textures/" + textureVersion + "/target.png")) {
            throw (std::string) "Wystapil blad przy wczytywaniu tekstury celu ze sciezki "
                + "\x1B[31mtextures/" + textureVersion + "/target.png\033[0m\t\t";
        }
        if (!boxTexture.loadFromFile("textures/" + textureVersion + "/box.png")) {
            throw (std::string)"Wystapil blad przy wczytywaniu tekstury skrzynki ze sciezki "
                + "\x1B[31mtextures/" + textureVersion + "/box.png\033[0m\t\t";
        }
        return true;
    }
    catch (std::string errorMessage) {
        system("cls");
        std::cout << errorMessage << std::endl;
        return false;
    }
}

void Game::clearBoard() {
    for (Wall* wall : walls) {
        delete(wall);
    }
    for (Target* target : targets) {
        delete (target);
    }
    for (Box* box : boxes) {
        delete (box);
    }
    walls.clear();
    boxes.clear();
    targets.clear();
}

void Game::prepareBoard() {
    clearBoard();

    generateWalls();
    generateTargets();
    generateBoxes();

    Position playerPosition = randomPosition();
    while (isPositionOfWall(playerPosition) 
        || isPositionOfTarget(playerPosition) 
        || isPositionOfBox(playerPosition)) {
        playerPosition = randomPosition();
    }
    player.setPosition(playerPosition);
    victory = false;
    gameActive = true;
}

void Game::handleGameLoop(RenderWindow& renderWindow, Event& event) {
    handleDirection(handleKeyEvent(renderWindow, event));
    displayGame(renderWindow);
}

void Game::play() {
    RenderWindow renderWindow(VideoMode(1200, 720), "Sokoban");
    Event event;
    loadResources();
    while (renderWindow.isOpen()) {
        if (resourcesLoaded) {
            handleGameLoop(renderWindow, event);
        }
        else if (loadResources()) {
            resourcesLoaded = true;
            prepareBoard();
        }
        else {
            renderWindow.close();
        }
    }
    clearBoard();
}
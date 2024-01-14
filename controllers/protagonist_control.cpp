#include "protagonist_control.h"
#include <iostream>
#include <cmath>
#include <QTimer>

// Constructor for ProtagonistController class
ProtagonistController::ProtagonistController(GameModel *model, const std::unique_ptr <ProtagonistModel> &protag)
        : protagModel(protag), gameModel(model) {
    // Map commands to functions
    commandHandlers = {
            {"up",     [this]() { moveUp(); }},
            {"down",   [this]() { moveDown(); }},
            {"left",   [this]() { moveLeft(); }},
            {"right",  [this]() { moveRight(); }},
            {"goto ",  [this]() { goTo(protagModel->getXPos(), protagModel->getYPos()); }
            },
            {"attack", [this]() { attackNearest(); }},
            {"heal",   [this]() { healNearest(); }},
            // Add other command handlers here...
    };
    healthDecreaseTimer = new QTimer(this);
    movementTimer = new QTimer(this);
}

// Function to handle a fight with an enemy
void ProtagonistController::fight(std::unique_ptr <Enemy> &enemy) {
    if (enemy->getDefeated())
        return;
    float remainHP = protagModel->getHealth() - difficulty_factor * enemy->getValue();
    float remainEP = protagModel->getEnergy() + (1 + difficulty_factor) * enemy->getValue();
    updateHP(remainHP);
    updateEP(remainEP);
    enemy->setDefeated(true);
    qDebug() << "Enemy killed";
}

void ProtagonistController::updateDifficulty(int difficulty) {
    difficulty_factor = difficulty * 0.1;
    qDebug() << "Difficulty factor: " << difficulty_factor;
}

/********************************************************************************
Basic functions
*********************************************************************************/

// Function to heal the protagonist using a health pack
void ProtagonistController::heal(std::unique_ptr <HealthPack> &hp) {
    float remainHP = protagModel->getHealth() + (1 + difficulty_factor) * hp->getHP();
    updateHP(remainHP);
    hp->setHP(0.0f);
}

// Function to poison the protagonist
void ProtagonistController::poisoned(float poisonLevel) {
    if (!protagModel->getIsPoisoned()) {
        protagModel->setIsPoisoned(true);

        // Poison duration and timer setup

        elapsed = 0; // Time elapsed

        // Calculate the amount of poison to apply each second
        poisonPerInterval = poisonLevel / 30.0;

        connect(healthDecreaseTimer, SIGNAL(timeout()), this, SLOT(handlePoisoned()));

        healthDecreaseTimer->start(timerInterval);
    }
}

// Function to update the protagonist's health
void ProtagonistController::updateHP(float remainHP) {
    if (remainHP <= 0.0f) {
        protagModel->setHealth(0.0f);
        emit protagDead();
    } else if (remainHP >= 100.0f) {
        protagModel->setHealth(100.0f);
    } else {
        protagModel->setHealth(remainHP);
    }
}

// Function to update the protagonist's energy
void ProtagonistController::updateEP(float remainEP) {
    if (remainEP <= 0.0f) {
        protagModel->setEnergy(0.0f);
        emit protagTired();
        emit protagDead();
    } else if (remainEP >= 100.0f) {
        protagModel->setEnergy(100.0f);
    } else {
        protagModel->setEnergy(remainEP);
    }
}

// Function to move the protagonist right
int ProtagonistController::moveRight() {
    int x = protagModel->getXPos();
    int y = protagModel->getYPos();
    int row = gameModel->getRows();

    // Check if the right move is possible
    if (!gameModel->isWall(x + 1, y) && (x + 1) < row) {
        // Move right
        protagModel->setPos(x + 1, y);
        updateProtagonistState(x + 1, y);
        return 1;
    } else {
        return 0; // Return 0 if the move is not possible
    }
}

// Function to move the protagonist left
int ProtagonistController::moveLeft() {
    int x = protagModel->getXPos();
    int y = protagModel->getYPos();

    // Check if the left move is possible
    if (!gameModel->isWall(x - 1, y) && (x - 1) >= 0) {
        // Move left
        protagModel->setPos(x - 1, y);
        updateProtagonistState(x - 1, y);
        return 1; // Return 1 if the move is successful
    } else {
        return 0; // Return 0 if the move is not possible
    }
}

// Function to move the protagonist up
int ProtagonistController::moveUp() {
    int x = protagModel->getXPos();
    int y = protagModel->getYPos();

    // Check if the up move is possible
    if (!gameModel->isWall(x, y - 1) && (y - 1) >= 0) {
        // Move up
        protagModel->setPos(x, y - 1);
        updateProtagonistState(x, y - 1);
        return 1; // Return 1 if the move is successful
    } else {
        return 0; // Return 0 if the move is not possible
    }
}

// Function to move the protagonist down
int ProtagonistController::moveDown() {
    int x = protagModel->getXPos();
    int y = protagModel->getYPos();
    int col = gameModel->getCols();

    // Check if the down move is possible
    if (!gameModel->isWall(x, y + 1) && (y + 1) < col) {
        // Move down
        protagModel->setPos(x, y + 1);
        updateProtagonistState(x, y + 1);
        return 1; // Return 1 if the move is successful
    } else {
        return 0; // Return 0 if the move is not possible
    }
}

// Function to update the protagonist's state based on the tile
void ProtagonistController::updateProtagonistState(int x, int y) {
    if (nextLevel) {
        return; // Skip updates if transitioning to the next level
    }

    // Safely access elements in gameModel
    auto it_T = gameModel->findTile(x, y);
    if (it_T != gameModel->getTiles().end()) {
        float remainEP = protagModel->getEnergy() - difficulty_factor * ((1.0f - it_T->get()->getValue()) * 3.0f);
        updateEP(remainEP);
    }

    auto it_E = gameModel->findEnemy(x, y);
    if (it_E != gameModel->getEnemies().end()) {
        XEnemy *xEnemy = dynamic_cast<XEnemy *>(it_E->get());
        if (xEnemy) {
            xEnemy->bounceProtagonist();
        }
        fight(*it_E);
    }

    auto it_H = gameModel->findHealthPack(x, y);
    if (it_H != gameModel->getHealthPacks().end()) {
        heal(*it_H);
    }

    float poisonLevel = gameModel->findPoison(x, y);
    if (poisonLevel > 0.0f) {
        poisoned(poisonLevel);
    }

    auto it_G = gameModel->findGate(x, y);
    if (it_G != gameModel->getGates().end()) {
        stopAutoPlay();
        stopClickMove();
        nextLevel = true;
        qDebug() << "Next level in update: " << nextLevel;
        it_G->get()->updateLevel();
    }
}

// Function to handle the protagonist being poisoned
void ProtagonistController::handlePoisoned() {
    if (elapsed <= totalTime) {
        elapsed += timerInterval;
        updateHP(protagModel->getHealth() - poisonPerInterval);
    } else {
        healthDecreaseTimer->stop();
        protagModel->setIsPoisoned(false);
    }
}

void ProtagonistController::attackNearest() {
    Tile *en_nearest;
    float minDistance = std::numeric_limits<float>::max();
    for (const auto &enemy: gameModel->getEnemies()) {
        if (!enemy->getDefeated()) {
            int dx = protagModel->getXPos() - enemy->getXPos();
            int dy = protagModel->getYPos() - enemy->getYPos();
            float distance = std::sqrt(dx * dx + dy * dy);
            if (distance < minDistance) {
                minDistance = distance;
                en_nearest = enemy.get();
            }
        }
    }
    goTo(en_nearest->getXPos(), en_nearest->getYPos());

}

void ProtagonistController::healNearest() {
    Tile *hp_nearest;
    float minDistance = std::numeric_limits<float>::max();
    for (const auto &hp: gameModel->getHealthPacks()) {
        if (hp->getHP() > 0) {
            int dx = protagModel->getXPos() - hp->getXPos();
            int dy = protagModel->getYPos() - hp->getYPos();
            float distance = std::sqrt(dx * dx + dy * dy);
            if (distance < minDistance) {
                minDistance = distance;
                hp_nearest = hp.get();
            }
        }
    }
    qDebug() << hp_nearest->getXPos() << hp_nearest->getYPos();
    goTo(hp_nearest->getXPos(), hp_nearest->getYPos());
}

// Function to move the protagonist to a specified position
void ProtagonistController::goTo(int x_target, int y_target) {
    stopAutoPlay();
    stopClickMove();

    // Check if the target position is valid
    if (x_target < 0 || x_target >= gameModel->getRows() || y_target < 0 || y_target >= gameModel->getCols() ||
        gameModel->isWall(x_target, y_target)) {
        qDebug() << "Invalid target position or blocked by a wall.";
        return;
    }

    // Calculate the path using a simple heuristic, e.g., Manhattan distance
    std::vector<int> path;

    int currentX = protagModel->getXPos();
    int currentY = protagModel->getYPos();

    while (currentX != x_target || currentY != y_target) {
        int dx = x_target - currentX;
        int dy = y_target - currentY;

        if (std::abs(dx) > std::abs(dy)) {
            if (dx > 0) {
                path.push_back(6); // Move right
                currentX++;
            } else {
                path.push_back(2); // Move left
                currentX--;
            }
        } else {
            if (dy > 0) {
                path.push_back(4); // Move down
                currentY++;
            } else {
                path.push_back(0); // Move up
                currentY--;
            }
        }
    }

    if (!path.empty()) {
        this->path = path; // Assign the calculated path to the member variable
        currentIndex = 0;
        connect(movementTimer, &QTimer::timeout, this, &ProtagonistController::moveNextStep);
        movementTimer->start(250); // Adjust as needed
        isClickMove = true;
        // Emit signal to mark the tile as visited
        emit tileVisited(x_target, y_target);
    } else {
        qDebug() << "No path found for goTo";
    }
}

Tile *ProtagonistController::findNearestObjective() {
    Tile *nearestObjective = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    int protagonistX = protagModel->getXPos();
    int protagonistY = protagModel->getYPos();

    bool prioritizeHealthPack = protagModel->getHealth() < 50.0f;
    bool enemiesAllDefeated = std::all_of(gameModel->getEnemies().begin(), gameModel->getEnemies().end(),
                                          [](const auto &enemy) { return enemy->getDefeated(); });

    auto updateNearest = [&](const auto &obj) {
        int objX = obj->getXPos();
        int objY = obj->getYPos();
        float distance = std::hypot(objX - protagonistX, objY - protagonistY);
        if (distance < minDistance) {
            minDistance = distance;
            nearestObjective = obj.get();
        }
    };

    if (prioritizeHealthPack) {
        for (const auto &hp: gameModel->getHealthPacks()) {
            if (hp->getHP() > 0) {
                updateNearest(hp);
            }
        }
    }

    if (!nearestObjective && !enemiesAllDefeated) {
        for (const auto &enemy: gameModel->getEnemies()) {
            if (!enemy->getDefeated()) {
                updateNearest(enemy);
            }
        }
    }

    if (!nearestObjective || enemiesAllDefeated) {
        for (const auto &gate: gameModel->getGates()) {
            if (gate->getType() == 1)
                updateNearest(gate);
        }
    }

    return nearestObjective;
}

void ProtagonistController::handleStep(int step) {
    if (!isProtagonistActive()) {
        qDebug() << "Protagonist is not active";
        return;
    }
    // 0: up, 1: up-left, 2: left, 3: down-left, 4: down, 5: down-right, 6: right, 7: up-right
    qDebug() << "Step: " << step;
    switch (step) {
        case 0:
            moveUp();
            break;
        case 1:
            moveUp();
            moveLeft();
            break;
        case 2:
            moveLeft();
            break;
        case 3:
            moveDown();
            moveLeft();
            break;
        case 4:
            moveDown();
            break;
        case 5:
            moveDown();
            moveRight();
            break;
        case 6:
            moveRight();
            break;
        case 7:
            moveUp();
            moveRight();
            break;
        default:
            qDebug() << "Invalid step: " << step;
            break;
    }
}

void ProtagonistController::clickMove() {
    stopAutoPlay();

    // Check if the clicked tile coordinates are valid
    if (clickedTileCoords.first < 0 || clickedTileCoords.second < 0) {
        qDebug() << "Invalid clicked tile coordinates";
        return;
    }

    const auto &tiles = gameModel->getTiles();
    Tile *startTile = dynamic_cast<Tile *>(protagModel.get());

    std::vector <TileAdapter> tileAdapters;
    tileAdapters.reserve(tiles.size());
    for (auto &tile: tiles) {
        tileAdapters.emplace_back(tile.get());
    }

    auto it = std::find_if(tiles.begin(), tiles.end(), [this](const auto &tile) {
        return tile->getXPos() == clickedTileCoords.first && tile->getYPos() == clickedTileCoords.second;
    });

    if (it == tiles.end()) {
        qDebug() << "Clicked tile not found in tile list";
        return;
    }

    Tile *destinationTile = it->get();

    Comparator <TileAdapter> comparator = [](const TileAdapter &a, const TileAdapter b) {
        return a.h > b.h;
    };

    // Create the PathFinder instance
    PathFinder <TileAdapter, Tile> pathFinder(
            tileAdapters, startTile, destinationTile, comparator,
            gameModel->getRows(), 1.0f);

    // Calculate the path
    std::vector<int> path = pathFinder.A_star();

    if (!path.empty()) {
        this->path = path; // Assign the calculated path to the member variable
        currentIndex = 0;
        connect(movementTimer, &QTimer::timeout, this, &ProtagonistController::moveNextStep);
        movementTimer->start(250); // Adjust as needed
        isClickMove = true;
    } else {
        qDebug() << "No path found for clickMove";
    }
}

void ProtagonistController::handleTileClick(int x, int y) {
    if (isAutoPlaying) {
        stopAutoPlay();
    }
    setClickedTile(x, y);
    clickMove();
}

void ProtagonistController::stopAutoPlay() {
    if (isAutoPlaying) {
        movementTimer->stop();
        disconnect(movementTimer, nullptr, this, nullptr);
        currentIndex = 0;
        isAutoPlaying = false;
    }
}

void ProtagonistController::stopClickMove() {
    if (isClickMove) {
        movementTimer->stop();
        disconnect(movementTimer, nullptr, this, nullptr);
        currentIndex = 0;
        isClickMove = false;
    }
}

void ProtagonistController::autoPlay() {
    stopClickMove();

    const auto &tiles = gameModel->getTiles();
    if (!isProtagonistActive()) {
        qDebug() << "Protagonist is not active";
        return;
    }

    // Create TileAdapters for each Tile
    std::vector <TileAdapter> tileAdapters;
    tileAdapters.reserve(tiles.size());
    for (auto &tile: tiles) {
        tileAdapters.emplace_back(tile.get());
    }

    Tile *startTile = dynamic_cast<Tile *>(protagModel.get());
    Tile *destinationTile = findNearestObjective();

    if (!destinationTile) {
        qDebug() << "No destination objective found";
        return;
    }

    Comparator <TileAdapter> comparator = [](const TileAdapter &a, const TileAdapter b) {
        return a.h > b.h;
    };

    // Create the PathFinder instance
    PathFinder <TileAdapter, Tile> pathFinder(
            tileAdapters, startTile, destinationTile, comparator,
            gameModel->getRows(), 1.0f);

    // Calculate the path
    std::vector<int> path = pathFinder.A_star();

    if (!path.empty()) {
        this->path = path; // Assign the calculated path to the member variable
        currentIndex = 0;
        connect(movementTimer, &QTimer::timeout, this, &ProtagonistController::moveNextStep);
        movementTimer->start(250); // Adjust as needed
        isAutoPlaying = true;
    } else {
        qDebug() << "No path found for autoPlay";
    }
}

void ProtagonistController::moveNextStep() {
    if (currentIndex < path.size()) {
        handleStep(path[currentIndex]);
        qDebug() << "Next level in moveNextStep: " << nextLevel;

        if (nextLevel == false || nextLevel == 0) {
            updateProtagonistState(protagModel->getXPos(), protagModel->getYPos());
            emit tileVisited(protagModel->getXPos(), protagModel->getYPos());
            markedCoordinates.push_back(std::make_pair(protagModel->getXPos(), protagModel->getYPos()));
        }
        currentIndex++;
        // Emit signal to mark the tile as visited
    } else {
        movementTimer->stop();
        disconnect(movementTimer, nullptr, this, nullptr);
        currentIndex = 0;

        if (isAutoPlaying) {
            Tile *newDestination = findNearestObjective();
            if (newDestination) {
                autoPlay(); // Restart autoPlay with new objective
            } else {
                isAutoPlaying = false;
            }
        } else if (isClickMove) {
            isClickMove = false;
            qDebug() << "click move completed";
            for (auto &p: markedCoordinates)
                emit tileCleaned(p);
        }
    }
}

void ProtagonistController::handleBounce() {
    int direction = rand() % 4;
    int moveSuccess = 0;
    switch (direction) {
        case 0:
            moveUp();
            moveSuccess = moveUp();
            break;
        case 1:
            moveDown();
            moveSuccess = moveDown();
            break;
        case 2:
            moveLeft();
            moveSuccess = moveLeft();
            break;
        case 3:
            moveRight();
            moveSuccess = moveRight();
            break;
        default:
            qDebug() << "Invalid direction: " << direction;
            break;
    }
    if (moveSuccess == 0) {
        handleBounce();
    } else if (moveSuccess == 1) {
        qDebug() << "Moved to position" << protagModel->getXPos() << "," << protagModel->getYPos();
    }
}


/********************************************************************************
Handle typed commands or key presses
*********************************************************************************/
// Function to handle tab key presses
void ProtagonistController::handleTab(QString partialCommand) {
    QStringList matchingCommands;

    for (const QString &command: commandHandlers.keys()) {
        if (command.startsWith(partialCommand.trimmed(), Qt::CaseInsensitive)) {
            matchingCommands.append(command);
        }
    }

    // If there is exactly one matching command, emit a signal to complete the command
    if (matchingCommands.count() == 1) {
        emit commandToComplete(matchingCommands.first());
    }
}

// Function to handle typed commands
void ProtagonistController::handleCommand(QString command) {
    if (!isProtagonistActive()) {
        qDebug() << "Protagonist is not active";
        return;
    }
    command = command.toLower();

    // Check for "goto x,y" pattern
    if (command.startsWith("goto ")) {
        QStringList parts = command.mid(4).split(",");
        if (parts.size() == 2) {
            bool ok1, ok2;
            int x = parts[0].toInt(&ok1);
            int y = parts[1].toInt(&ok2);
            if (ok1 && ok2) {
                goTo(x, y);
                return;
            }
        }
    }

    // Execute the command if it exists in the commandHandlers map
    if (commandHandlers.contains(command)) {
        commandHandlers[command]();
    } else {
        qDebug() << "Unknown command:" << command;
    }
}

// Function to handle key presses
void ProtagonistController::handleKeyPress(int key) {
    if (!isProtagonistActive()) {
        qDebug() << "Protagonist is not active";
        return;
    }
    QMap<int, std::function<void()>> keyHandlers = {
            {Qt::Key_Left,  [this]() { moveLeft(); }},
            {Qt::Key_Right, [this]() { moveRight(); }},
            {Qt::Key_Up,    [this]() { moveUp(); }},
            {Qt::Key_Down,  [this]() { moveDown(); }}};

    // Check if the key is in the keyHandlers map and execute the corresponding movement function
    if (keyHandlers.contains(key))
        keyHandlers[key]();

    else
        qDebug() << "Unknown key pressed:" << key;
}

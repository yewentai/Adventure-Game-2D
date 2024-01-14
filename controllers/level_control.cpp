#include "level_control.h"
#include <QDebug>

LevelController::LevelController()
        : currentLevel{1}, MAXLEVEL{3}, currentIndex{1} {
    // Initialize the levels array
    levels[0] = nullptr;
    levels[1] = std::make_unique<GameModel>(QString(":/src/world_images/worldmap.png"), 5, 10, 0.25f, 50.0f);
    levels[2] = std::make_unique<GameModel>(QString(":/src/world_images/worldmap1.png"), 10, 8, 0.25f, 50.0f);

    // Connect models to gates
    connectModel();
}

int LevelController::getCurrentLevel() const {
    return currentLevel;
}

void LevelController::connectModel() {
    for (auto &model: levels) {
        if (model) {
            for (auto &g: model->getGates()) {
                if (g->getType()) // If it's a "next" gate
                {
                    qDebug() << "LevelUp connected to gate";
                    connect(g.get(), SIGNAL(levelUp()), this, SLOT(handleLevelUp()));
                } else {
                    // Connect the levelDown signal to the handleLevelDown slot
                    connect(g.get(), SIGNAL(levelDown()), this, SLOT(handleLevelDown()));
                }
            }
        }
    }
}

const std::unique_ptr <GameModel> &LevelController::getCurrentModel() {
    return levels.at(currentIndex);
}

const std::unique_ptr <GameModel> &LevelController::getModelByIndex(int index) {
    return levels.at(index);
}

int LevelController::getCurrentIndex() const {
    return currentIndex;
}

void LevelController::handleLevelUp() {
    if ((currentLevel < MAXLEVEL) && (currentLevel >= 1)) {
        qDebug() << "Handling LevelUp";
        // Increase the level
        currentLevel++;
        // Update the current Index
        currentIndex = currentLevel % 3;
        // put the new model to the nextIndex
        int nextIndex = (currentLevel + 1) % 3;
        int preIndex = (currentLevel - 1) % 3;
        switch (currentLevel) {
            case 2:
                // Strategy for level 2
                levels[nextIndex] = std::make_unique<GameModel>(QString(":/src/world_images/worldmap1.png"), 10, 8,
                                                                0.25f, 50.0f);
                connectModel();
                qDebug() << "Current level:" << currentLevel;
                qDebug() << "Current Index:" << currentIndex;
                qDebug() << "Next Index:" << nextIndex;
                qDebug() << "Level 2 strategy selected.";
                emit levelUpdated(preIndex);
                break;
            case 3:
                // Strategy for level 3 (maximum level, no next level)
                // if (levels[nextIndex] != nullptr)
                // {
                //     levels[nextIndex] = nullptr;
                // }
                levels[nextIndex] = std::make_unique<GameModel>(QString(":/src/world_images/worldmap2.png"), 10, 8,
                                                                0.25f, 50.0f);
                connectModel();
                emit levelUpdated(preIndex);
                qDebug() << "Level 3 strategy selected.";
                break;
            default:
                // Default strategy for unknown levels
                qDebug() << "Unknown levels strategy selected.";
                break;
        }
    }
}

void LevelController::handleLevelDown() {
    qDebug() << "Handling LevelDown";
    if ((currentLevel <= MAXLEVEL) && (currentLevel > 1)) {
        // Decrease the level
        currentLevel--;
        // Update the current Index
        currentIndex = currentLevel % 3;
        int nextIndex = (currentLevel - 1) % 3;
        int preIndex = (currentLevel + 1) % 3;
        switch (currentLevel) {
            case 1:
                // Strategy for level 1 (minimum level, no previous level)
                if (levels[nextIndex] != nullptr) {
                    levels[nextIndex] = nullptr;
                }
                emit levelUpdated(preIndex);
                qDebug() << "Level 1 strategy selected.";
                break;
            case 2:
                // Strategy for level 2
                levels[nextIndex] = std::make_unique<GameModel>(QString(":/src/world_images/worldmap1.png"), 5, 10,
                                                                0.25f, 50.0f);
                connectModel();
                emit levelUpdated(preIndex);
                qDebug() << "Level 2 strategy selected.";
                break;
            default:
                // Default strategy for unknown levels
                qDebug() << "Unknown levels strategy selected.";
                break;
        }
    }
}

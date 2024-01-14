#include "game.h"
#include <algorithm> // for std::find_if
#include <cmath>
#include <random>

GameModel::GameModel(QString fileName, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio, float hp)
        : background{new QPixmap(fileName)} {
    World *world = new World();
    world->createWorld(fileName, nrOfEnemies, nrOfHealthpacks, pRatio);
    tiles = world->getTiles();
    // enemies = world->getEnemies();
    protag = std::make_unique<ProtagonistModel>();
    rows = world->getRows();
    cols = world->getCols();

    // Random number generator
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    // HealthPacks from Tile to HealthPack
    //  Convert the vector to a vector of unique pointers to the derived class

    for (auto &basePtr: world->getHealthPacks()) {
        // Use std::move to transfer ownership to the new vector
        std::unique_ptr <HealthPack> hpPtr = std::make_unique<HealthPack>(basePtr->getXPos(), basePtr->getYPos(), hp);
        healthPacks.emplace_back(std::move(hpPtr));
    }
    // PEnemys & XEnemys from Enemy to PEnemyModel & XEnemy
    // Define the proportion of enemies to be transformed into XEnemies
    const float proportionOfXEnemies = 0.20f; // 20% of enemies are XEnemies

    for (auto &enemy: world->getEnemies()) {
        if (dynamic_cast<PEnemy *>(enemy.get())) {
            std::unique_ptr <PEnemyModel> pePtr = std::make_unique<PEnemyModel>(enemy->getXPos(), enemy->getYPos(),
                                                                                enemy->getValue());
            enemies.emplace_back(std::move(pePtr));
        } else {
            // Randomly decide whether to transform this enemy into an XEnemy
            if (distribution(generator) < proportionOfXEnemies) {
                std::unique_ptr <XEnemy> xePtr = std::make_unique<XEnemy>(enemy->getXPos(), enemy->getYPos(),
                                                                          enemy->getValue());
                enemies.emplace_back(std::move(xePtr));
            } else {
                std::unique_ptr <Enemy> regularEnemyPtr = std::make_unique<Enemy>(enemy->getXPos(), enemy->getYPos(),
                                                                                  enemy->getValue());
                enemies.emplace_back(std::move(regularEnemyPtr));
            }
        }
    }

    //generate 2 Gates, levelup*1, leveldown*1
    gates.emplace_back(std::make_unique<Gate>(0, 0, false));
    //generate gate in unique position
    std::vector<bool> used(cols * rows);
    //mark all used pos
    for (auto &e: enemies) {
        used[e->getYPos() * cols + e->getXPos()] = true;
    }
    for (auto &hp: healthPacks) {
        used[hp->getYPos() * cols + hp->getXPos()] = true;
    }
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_x(0, cols - 1);
    std::uniform_int_distribution<int> uniform_y(0, rows - 1);
    bool isUnique = false;
    while (!isUnique) {
        int xPos = uniform_x(e1);
        int yPos = uniform_y(e1);
        if (background->toImage().pixelColor(xPos, yPos) == QColor(Qt::black))
            continue;
        auto gatePtr = std::make_unique<Gate>(xPos, yPos, true);
        if (xPos != 0 || yPos != 0) {
            if (used[yPos * cols + xPos] == false) {
                gates.push_back(std::move(gatePtr));
                used[yPos * cols + xPos] = true;
                isUnique = true;
            }
        }
    }
}

bool GameModel::isWall(int x, int y) {
    for (auto &t: tiles) {
        if (t->getXPos() == x && t->getYPos() == y) {
            if (t->getValue() == std::numeric_limits<float>::infinity()) {
                return true;
            }
            return false;
        }
    }
    return false;
}

std::vector<std::unique_ptr < Tile>>

::iterator GameModel::findTile(int x, int y) {
    auto it = std::find_if(tiles.begin(), tiles.end(),
                           [x, y](const auto &t) {
                               return t->getXPos() == x && t->getYPos() == y;
                           });

    return it;
}

std::vector<std::unique_ptr < Enemy>>

::iterator GameModel::findEnemy(int x, int y) {
    auto it = std::find_if(enemies.begin(), enemies.end(),
                           [x, y](const auto &e) {
                               return e->getXPos() == x && e->getYPos() == y;
                           });

    return it;
}

std::vector<std::unique_ptr < HealthPack>>

::iterator GameModel::findHealthPack(int x, int y) {
    auto it = std::find_if(healthPacks.begin(), healthPacks.end(),
                           [x, y](const auto &h) {
                               return h->getXPos() == x && h->getYPos() == y;
                           });

    return it;
}

std::vector<std::unique_ptr < Gate>>

::iterator GameModel::findGate(int x, int y) {
    auto it = std::find_if(gates.begin(), gates.end(),
                           [x, y](const auto &g) {
                               return g->getXPos() == x && g->getYPos() == y;
                           });

    return it;
}

float GameModel::findPoison(int x, int y) {
    float poisonLevel = 0.0f;

    for (auto &e: enemies) {
        PEnemyModel *pEnemy = dynamic_cast<PEnemyModel *>(e.get());
        if (pEnemy) {
            // Calculate the distance between the protagonist and the center of the poison
            int distX = std::abs(x - pEnemy->getXPos());
            int distY = std::abs(y - pEnemy->getYPos());
            int range = pEnemy->getPoisonRange();
            float level = pEnemy->getPoisonLevel();
            // Check if the protagonist is within the poison
            if (distX <= (range - 1) && distY <= (range - 1)) {
                if (level > poisonLevel) {
                    poisonLevel = level;
                }
            }
        }
    }

    return poisonLevel;
}

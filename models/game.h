#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include "models/healthpack.h"
#include "models/penemy.h"
#include "models/xenemy.h"
#include "models/protagonist.h"
#include "models/gate.h"
class GameModel
{
public:
    GameModel(QString fileName, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio = 0.25f, float hp = 100.0f);
    const std::vector<std::unique_ptr<Tile>> &getTiles() const { return tiles; };
    const std::vector<std::unique_ptr<Enemy>> &getEnemies() const { return enemies; };
    const std::vector<std::unique_ptr<HealthPack>> &getHealthPacks() const { return healthPacks; };
    const std::unique_ptr<ProtagonistModel> &getProtagonist() const { return protag; };
    const std::vector<std::unique_ptr<Gate>> & getGates() const {return gates;};
    int getRows() const { return rows; };
    int getCols() const { return cols; };
    QPixmap *getBackground() { return background; };

    bool isWall(int x, int y);
    std::vector<std::unique_ptr<Tile>>::iterator findTile(int x, int y);
    std::vector<std::unique_ptr<Enemy>>::iterator findEnemy(int x, int y);
    std::vector<std::unique_ptr<HealthPack>>::iterator findHealthPack(int x, int y);
    std::vector<std::unique_ptr<Gate>>::iterator findGate(int x,int y);
    float findPoison(int x, int y); // return the poisonLevel at this position

private:
    int rows, cols;
    QPixmap *background;
    std::unique_ptr<ProtagonistModel> protag;
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<HealthPack>> healthPacks;
    std::vector<std::unique_ptr<Gate>> gates;
};

#endif // GAME_H

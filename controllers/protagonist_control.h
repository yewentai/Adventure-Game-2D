#ifndef PROTAGONIST_CONTROL_H
#define PROTAGONIST_CONTROL_H

#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

#include "models/game.h"
#include "models/tileadapter.h"
#include "lib/pathfinder_class.h"
#include "lib/pathfinder_function.h"

class ProtagonistController : public QObject
{
    Q_OBJECT
public:
    ProtagonistController(GameModel *model, const std::unique_ptr<ProtagonistModel> &protag);
    int moveRight();
    int moveLeft();
    int moveUp();
    int moveDown();
    void goTo(int x, int y);
    void attackNearest();
    void healNearest();
    void handleStep(int step);
    void updateProtagonistState(int x, int y);
    Tile *findNearestObjective();
    void setClickedTile(int x, int y)
    {
        clickedTileCoords = std::make_pair(x, y);
    }

private:
    bool isAutoPlaying{false};
    bool isClickMove{false};
    bool autoPlayInterrupted = false;
    bool clickMoveActive{false};
    std::pair<int, int> clickedTileCoords{-1, -1};
    QTimer *movementTimer;
    QTimer *clickMoveTimer;

    void fight(std::unique_ptr<Enemy> &enemy);
    void heal(std::unique_ptr<HealthPack> &hp);
    void poisoned(float poisonLevel);
    void updateEP(float remainEP);
    void updateHP(float remainHP);
    bool isProtagonistActive()
    {

        if (protagModel->getHealth() > 0 && protagModel->getEnergy() > 0)
            return true;
        else
        {
            emit protagDead();
            return false;
        }
    };

    const std::unique_ptr<ProtagonistModel> &protagModel;
    GameModel *gameModel;
    QTimer *healthDecreaseTimer;
    int elapsed{0};                // Time elapsed
    const int totalTime{5000};     // Total time for poison effect
    const int timerInterval{1000}; // Interval for timer ticks (1 second)
    float poisonPerInterval{0.0f};
    QMap<QString, std::function<void()>> commandHandlers;
    unsigned long currentIndex{0};
    bool nextLevel{false};
    float difficulty_factor{0.5f};
    std::vector<int> path;
    //    std::vector<int,int> markedCoordinates;
    std::vector<std::pair<int, int>> markedCoordinates;
signals:
    void protagDead();
    void protagTired();
    void tileVisited(int x, int y);
    void tileCleaned(std::pair<int, int> coord);
    void commandToComplete(const QString &command);

public slots:
    void handleKeyPress(int key);
    void handleCommand(QString command);
    void autoPlay();
    void clickMove();
    void handleTab(QString command);
    void handlePoisoned();
    void handleBounce();
    void updateDifficulty(int value);
    void handleTileClick(int x, int y);
    void stopAutoPlay();
    void stopClickMove();
    void moveNextStep();
};

#endif // PROTAGONIST_CONTROL_H

#ifndef LEVELCONTROLLER_H
#define LEVELCONTROLLER_H

#include <QObject>
#include "models/game.h"

class LevelController : public QObject {
    Q_OBJECT
public:
    LevelController();

    int getCurrentLevel() const;

    void connectModel();

    const std::unique_ptr <GameModel> &getCurrentModel();

    const std::unique_ptr <GameModel> &getModelByIndex(int index);

    int getCurrentIndex() const;

private:
    std::array<std::unique_ptr<GameModel>, 3> levels;
    int currentIndex;
    int currentLevel;
    const int MAXLEVEL;
public
    slots:
            void handleLevelUp();

    void handleLevelDown();

    signals:
            void levelUpdated(int
    preIndex);
};

#endif // LEVELCONTROLLER_H

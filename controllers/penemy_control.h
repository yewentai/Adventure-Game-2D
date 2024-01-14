#ifndef PENEMY_CONTROL_H
#define PENEMY_CONTROL_H

#include <QObject>
#include "models/game.h"

class PEnemyController : public QObject
{
    Q_OBJECT
public:
    PEnemyController(PEnemyModel *pEnemy);

private:
    PEnemyModel *pEnemyModel;

public slots:
    void handleDead();
    void handlePoisonLevelUpdated(int value);

signals:
    void startPoison();
};

#endif // PENEMY_CONTROL_H

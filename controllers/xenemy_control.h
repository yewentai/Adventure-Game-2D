#ifndef XENEMY_CONTROL_H
#define XENEMY_CONTROL_H

#include <QObject>
#include "models/game.h"

class XEnemyController : public QObject {
    Q_OBJECT
public:
    XEnemyController(XEnemyModel *xEnemy);

private:
    XEnemyModel *xEnemyModel;

public
    slots:
            void handleDead();

    signals:
};

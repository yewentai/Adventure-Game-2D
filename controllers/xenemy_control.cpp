#include "xenemy_control.h"

XEnemyController::XEnemyController(XEnemyModel *xEnemy)
{
    xEnemyModel = xEnemy;
    connect(xEnemyModel, SIGNAL(dead()), this, SLOT(handleDead()));
}
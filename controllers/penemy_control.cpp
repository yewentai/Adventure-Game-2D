#include "penemy_control.h"

PEnemyController::PEnemyController(PEnemyModel *pEnemy) : pEnemyModel(pEnemy) {
    connect(pEnemyModel, SIGNAL(dead()), this, SLOT(handleDead()));
    connect(this, SIGNAL(startPoison()), pEnemyModel, SLOT(poison()));
    connect(pEnemyModel, SIGNAL(poisonLevelUpdated(int)), this, SLOT(handlePoisonLevelUpdated(int)));
}

void PEnemyController::handleDead() {
    if (pEnemyModel->getPoisonLevel() > 0.0f) {
        emit startPoison();
    } else {
        pEnemyModel->setPoisonRange(0); // no poison after dead
    }
}

void PEnemyController::handlePoisonLevelUpdated(int value) {
    pEnemyModel->addPoisonRange(1);
}

#include "penemy.h"

PEnemyModel::PEnemyModel(int xPosition, int yPosition, float strength)
        : PEnemy(xPosition, yPosition, strength) {
}

int PEnemyModel::getPoisonRange() const {
    return poisonRange;
}

void PEnemyModel::addPoisonRange(int value) {
    poisonRange += value;
    emit poisonUpdated(getPoisonRange(), getPoisonLevel());
}

void PEnemyModel::setPoisonRange(int newPoisonRange) {
    poisonRange = newPoisonRange;
}

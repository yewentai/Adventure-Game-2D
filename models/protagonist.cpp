#include "protagonist.h"

ProtagonistModel::ProtagonistModel()
        : Protagonist() {
}

bool ProtagonistModel::getIsPoisoned() const {
    return isPoisoned;
}

void ProtagonistModel::setIsPoisoned(bool newIsPoisoned) {
    isPoisoned = newIsPoisoned;

    if (newIsPoisoned) {
        emit protagPoisoned();
    } else {
        emit protagRecovered();
    }
}

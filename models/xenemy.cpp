#include "xenemy.h"

XEnemy::XEnemy(int xPosition, int yPosition, float strength) : Enemy(xPosition, yPosition, strength) {
}

void XEnemy::setBounceTimes(int value) {
    bounceTimes = value;
}

int XEnemy::getBounceTimes() const {
    return bounceTimes;
}

std::string XEnemy::serialize() {
    std::stringstream res;
    res << Enemy::serialize() << "," << bounceTimes;
    return res.str();
}

bool XEnemy::bounceProtagonist() {
    bounceTimes++;
    if (bounceTimes < 3) {
        emit bounce();
        return true;
    } else {
        setDefeated(true);
        emit dead();
    }
    return false;
}
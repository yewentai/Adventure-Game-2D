#ifndef XENEMYMODEL_H
#define XENEMYMODEL_H

#include <QObject>
#include <QtDebug>
#include <iostream>
#include <sstream>
#include "lib/world.h"

class XEnemy : public Enemy {
    Q_OBJECT

public:
    XEnemy(int xPosition, int yPosition, float strength);

    ~XEnemy() override = default;

    std::string serialize() override;

    void setBounceTimes(int value);

    int getBounceTimes() const;

private:
    int bounceTimes{0};

    signals:
            void bounce();

public
    slots:
            bool bounceProtagonist();
};

#endif // XENEMYMODEL_H
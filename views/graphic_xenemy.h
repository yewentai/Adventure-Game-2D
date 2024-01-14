#ifndef GRAPHIC_XENEMY_H
#define GRAPHIC_XENEMY_H

#include <QObject>
#include <QImage>
#include "views/graphic_enemy.h"

class XEnemyViewGraphic : public EnemyViewGraphic {
    Q_OBJECT

public:
    XEnemyViewGraphic(int size, int xPos, int yPos)
            : EnemyViewGraphic(size, xPos, yPos) {
        this->viewAlive = new QPixmap(QString(":/src/tile_images/x_alive.png"));
        this->viewDead = new QPixmap(QString(":/src/tile_images/x_dead.png"));
        this->setPixmap(viewAlive->scaled(size, size));
        this->setZValue(2);
    };

private:
};

#endif // GRAPHIC_XENEMY_H

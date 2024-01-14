#ifndef GRAPHIC_XENEMY_H
#define GRAPHIC_XENEMY_H

#include <QObject>
#include <QImage>
#include "views/graphic_enemy.h"

class XEnemyView2D : public EnemyView2D
{
    Q_OBJECT

public:
    XEnemyView2D(int size, int xPos, int yPos)
        : EnemyView2D(size, xPos, yPos)
    {
        this->viewAlive = new QPixmap(QString(":/src/tile_images/x_alive.png"));
        this->viewDead = new QPixmap(QString(":/src/tile_images/x_dead.png"));
        this->setPixmap(viewAlive->scaled(size, size));
        this->setZValue(2);
    };

private:
};
#endif // GRAPHIC_XENEMY_H

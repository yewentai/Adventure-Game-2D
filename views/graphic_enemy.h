#ifndef GRAPHIC_ENEMY_H
#define GRAPHIC_ENEMY_H

#include <QObject>
#include <QImage>
#include "views/graphic_tile.h"

class EnemyViewGraphic : public TileViewGraphic {
    Q_OBJECT

public:
    // Constructor for the EnemyViewGraphic class
    EnemyViewGraphic(int size, int xPos, int yPos) : TileViewGraphic(size, xPos, yPos) {
        this->viewAlive = new QPixmap(QString(":/src/tile_images/enemy.png"));
        this->viewDead = new QPixmap(QString(":/src/tile_images/enemy_dead.png"));
        this->setPixmap(viewAlive->scaled(size, size));
        this->setZValue(2);
    };

    // Destructor for the EnemyViewGraphic class
    ~EnemyViewGraphic() {
        delete viewAlive;
        delete viewDead;
    };

protected:
    bool dead{false};   // Flag to track if the enemy is dead
    QPixmap *viewAlive; // Pixmap for the alive enemy view
    QPixmap *viewDead;  // Pixmap for the dead enemy view

public
    slots:

    // Handle the event when the enemy is defeated
    inline void handleDead() {
        dead = true;
        this->setPixmap(viewDead->scaled(size, size));
    }
};

#endif // GRAPHIC_ENEMY_H

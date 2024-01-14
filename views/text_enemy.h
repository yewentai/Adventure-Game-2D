#ifndef TEXT_ENEMY_H
#define TEXT_ENEMY_H

#include <QObject>
#include "views/text_tile.h"

class EnemyViewText : public TileViewText
{
    Q_OBJECT

public:
    // Constructor for the EnemyViewText class
    EnemyViewText(int size, int xPos, int yPos) : TileViewText(size, xPos, yPos)
    {
        this->setPlainText(QString("E"));
        this->setZValue(2);
    };

    // Set the status of the enemy (alive or dead)
    void setIsDead(bool newIsDead);

public slots:
    // Handle the event when the enemy is defeated
    inline void handleDead()
    {
        dead = true;
        this->setPlainText(QString(" "));
    };

protected:
    bool dead{false}; // Flag to track if the enemy is dead
};

#endif // TEXT_ENEMY_H

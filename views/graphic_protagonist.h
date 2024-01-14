#ifndef GRAPHIC_PROTAGONIST_H
#define GRAPHIC_PROTAGONIST_H

#include <QPropertyAnimation>
#include <QImage>
#include "views/graphic_tile.h"
#include "views/graphic_poison.h"

class ProtagonistView2D : public TileView2D {
    Q_OBJECT

public:
    // Constructor for the ProtagonistView2D class
    ProtagonistView2D(int size, int xPos, int yPos);

    // Destructor for the ProtagonistView2D class
    ~ProtagonistView2D() { delete viewAlive; };

private:
    bool dead{false};   // Flag to track if the protagonist is dead
    QPixmap *viewAlive; // Pixmap for the alive protagonist view
    PoisonView2D *viewPoisoned;
    QPropertyAnimation *poisonedAnimationX;
    QPropertyAnimation *poisonedAnimationY;

public
    slots:
            // Handle position changes for the protagonist
            void handlePosChanged(int
    x,
    int y
    );

    void handlePoioned();

    void handleRecovered();
};

#endif // GRAPHIC_PROTAGONIST_H

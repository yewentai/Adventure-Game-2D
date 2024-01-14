#ifndef TEXT_PROTAGONIST_H
#define TEXT_PROTAGONIST_H

#include "views/text_tile.h"

class ProtagonistViewText : public TileViewText {
    Q_OBJECT

public:
    // Constructor for the ProtagonistViewText class
    ProtagonistViewText(int size, int xPos, int yPos)
            : TileViewText(size, xPos, yPos) {
        this->setPlainText(QString("@")); // Set the pixmap for the protagonist view
        this->setPos(xPos * size, yPos * size);
    };

private:
    bool dead{false}; // Flag to track if the protagonist is dead

public
    slots:
            // Handle position changes for the protagonist
            void handlePosChanged(int
    x,
    int y
    )
    {
        this->setPos(x * size, y * size);
    }
};

#endif // TEXT_PROTAGONIST_H

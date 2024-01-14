#ifndef GRAPHIC_GATE_H
#define GRAPHIC_GATE_H

#include <QImage>
#include "views/graphic_tile.h"

class GateView2D : public TileView2D {

public:
    // Constructor for the HealthPackView2D class
    GateView2D(int size, int xPos, int yPos)
            : TileView2D(size, xPos, yPos) {
        // Set the pixmap and Z-value for the health pack view
        QPixmap resizedPixmap = (new QPixmap(QString(":/src/tile_images/gate.png")))->scaled(size, size);
        this->setPixmap(resizedPixmap);
        this->setZValue(2); // Set the Z-value for layering
    };

private:

};

#endif // GRAPHIC_GATE_H

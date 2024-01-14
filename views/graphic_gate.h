#ifndef GRAPHIC_GATE_H
#define GRAPHIC_GATE_H

#include <QImage>
#include "views/graphic_tile.h"

class GateViewGraphic : public TileViewGraphic {

public:
    // Constructor for the HealthPackViewGraphic class
    GateViewGraphic(int size, int xPos, int yPos)
            : TileViewGraphic(size, xPos, yPos) {
        // Set the pixmap and Z-value for the health pack view
        QPixmap resizedPixmap = (new QPixmap(QString(":/src/tile_images/gate.png")))->scaled(size, size);
        this->setPixmap(resizedPixmap);
        this->setZValue(2); // Set the Z-value for layering
    };

private:

};

#endif // GRAPHIC_GATE_H

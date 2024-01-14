#ifndef GRAPHIC_HEALTHPACK_H
#define GRAPHIC_HEALTHPACK_H

#include <QObject>
#include <QImage>
#include "views/graphic_tile.h"

class HealthPackViewGraphic : public TileViewGraphic {
    Q_OBJECT

public:
    // Constructor for the HealthPackViewGraphic class
    HealthPackViewGraphic(int size, int xPos, int yPos)
            : TileViewGraphic(size, xPos, yPos) {
        // Set the pixmap and Z-value for the health pack view
        QPixmap resizedPixmap = (new QPixmap(QString(":/src/tile_images/heal.png")))->scaled(size, size);
        this->setPixmap(resizedPixmap);
        this->setZValue(2); // Set the Z-value for layering
    };

private:
public
    slots:
            // Handle the event when the health pack is picked up
            void handlePicked();
};

// Implementation of the handlePicked slot
inline void HealthPackViewGraphic::handlePicked() {
    this->deleteLater(); // Delete the health pack view after it's picked up
}

#endif // GRAPHIC_HEALTHPACK_H

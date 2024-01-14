#ifndef GRAPHIC_TILE_H
#define GRAPHIC_TILE_H

#include <QGraphicsPixmapItem>

class TileView2D : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    // Constructor for the TileView2D class
    TileView2D(int size, int xPos, int yPos)
            : size(size),
              xPos(xPos),
              yPos(yPos) {
        // Set the position offset based on the tile size and coordinates
        this->setPos(xPos * size, yPos * size);
    };

protected:
    int size{1}; // Size of the tile
    int xPos{0}; // X position of the tile
    int yPos{0}; // Y position of the tile
};

#endif // GRAPHIC_TILE_H

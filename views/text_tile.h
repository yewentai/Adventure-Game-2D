#ifndef TEXT_TILE_H
#define TEXT_TILE_H

#include <QObject>
#include <QGraphicsTextItem>

class TileViewText : public QGraphicsTextItem
{
    Q_OBJECT

public:
    // Constructor for the TileViewText class
    TileViewText(int size, int xPos, int yPos)
        : size(size),
          xPos(xPos),
          yPos(yPos)
    {
        // Set the position offset based on the tile size and coordinates
        this->setPos(xPos * size, yPos * size);
    };

protected:
    int size{1}; // Size of the tile
    int xPos{0}; // X position of the tile
    int yPos{0}; // Y position of the tile
};

#endif // TEXT_TILE_H

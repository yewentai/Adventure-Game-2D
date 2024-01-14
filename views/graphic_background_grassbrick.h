#ifndef GRAPHIC_BACKGROUND_GRASSBRICK_H
#define GRAPHIC_BACKGROUND_GRASSBRICK_H

#include <QObject>
#include <QImage>
#include "views/graphic_tile.h"

class GrassbrickView2D : public TileView2D
{
    Q_OBJECT

public:
    GrassbrickView2D(int size, int xPos, int yPos)
        : TileView2D(size, xPos, yPos)
    {
        QPixmap resizedPixmap = (new QPixmap(QString(":/src/tile_images/grassbrick.png")))->scaled(size, size);
        this->setPixmap(resizedPixmap);
        this->setZValue(1);
    };

private:
public slots:
};

#endif // GRAPHIC_BACKGROUND_GRASSBRICK_H

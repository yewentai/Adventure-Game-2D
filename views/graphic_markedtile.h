#ifndef GRAPHIC_MARKEDTILE_H
#define GRAPHIC_MARKEDTILE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScale>
#include "views/graphic_tile.h"

class MarkedTileView2D : public TileView2D
{
    Q_OBJECT

public:
    MarkedTileView2D(int size, int xPos, int yPos, QObject *parent = nullptr)
        : TileView2D(size, xPos, yPos)
    {
        this->setParent(parent);
        this->setPixmap(QPixmap(":/src/tile_images/marked.png").scaled(size, size)); // Path to the marked tile image
        this->setZValue(4);                                                          // Ensure it's rendered above the base tile

        // Initialize the scale transformation
        scaleTransform = new QGraphicsScale(this);
        // Set the origin to the center for scaling
        QPointF originPoint(this->pixmap().width() / 2, this->pixmap().height() / 2);
        scaleTransform->setOrigin(QVector3D(originPoint.x(), originPoint.y(), 0));

        this->setTransformations(QList<QGraphicsTransform *>() << scaleTransform);
    }

    QGraphicsScale *getScaleTransform() const;

private:
    QGraphicsScale *scaleTransform;
};

#endif // GRAPHIC_MARKEDTILE_H

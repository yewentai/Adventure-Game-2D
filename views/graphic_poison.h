#ifndef GRAPHIC_POISON_H
#define GRAPHIC_POISON_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScale>
#include "views/graphic_tile.h"

class PoisonView2D : public TileView2D {
    Q_OBJECT

public:
    PoisonView2D(int size, int xPos, int yPos, QObject *parent = nullptr)
            : TileView2D(size, xPos, yPos) {
        this->setParent(parent);
        this->setPixmap(QPixmap(":/src/tile_images/poisoned.png").scaled(size, size));
        this->setZValue(4);

        // Initialize the scale transformation
        scaleTransform = new QGraphicsScale(this);
        // Set the origin to the bottom-left corner
        QPointF originPoint(0, this->pixmap().height());
        scaleTransform->setOrigin(QVector3D(originPoint.x(), originPoint.y(), 0));

        this->setTransformations(QList<QGraphicsTransform *>() << scaleTransform);
    }

    QGraphicsScale *getScaleTransform() const;

private:
    QGraphicsScale *scaleTransform;
};

inline QGraphicsScale *PoisonView2D::getScaleTransform() const {
    return scaleTransform;
}

#endif // GRAPHIC_POISON_H

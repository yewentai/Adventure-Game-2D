#ifndef TEXT_POISON_H
#define TEXT_POISON_H
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScale>
#include "views/text_tile.h"

class TextPoison : public TileViewText
{
    Q_OBJECT

public:
    TextPoison(int size, int xPos, int yPos, QObject *parent = nullptr)
        : TileViewText(size, xPos, yPos)
    {
        this->setParent(parent);
        this->setPlainText(QString("X_X"));  // 'P' for poison
        this->setZValue(4);

        // Initialize the scale transformation
        scaleTransform = new QGraphicsScale(this);
        // Set the origin to the bottom-left corner
        QPointF originPoint(0, 0);
        scaleTransform->setOrigin(QVector3D(originPoint.x(), originPoint.y(), 0));

        this->setTransformations(QList<QGraphicsTransform *>() << scaleTransform);
    }

    QGraphicsScale *getScaleTransform() const;

private:
    QGraphicsScale *scaleTransform;
};

inline QGraphicsScale *TextPoison::getScaleTransform() const
{
    return scaleTransform;
}

#endif // TEXT_POISON_H


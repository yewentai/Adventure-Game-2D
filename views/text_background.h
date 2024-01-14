#ifndef TEXT_BACKGROUND_H
#define TEXT_BACKGROUND_H

#include "models/game.h"

class GrassworldViewText
{

public:
    GrassworldViewText(const std::vector<std::unique_ptr<Tile>> &tiles, int size, QGraphicsScene *scene)
        : size(size)
    {
        for (const auto &t : tiles)
        {
            QGraphicsTextItem *tileView;
            if (t->getValue() == std::numeric_limits<float>::infinity())
            {
                tileView = new QGraphicsTextItem(QString("|"));
                tileView->setPos(t->getXPos() * size, t->getYPos() * size);
                tileView->setDefaultTextColor(Qt::gray);
            }
            else if (t->getValue() > 0.6f)
            {
                tileView = new QGraphicsTextItem(QString("."));
                tileView->setPos(t->getXPos() * size, t->getYPos() * size);
                tileView->setDefaultTextColor(Qt::yellow);
            }
            else if (t->getValue() > 0.3f)
            {
                tileView = new QGraphicsTextItem(QString("."));
                tileView->setPos(t->getXPos() * size, t->getYPos() * size);
                tileView->setDefaultTextColor(Qt::green);
            }
            else if (t->getValue() > 0.2f)
            {
                tileView = new QGraphicsTextItem(QString("_"));
                tileView->setPos(t->getXPos() * size, t->getYPos() * size);
                tileView->setDefaultTextColor(Qt::darkGreen);
            }
            else if (t->getValue() > 0.12f)
            {
                tileView = new QGraphicsTextItem(QString("_"));
                tileView->setPos(t->getXPos() * size, t->getYPos() * size);
                tileView->setDefaultTextColor(Qt::blue);
            }
            else
            {
                tileView = new QGraphicsTextItem(QString("_"));
                tileView->setPos(t->getXPos() * size, t->getYPos() * size);
                tileView->setDefaultTextColor(Qt::cyan);
            }
            scene->addItem(tileView);
        }
    };

private:
    int size;
public slots:
};

#endif // TEXT_BACKGROUND_H

#include "text_penemy.h"

PEnemyViewText::PEnemyViewText(int size, int xPos, int yPos, int cols, int rows)
    : EnemyView2D(size, xPos, yPos), viewPoison(new ), cols(cols), rows(rows)
{
    this->viewAlive = new QPixmap(QString(":/src/tile_images/p_alive.png"));
    this->viewDead = new QPixmap(QString(":/src/tile_images/p_dead.png"));

    this->setPixmap(viewAlive->scaled(size, size));
    this->setZValue(3);
    poisons = new QGraphicsItemGroup();
    poisons->setZValue(2);
    // poisons->setPos(xPos*size,yPos*size);
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void  PEnemyViewText::handlePoisonUpdated(int range, float poisonLevel)
{
    // timer(animation) start or keep
    // poison color change according to value

    // poison range change according to value
    clearPoisons();
    // paint poison pixmap and store in one pixmap

    int xStart = max(0, xPos - range / 2);
    int xEnd = min(cols - 1, xPos + range / 2);
    int yStart = max(0, yPos - range / 2);
    int yEnd = min(rows - 1, yPos + range / 2);
    int height = viewPoison->height(); // Height of the original pixmap
    int widthToCopy = height;          // Width of the frame you want to select
    // Create a new pixmap to hold the concatenated images
    for (int k = 0; k < 4; k++)
    {
        QPixmap *pTempPix = new QPixmap((xEnd - xStart + 1) * height, (yEnd - yStart + 1) * height); // Set width and height as needed
        // Create a QPainter to paint on the concatenated pixmap
        QPainter painter(pTempPix);

        for (int i = xStart; i <= xEnd; i++)
        {
            for (int j = yStart; j <= yEnd; j++)
            {
                // if(i != xPos || j != yPos)
                // {
                //     painter.drawPixmap((i-xStart)*height, (j-yStart)*height,widthToCopy,widthToCopy,viewPoison->copy(k*widthToCopy, 0, height, height));
                // }
                painter.drawPixmap((i - xStart) * height, (j - yStart) * height, widthToCopy, widthToCopy, viewPoison->copy(k * widthToCopy, 0, height, height));
            }
        }

        // End painting
        painter.end();
        QGraphicsPixmapItem *pTempItem = new QGraphicsPixmapItem();
        pTempItem->setPixmap(pTempPix->scaled((xEnd - xStart + 1) * size, (yEnd - yStart + 1) * size));

        // Create opacity effect
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        pTempItem->setGraphicsEffect(opacityEffect);

        // Set the initial opacity to 0 (completely transparent)
        // opacityEffect->setOpacity(1);

        // Create opacity animation
        QPropertyAnimation *opacityAnimation = new QPropertyAnimation(opacityEffect, "opacity");
        opacityAnimation->setDuration(1000);                           // Set the duration of the animation in milliseconds
        opacityAnimation->setStartValue(poisonLevel / 100.0f);         // Start with full transparency
        opacityAnimation->setEndValue((poisonLevel - 10.0f) / 100.0f); // End with full opacity

        // Start the opacity animation
        opacityAnimation->start();

        // Set the position and add the item to the group
        pTempItem->setPos((xStart)*size, (yStart)*size);
        pTempItem->setVisible(true);
        poisons->addToGroup(pTempItem);
    }
}

QGraphicsItemGroup * PEnemyViewText::getPoisons() const
{
    return poisons;
}

void  PEnemyViewText::clearPoisons()
{
    if (poisons)
    {
        QList<QGraphicsItem *> itemsInGroup = poisons->childItems();

        for (QGraphicsItem *item : itemsInGroup)
        {
            // Remove the item from the group
            poisons->removeFromGroup(item);
            // Optionally, delete the item if it's no longer needed
            delete item;
        }

        // Additionally, you can clear the entire group from the scene
        // poisons->scene()->removeItem(poisons);
    }
}

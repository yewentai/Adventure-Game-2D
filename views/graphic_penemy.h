#ifndef GRAPHIC_PENEMY_H
#define GRAPHIC_PENEMY_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "views/graphic_enemy.h"

class PEnemyViewGraphic : public EnemyViewGraphic {
    Q_OBJECT

public:
    PEnemyViewGraphic(int size, int xPos, int yPos, int cols, int rows);

    QGraphicsItemGroup *getPoisons() const;

    void clearPoisons();

private:
    QPixmap *viewPoison;
    QGraphicsItemGroup *poisons;
    int poisonIndex{0};
    float poisonOpacity{1.0f};
    int cols;
    int rows;

public
    slots:
            void handlePoisonUpdated(int
    range,
    float poisonLevel
    );
};

#endif // GRAPHIC_PENEMY_H

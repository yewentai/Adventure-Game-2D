#ifndef TEXT_PENEMY_H
#define TEXT_PENEMY_H

#include <QObject>
#include <QImage>
#include "views/text_enemy.h"

class PEnemyViewText : public EnemyViewText {
    Q_OBJECT

public:
    PEnemyViewText(int size, int xPos, int yPos)
            : EnemyViewText(size, xPos, yPos) {
        this->setPlainText(QString("P"));
        this->setZValue(2);
    };

private:
    QGraphicsTextItem *viewPoison;
    int poisonIndex{0};
    int poisonRange{3};

public
    slots:

    inline void handlePoisonLevelUpdated(int value) {};
};

#endif // TEXT_PENEMY_H

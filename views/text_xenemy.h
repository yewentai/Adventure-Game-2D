#ifndef TEXT_XENEMY_H
#define TEXT_XENEMY_H

#include <QObject>
#include <QImage>
#include "views/text_enemy.h"

class XEnemyViewText : public EnemyViewText
{
    Q_OBJECT

public:
    XEnemyViewText(int size, int xPos, int yPos)
        : EnemyViewText(size, xPos, yPos)
    {
        this->setPlainText(QString("B"));
        this->setZValue(2);
    };

private:
};
#endif // TEXT_XENEMY_H

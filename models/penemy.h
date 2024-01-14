#ifndef PENEMYMODEL_H
#define PENEMYMODEL_H

#include <QObject>
#include "lib/world.h"

class PEnemyModel : public PEnemy
{
    Q_OBJECT

public:
    PEnemyModel(int xPosition, int yPosition, float strength);

    int getPoisonRange() const;
    void addPoisonRange(int value);

    void setPoisonRange(int newPoisonRange);

private:
    int poisonRange{1};

signals:
    void poisonUpdated(int range, float poisonLevel);
};

#endif // PENEMYMODEL_H

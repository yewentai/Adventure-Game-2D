#ifndef GATE_H
#define GATE_H

#include <QObject>
#include "lib/world.h"

class Gate : public QObject, public Tile
{
    Q_OBJECT
public:
    Gate(int xPosition, int yPosition, bool gateType, float strength = 0.0f);
    bool getType() const;
    void updateLevel();

private:
    bool gateType; //0: return to previous level; 1: next level
public slots:

signals:
    void levelUp();
    void levelDown();

};

#endif // GATE_H

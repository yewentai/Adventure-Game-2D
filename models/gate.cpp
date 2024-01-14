#include "gate.h"

Gate::Gate(int xPosition, int yPosition, bool gateType, float strength)
    : Tile(xPosition, yPosition, strength), gateType{gateType}
{}

bool Gate::getType() const
{
    return gateType;
}

void Gate::updateLevel()
{
    if(gateType)
    {
        emit levelUp();
    }else
    {
        emit levelDown();
    }
}

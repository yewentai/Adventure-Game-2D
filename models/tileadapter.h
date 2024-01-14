#ifndef TILEADAPTER_H
#define TILEADAPTER_H

#include <iostream>
#include "lib/world.h"

class TileAdapter {
public:
    Tile *tile; // Reference to the actual Tile
    float f, g, h;
    bool visited;
    TileAdapter *prev;

    TileAdapter(Tile *t) : tile(t), f(0.0f), g(0.0f), h(0.0f), visited(false), prev(nullptr) {}

    // Delegate methods to the Tile
    int getXPos() const { return tile->getXPos(); }

    int getYPos() const { return tile->getYPos(); }

    float getValue() const { return tile->getValue(); }
};

#endif // TILEADAPTER_H

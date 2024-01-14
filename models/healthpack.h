#ifndef HEALTHPACK_H
#define HEALTHPACK_H

#include <sstream>
#include "lib/world.h"

class HealthPack : public QObject, public Tile
{
    Q_OBJECT
public:
    // Constructor for the HealthPack class
    HealthPack(int xPosition, int yPosition, float strength = 30.0f)
        : Tile(xPosition, yPosition, strength),
          hp{strength} {};

    // Destructor for the HealthPack class
    ~HealthPack() override = default;

    // Get the health points of the health pack
    float getHP() const { return hp; }

    // Set the health points of the health pack and emit a signal if HP is <= 0
    void setHP(float hp)
    {
        this->hp = hp;
        if (hp <= 0.0f)
            emit hpPicked();
    }

    // Serialize the HealthPack object to a string
    std::string serialize() override;

private:
    float hp{0.0f}; // Health points of the health pack

signals:
    void hpPicked(); // Signal emitted when the health pack is picked up

public slots:
};

#endif // HEALTHPACK_H

// Implementation of the serialize function
inline std::string HealthPack::serialize()
{
    std::stringstream res;
    res << Tile::serialize() << "," << hp;
    return res.str();
}

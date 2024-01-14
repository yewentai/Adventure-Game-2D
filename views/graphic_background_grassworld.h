#ifndef GRAPHIC_BACKGROUND_GRASSWORLD_H
#define GRAPHIC_BACKGROUND_GRASSWORLD_H

#include "models/game.h"
#include "graphic_background_grassbrick.h"
#include "graphic_background_grassflower.h"
#include "graphic_background_lightgrass.h"
#include "graphic_background_brick.h"
#include "graphic_background_yellowgrass.h"
#include "graphic_background_pool.h"
#include "graphic_background_road.h"
#include "graphic_background_greengrass.h"

class GrassworldViewGraphic {

public:
    GrassworldViewGraphic(const std::vector <std::unique_ptr<Tile>> &tiles, int size, QGraphicsScene *scene)
            : size(size) {
        for (const auto &t: tiles) {
            if (t->getValue() == std::numeric_limits<float>::infinity()) {
                BrickViewGraphic *brickView = new BrickViewGraphic(size, t->getXPos(), t->getYPos());
                scene->addItem(brickView);
            } else if (t->getValue() > 0.65f) {
                RoadViewGraphic *roadView = new RoadViewGraphic(size, t->getXPos(), t->getYPos());
                scene->addItem(roadView);
            } else if (t->getValue() > 0.6f) {
                GrassflowerViewGraphic *grassflowerView = new GrassflowerViewGraphic(size, t->getXPos(), t->getYPos());
                scene->addItem(grassflowerView);
            } else if (t->getValue() > 0.3f) {
                YellowgrassViewGraphic *yellowgrassView = new YellowgrassViewGraphic(size, t->getXPos(), t->getYPos());
                scene->addItem(yellowgrassView);
            } else if (t->getValue() > 0.2f) {
                GreengrassViewGraphic *greengrassView = new GreengrassViewGraphic(size, t->getXPos(), t->getYPos());
                scene->addItem(greengrassView);
            } else if (t->getValue() > 0.12f) {
                LightgrassViewGraphic *lightgrassView = new LightgrassViewGraphic(size, t->getXPos(), t->getYPos());
                scene->addItem(lightgrassView);
            } else {
                PoolViewGraphic *poolView = new PoolViewGraphic(size, t->getXPos(), t->getYPos());
                scene->addItem(poolView);
            }
        }
    };

    ~GrassworldViewGraphic() {};

private:
    int size;
public
    slots:
};

#endif // GRAPHIC_BACKGROUND_GRASSWORLD_H

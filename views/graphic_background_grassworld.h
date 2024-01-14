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

class GrassworldView2D
{

public:
    GrassworldView2D(const std::vector<std::unique_ptr<Tile>> &tiles, int size, QGraphicsScene *scene)
        : size(size)
    {
        for (const auto &t : tiles)
        {
            if (t->getValue() == std::numeric_limits<float>::infinity())
            {
                BrickView2D *brickView = new BrickView2D(size, t->getXPos(), t->getYPos());
                scene->addItem(brickView);
            }
            else if (t->getValue() > 0.65f)
            {
                RoadView2D *roadView = new RoadView2D(size, t->getXPos(), t->getYPos());
                scene->addItem(roadView);
            }
            else if (t->getValue() > 0.6f)
            {
                GrassflowerView2D *grassflowerView = new GrassflowerView2D(size, t->getXPos(), t->getYPos());
                scene->addItem(grassflowerView);
            }
            else if (t->getValue() > 0.3f)
            {
                YellowgrassView2D *yellowgrassView = new YellowgrassView2D(size, t->getXPos(), t->getYPos());
                scene->addItem(yellowgrassView);
            }
            else if (t->getValue() > 0.2f)
            {
                GreengrassView2D *greengrassView = new GreengrassView2D(size, t->getXPos(), t->getYPos());
                scene->addItem(greengrassView);
            }
            else if (t->getValue() > 0.12f)
            {
                LightgrassView2D *lightgrassView = new LightgrassView2D(size, t->getXPos(), t->getYPos());
                scene->addItem(lightgrassView);
            }
            else
            {
                PoolView2D *poolView = new PoolView2D(size, t->getXPos(), t->getYPos());
                scene->addItem(poolView);
            }
        }
    };
    ~GrassworldView2D(){};

private:
    int size;
public slots:
};

#endif // GRAPHIC_BACKGROUND_GRASSWORLD_H

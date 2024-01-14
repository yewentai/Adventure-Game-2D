#include "graphic.h"

ViewGraphic::ViewGraphic(GameModel *model, int size, int bgSkin) : size(size) {
    // Initialize the scene and add it to the view
    scene = new QGraphicsScene();
    this->setScene(scene);

    const std::vector <std::unique_ptr<Tile>> &tiles = model->getTiles();
    const std::unique_ptr <ProtagonistModel> &protag = model->getProtagonist();
    const std::vector <std::unique_ptr<Enemy>> &enemies = model->getEnemies();
    const std::vector <std::unique_ptr<HealthPack>> &hps = model->getHealthPacks();

    // Set the default size of the view.
    this->setFixedSize(size * model->getCols() + 2, size * model->getRows() + 2);

    // Construct views according to the tile model and connect

    // Construct a background view for the model and connect
    if (bgSkin == 1) {
        new GrassworldViewGraphic(tiles, size, scene);
    } else {
        new GrassworldViewGraphic(tiles, size, scene);
    }

    // Construct controllers for the model and connect
    ProtagonistViewGraphic *pView = new ProtagonistViewGraphic(size, protag->getXPos(), protag->getYPos());
    scene->addItem(pView);
    connect(protag.get(), SIGNAL(posChanged(int, int)), pView, SLOT(handlePosChanged(int, int)));
    connect(protag.get(), SIGNAL(protagPoisoned()), pView, SLOT(handlePoioned()));
    connect(protag.get(), SIGNAL(protagRecovered()), pView, SLOT(handleRecovered()));

    for (const auto &e: enemies) {
        // Generate the views of tiles according to the tile type
        if (dynamic_cast<PEnemyModel *>(e.get())) {
            PEnemyViewGraphic *pView = new PEnemyViewGraphic(size, e->getXPos(), e->getYPos(), model->getCols(),
                                                   model->getRows());
            scene->addItem(pView);
            scene->addItem(pView->getPoisons());
            // pView->drawPoison(model->getCols(),model->getRows());
            connect(e.get(), SIGNAL(dead()), pView, SLOT(handleDead()));
            connect(e.get(), SIGNAL(poisonUpdated(int, float)), pView, SLOT(handlePoisonUpdated(int, float)));
        } else if (dynamic_cast<XEnemy *>(e.get())) {
            XEnemyViewGraphic *xView = new XEnemyViewGraphic(size, e->getXPos(), e->getYPos());
            scene->addItem(xView);
            connect(e.get(), SIGNAL(dead()), xView, SLOT(handleDead()));
        } else {
            EnemyViewGraphic *eView = new EnemyViewGraphic(size, e->getXPos(), e->getYPos());
            scene->addItem(eView);
            connect(e.get(), SIGNAL(dead()), eView, SLOT(handleDead()));
        }
    }
    for (const auto &h: hps) {
        HealthPackViewGraphic *hView = new HealthPackViewGraphic(size, h->getXPos(), h->getYPos());
        scene->addItem(hView);
        connect(h.get(), SIGNAL(hpPicked()), hView, SLOT(handlePicked()));
    }
    for (const auto &g: model->getGates()) {
        GateViewGraphic *gView = new GateViewGraphic(size, g->getXPos(), g->getYPos());
        scene->addItem(gView);
    }
}

QGraphicsScene *ViewGraphic::getScene() const {
    return scene;
}

void ViewGraphic::mousePressEvent(QMouseEvent *event) {
    int x = event->x() / size; // Convert mouse coordinates to tile coordinates
    int y = event->y() / size;
    qDebug() << "Emitting coordinates x and y: " << x << " " << y;
    emit tileClicked(x, y); // Emit the signal
    QGraphicsView::mousePressEvent(event);
}

int ViewGraphic::getTileSize() const {
    return size;
}

void ViewGraphic::keyPressEvent(QKeyEvent *event) {
    // Emit a signal with key information
    emit keyPressed(event->key());
}

void ViewGraphic::wheelEvent(QWheelEvent *event) {
    // Zoom
    const ViewportAnchor anchor = transformationAnchor();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    int angle = event->angleDelta().y();
    qreal factor;
    if (angle > 0 && zoomFactor <= 5.0f) {
        factor = 1.03;
    } else if (angle < 0) {
        factor = 0.97;
        if (zoomFactor * factor < 1.0f) {
            factor = 1.0f / zoomFactor;
        }
    } else {
        return;
    }
    zoomFactor *= factor;
    scale(factor, factor);
    setTransformationAnchor(anchor);
}

void ViewGraphic::cleanupMarkedTiles() {
    QList < QGraphicsItem * > itemsToRemove;

    for (QGraphicsItem *item: scene->items()) {
        // Check if the item is a MarkedTileViewGraphic
        MarkedTileViewGraphic *markedTile = dynamic_cast<MarkedTileViewGraphic *>(item);
        if (markedTile) {
            // Add to the list for removal
            itemsToRemove.append(item);
        }
    }

    // Remove and delete the marked tiles
    for (QGraphicsItem *item: itemsToRemove) {
        scene->removeItem(item);
        delete item;
    }

}

void ViewGraphic::markVisited(int x, int y) {
    QPair<int, int> tilePos(x, y);

    // Check if this tile is already marked
    if (!markedTiles.contains(tilePos)) {
        // Create a new marked tile view
        MarkedTileViewGraphic *markedView = new MarkedTileViewGraphic(size, x, y);
        scene->addItem(markedView); // Assuming 'scene' is your QGraphicsScene instance

        // Store the reference to the marked tile
        markedTiles.insert(tilePos, markedView);
    }

    // Optional: Add any additional logic for already marked tiles
}

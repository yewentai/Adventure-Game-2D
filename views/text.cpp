#include "text.h"

ViewText::ViewText(GameModel *model, int size) : size(size) {
    // Initialize the scene and add it to the view
    scene = new QGraphicsScene();
    this->setScene(scene);

    const std::vector <std::unique_ptr<Tile>> &tiles = model->getTiles();
    const std::unique_ptr <ProtagonistModel> &protag = model->getProtagonist();
    const std::vector <std::unique_ptr<Enemy>> &enemies = model->getEnemies();
    const std::vector <std::unique_ptr<HealthPack>> &hps = model->getHealthPacks();

    // Set the default size of the view.
    this->setFixedSize(size * model->getCols() + 2, size * model->getRows() + 2);

    // Construct a background view for the model and connect
    new GrassworldViewText(tiles, size, scene);

    ProtagonistViewText *ptView = new ProtagonistViewText(size, protag->getXPos(), protag->getYPos());
    scene->addItem(ptView);
    connect(protag.get(), SIGNAL(posChanged(int, int)), ptView, SLOT(handlePosChanged(int, int)));

    for (const auto &e: enemies) {
        // Generate the views of tiles according to the tile type
        if (dynamic_cast<PEnemy *>(e.get())) {
            PEnemyViewText *pView = new PEnemyViewText(size, e->getXPos(), e->getYPos());
            scene->addItem(pView);
            connect(e.get(), SIGNAL(dead()), pView, SLOT(handleDead()));
            connect(e.get(), SIGNAL(poisonLevelUpdated(int)), pView, SLOT(handlePoisonLevelUpdated(int)));
        } else if (dynamic_cast<XEnemy *>(e.get())) {
            XEnemyViewText *xView = new XEnemyViewText(size, e->getXPos(), e->getYPos());
            scene->addItem(xView);
            connect(e.get(), SIGNAL(dead()), xView, SLOT(handleDead()));
        } else {
            EnemyViewText *eView = new EnemyViewText(size, e->getXPos(), e->getYPos());
            scene->addItem(eView);
            connect(e.get(), SIGNAL(dead()), eView, SLOT(handleDead()));
        }
    }

    for (const auto &h: hps) {
        HealthPackViewText *hView = new HealthPackViewText(size, h->getXPos(), h->getYPos());
        scene->addItem(hView);
        connect(h.get(), SIGNAL(hpPicked()), hView, SLOT(handlePicked()));
    }

    for (const auto &g: model->getGates()) {
        QGraphicsTextItem *gateViewText;
        gateViewText = new QGraphicsTextItem(QString("O"));
        gateViewText->setPos(g->getXPos() * size, g->getYPos() * size);

        // Set text color to black
        gateViewText->setDefaultTextColor(Qt::black);

        // Set text bold
        QFont font = gateViewText->font();
        font.setBold(true);
        gateViewText->setFont(font);

        scene->addItem(gateViewText);
    }
}

void ViewText::wheelEvent(QWheelEvent *event) {
    // Set the transformation anchor to the position of the mouse cursor.
    const ViewportAnchor anchor = transformationAnchor();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Get the amount of scrolling from the wheel event, specifically in the vertical direction.
    int angle = event->angleDelta().y();

    // This will hold the factor by which we'll scale the view.
    qreal factor;

    // Check if the wheel was scrolled upwards and the current zoom factor is not greater than 5.0.
    if (angle > 0 && zoomFactor <= 5.0f) {
        // If so, increase the zoom factor slightly (zoom in).
        factor = 1.03;
    }
        // Check if the wheel was scrolled downwards.
    else if (angle < 0) {
        // Decrease the zoom factor slightly (zoom out).
        factor = 0.97;

        // If the new zoom factor would be less than 1.0, adjust it so the zoom doesn't go below 1.0.
        if (zoomFactor * factor < 1.0f) {
            factor = 1.0f / zoomFactor;
        }
    } else {
        // If there's no vertical scroll, exit the function.
        return;
    }

    // Update the zoom factor.
    zoomFactor *= factor;

    // Apply the scaling to the view.
    scale(factor, factor);

    // Restore the original transformation anchor.
    setTransformationAnchor(anchor);
}

void ViewText::cleanupMarkedTiles() {
    QList < QGraphicsItem * > itemsToRemove;

    for (QGraphicsItem *item: scene->items()) {
        // Check if the item is a MarkedTileView2D
        TextMarkedTile *markedTile = dynamic_cast<TextMarkedTile *>(item);
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

void ViewText::markVisited(int x, int y) {
    QPair<int, int> tilePos(x, y);

    // Check if this tile is already marked
    if (!markedTiles.contains(tilePos)) {
        // Create a new TextMarkedTile object
        TextMarkedTile *markedView = new TextMarkedTile(size, x, y);
        scene->addItem(markedView); // Assuming 'scene' is your QGraphicsScene instance

        // Store the reference to the marked tile
        markedTiles.insert(tilePos, markedView);
    }
}

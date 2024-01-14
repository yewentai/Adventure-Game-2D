#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimeLine>
#include <QMap>
#include <QPair>

#include "lib/world.h"
#include "models/game.h"
#include "graphic_markedtile.h"
#include "views/graphic_protagonist.h"
#include "views/graphic_healthpack.h"
#include "views/graphic_gate.h"
#include "views/graphic_penemy.h"
#include "views/graphic_xenemy.h"
#include "views/graphic_background_grassworld.h"
#include "controllers/protagonist_control.h"

// Define a class called ViewGraphic that inherits from QGraphicsView
class ViewGraphic : public QGraphicsView {
    Q_OBJECT

public:
    // Constructor for the ViewGraphic class, takes a GameModel pointer and an integer size as parameters
    ViewGraphic(GameModel *model, int size, int bgSkin = 1);

    QGraphicsScene *scene; // Pointer to the QGraphicsScene
    virtual ~ViewGraphic() {};   // Virtual destructor

    // Zoom in or out by changing the size of tiles
    int getTileSize() const;

    void markVisited(int x, int y);

    void cleanupMarkedTiles();

    QGraphicsScene *getScene() const;

private:
    int size{1};                                           // Size of tiles
    float zoomFactor{1.0f};                                // Zoom factor
    QMap<QPair < int, int>, MarkedTileViewGraphic *>
    markedTiles; // Map to store marked tile instances
    // Override keyPressEvent to handle key events
    void keyPressEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    // Override wheelEvent to handle wheel events
    void wheelEvent(QWheelEvent *event) override;

    signals:
            void keyPressed(int
    key); // Signal emitted when a key is pressed
    void tileClicked(int x, int y);

public
    slots:
};

#endif // GRAPHIC_H

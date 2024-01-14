#ifndef TEXDT_H
#define TEXDT_H

#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimeLine>

#include "lib/world.h"
#include "models/game.h"
#include "views/text_protagonist.h"
#include "views/text_healthpack.h"
#include "views/text_penemy.h"
#include "views/text_xenemy.h"
#include "views/text_background.h"
#include "controllers/protagonist_control.h"
#include "text_markedtile.h"

// Define a class called ViewText that inherits from QGraphicsView
class ViewText : public QGraphicsView
{
    Q_OBJECT

public:
    // Constructor for the ViewText class, takes a GameModel pointer and an integer size as parameters
    ViewText(GameModel *model, int size);

    QGraphicsScene *scene; // Pointer to the QGraphicsScene
    virtual ~ViewText(){}; // Virtual destructor

    // Zoom in or out by changing the size of tiles
    void zoom(int newSize);
    void markVisited(int x, int y);
    void cleanupMarkedTiles();

private:
    int size{1};                                         // Size of tiles
    float zoomFactor{1.0f};                              // Zoom factor
    QMap<QPair<int, int>, TextMarkedTile *> markedTiles; // Map to store marked tile instances

    // Override wheelEvent to handle wheel events
    void wheelEvent(QWheelEvent *event) override;

public slots:
};

#endif // TEXDT_H

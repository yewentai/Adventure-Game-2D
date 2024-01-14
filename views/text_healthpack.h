#ifndef TEXT_HEALTHPACK_H
#define TEXT_HEALTHPACK_H

#include "views/text_tile.h"
#include <QFont> // Include for QFont

class HealthPackViewText : public TileViewText
{
    Q_OBJECT

public:
    // Constructor for the HealthPackViewText class
    HealthPackViewText(int size, int xPos, int yPos)
        : TileViewText(size, xPos, yPos)
    {
        // Set the pixmap and Z-value for the health pack view
        this->setPlainText(QString("+"));
        QFont font = this->font();
        font.setBold(true);
        this->setFont(font);
        this->setPos(xPos * size, yPos * size);
        this->setZValue(2); // Set the Z-value for layering
    };

private:
public slots:
    // Handle the event when the health pack is picked up
    void handlePicked();
};

// Implementation of the handlePicked slot
inline void HealthPackViewText::handlePicked()
{
    this->deleteLater(); // Delete the health pack view after it's picked up
}

#endif // TEXT_HEALTHPACK_H

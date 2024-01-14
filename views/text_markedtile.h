#ifndef TEXT_MARKEDTILE_H
#define TEXT_MARKEDTILE_H

#include "text_tile.h" // Include the header file for TileViewText
#include <QFont>
#include <QBrush>

class TextMarkedTile : public TileViewText
{
public:
    TextMarkedTile(int size, int xPos, int yPos)
        : TileViewText(size, xPos, yPos) // Call the constructor of the base class
    {
        setPlainText("X");                        // Set the text to 'X'
        setDefaultTextColor(Qt::red);             // Set the color to red
        setFont(QFont("Arial", 10, QFont::Bold)); // Set the font

        // The position is already set by the TileViewText constructor
    }
};

#endif // TEXT_MARKEDTILE_H

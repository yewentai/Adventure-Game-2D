#include "graphic_protagonist.h"

ProtagonistView2D::ProtagonistView2D(int size, int xPos, int yPos)
    : TileView2D(size, xPos, yPos),
      viewAlive(new QPixmap(QString(":/src/tile_images/player1.png")))
{
    // Set up the protagonist view
    this->setPixmap(viewAlive->scaled(size, size));
    this->setZValue(5);

    // Create the poisoned view
    viewPoisoned = new PoisonView2D(size, 0, 0, this);
    viewPoisoned->setPos(0, -1 * size);

    // Initialize poisoned animation for xScale
    poisonedAnimationX = new QPropertyAnimation(viewPoisoned->getScaleTransform(), "xScale", viewPoisoned);
    poisonedAnimationX->setDuration(1000);
    poisonedAnimationX->setKeyValueAt(0, 1.2);   // Starting scale
    poisonedAnimationX->setKeyValueAt(0.5, 1.8); // Midpoint - maximum scale
    poisonedAnimationX->setKeyValueAt(1, 1.2);   // End - back to original scale
    poisonedAnimationX->setEasingCurve(QEasingCurve::InOutQuad);
    poisonedAnimationX->setLoopCount(-1);

    // Initialize poisoned animation for yScale
    poisonedAnimationY = new QPropertyAnimation(viewPoisoned->getScaleTransform(), "yScale", viewPoisoned);
    poisonedAnimationY->setDuration(1000);
    poisonedAnimationY->setKeyValueAt(0, 1.2);   // Starting scale
    poisonedAnimationY->setKeyValueAt(0.5, 1.8); // Midpoint - maximum scale
    poisonedAnimationY->setKeyValueAt(1, 1.2);   // End - back to original scale
    poisonedAnimationY->setEasingCurve(QEasingCurve::InOutQuad);
    poisonedAnimationY->setLoopCount(-1);
}

void ProtagonistView2D::handlePosChanged(int x, int y)
{
    this->setPos(x * size, y * size);
}

void ProtagonistView2D::handlePoioned()
{
    viewPoisoned->setParentItem(this);
    viewPoisoned->setVisible(true);
    // Start the animations
    poisonedAnimationX->start();
    poisonedAnimationY->start();
}

void ProtagonistView2D::handleRecovered()
{
    // Stop the animations
    poisonedAnimationX->stop();
    poisonedAnimationY->stop();
    viewPoisoned->setVisible(false);
    viewPoisoned->setParentItem(nullptr);
}

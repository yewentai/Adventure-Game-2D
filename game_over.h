#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

class GameOverDialog : public QDialog {
    Q_OBJECT

public:
    explicit GameOverDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Game Over");
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *label = new QLabel("Game Over!", this);
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        QPushButton *restartButton = new QPushButton("Restart", this);
        layout->addWidget(restartButton);

        connect(restartButton, &QPushButton::clicked, this, &GameOverDialog::onRestartClicked);
    }

    // signals:
    //     void restartGame();

private

    slots :
    void onRestartClicked() {
        this->close(); // Close the dialog
        qDebug() << "Dialog closed";
    }
};

#endif // GAME_OVER_H

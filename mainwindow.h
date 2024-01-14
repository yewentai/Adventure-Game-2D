#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// Components
#include <QMenu>
#include <QMenuBar>
#include <QProgressBar>
#include <QAction>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QTabWidget>
#include <QTextBrowser>
// Layout
#include <QStackedWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGraphicsView>
#include <QPlainTextEdit>
#include <memory> // Include this for smart pointers
#include "lib/world.h"
#include "views/text.h"
#include "views/graphic.h"
#include "models/game.h"
#include "controllers/protagonist_control.h"
#include "controllers/penemy_control.h"
#include "controllers/level_control.h"
#include "my_text_editor.h"
#include "my_slider.h"
#include "views/game_over.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Constructor for the MainWindow class
    MainWindow(QWidget *parent = nullptr);

    // Destructor for the MainWindow class
    ~MainWindow();

    // Initialize the game world and user interface
    void worldInit();

    // Update the game world
    void updateGameState();

    // Handle the command entered by the user
    void handleCommandEntered();

protected:
    // bool eventFilter(QObject *obj, QEvent *event);

    signals:
            void commandEntered(
    const QString &command
    );

protected:
    // bool eventFilter(QObject *obj, QEvent *event);

public
    slots:
            void onTabChanged(int
    index);

    void onRestartButtonClicked();

    void onLevelChanged(int preIndex);

    void checkGameOver();

private:
    int currentTab;
    Ui::MainWindow *ui;                   // User interface components
    QHBoxLayout *hboxLayout1;             // Horizontal layout for UI components
    QGridLayout *worldLayout;             // Grid layout for the game world
    QPushButton *btn;                     // Button for UI interaction
    QLabel *commandLabel;                 // Command Label
    QLabel *difficultyLabel;              // Difficulty Label
    QTextBrowser *commandExamplesBrowser; // Command examples browser
    MyTextEditor *commandTextEdit;        // Declare the command widget as a member variable
    QTabWidget *tabWidget;                // Widget for different views
    QStackedWidget *tabGraphic;                // Widget for Graphic view
    QStackedWidget *tabText;              // Widget for Text view
    QProgressBar *healthBar;
    QProgressBar *energyBar;
    // std::unique_ptr<GameModel> gameModel;
    std::unique_ptr <LevelController> levelModel = nullptr;
    MySlider *difficultySlider;
    std::unique_ptr <GameModel> gameModel = nullptr;
    std::unique_ptr <ViewGraphic> viewGraphic = nullptr;
    std::unique_ptr <ViewText> viewText = nullptr;
    std::unique_ptr <ProtagonistController> pController = nullptr;
    QPushButton *autoplayBtn;
    std::vector <std::unique_ptr<PEnemyController>> pEnemyControllers;
    GameOverDialog *gameOverDialog;
    // QWidget* gameOverScreen;
    QLabel *healthLabel;
    QLabel *energyLabel;
    bool gameOver{false};
    bool levelInit{false};
};

#endif // MAINWINDOW_H

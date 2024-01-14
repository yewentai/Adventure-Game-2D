#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Main window settings
    this->setWindowTitle("MainWindow");
    this->resize(837, 593);

    // Central widget
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Top-level horizontal layout
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Tab widget
    tabWidget = new QTabWidget();
    tabWidget->setGeometry(10, 10, 550, 571);
    tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tabWidget->setMinimumSize(550, 550);
    mainLayout->addWidget(tabWidget);

    // Tab pages
    tab2D = new QStackedWidget();
    tab2D->setWindowTitle("Graphic");
    tab2D->setGeometry(0, 0, 542, 542);
    tabWidget->addTab(tab2D, "Graphic");

    tabText = new QStackedWidget();
    tabText->setWindowTitle("Text");
    tabText->setGeometry(0, 0, 542, 542);
    tabWidget->addTab(tabText, "Text");

    // Layout for side widgets
    QVBoxLayout *sideLayout = new QVBoxLayout();
    mainLayout->addLayout(sideLayout);
    sideLayout->setSizeConstraint(QLayout::SetMinimumSize);

    // Health Label
    healthLabel = new QLabel("Health", centralWidget);
    healthLabel->setAlignment(Qt::AlignCenter);
    sideLayout->addWidget(healthLabel);

    // Health Progress Bar
    healthBar = new QProgressBar(centralWidget);
    healthBar->setValue(24);
    sideLayout->addWidget(healthBar);

    // Energy Label
    energyLabel = new QLabel("Energy", centralWidget);
    energyLabel->setAlignment(Qt::AlignCenter);
    sideLayout->addWidget(energyLabel);

    // Energy Progress Bar
    energyBar = new QProgressBar(centralWidget);
    energyBar->setValue(24);
    sideLayout->addWidget(energyBar);

    // Difficulty Label
    difficultyLabel = new QLabel("Difficulty", centralWidget);
    difficultyLabel->setAlignment(Qt::AlignCenter);
    sideLayout->addWidget(difficultyLabel);

    // Difficulty Slider
    difficultySlider = new MySlider(centralWidget);
    difficultySlider->setOrientation(Qt::Horizontal);
    difficultySlider->setMinimum(1);
    difficultySlider->setMaximum(10);
    difficultySlider->setValue(5);
    sideLayout->addWidget(difficultySlider);

    // Auto Play Button
    autoplayBtn = new QPushButton("auto play", centralWidget);
    sideLayout->addWidget(autoplayBtn);

    // Restart Button
    QPushButton *restartBtn = new QPushButton("restart", centralWidget);
    sideLayout->addWidget(restartBtn);
    connect(restartBtn, SIGNAL(clicked()), this, SLOT(onRestartButtonClicked()));

    // Command Label
    commandLabel = new QLabel("Command", centralWidget);
    commandLabel->setVisible(false);
    sideLayout->addWidget(commandLabel);

    // Command Examples Text Browser
    commandExamplesBrowser = new QTextBrowser(centralWidget);
    commandExamplesBrowser->setPlainText("Examples:\n"
                                         "1. up\n"
                                         "2. down\n"
                                         "3. left\n"
                                         "4. right\n"
                                         "5. goto 2,2\n"
                                         "6. attack\n"
                                         "7. heal\n"
                                         );
    // Set the Browser's size to fit the text
    commandExamplesBrowser->setFixedSize(90, 155);

    // Set the background to be transparent
    QPalette palette = commandExamplesBrowser->palette();
    palette.setBrush(QPalette::Base, Qt::transparent);
    commandExamplesBrowser->setPalette(palette);

    commandExamplesBrowser->setVisible(false);
    sideLayout->addWidget(commandExamplesBrowser);

    // Command Text Edit
    commandTextEdit = new MyTextEditor(centralWidget);

    // Setup command widget (initially hidden)
    commandTextEdit->setVisible(false);
    sideLayout->addWidget(commandTextEdit);

    // connect onTabChanged slot to corresponding signal
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged(int)));

    // Ensure the sideLayout stretches to fill the space
    sideLayout->addStretch();

    // Initialize the game world
    worldInit();
}

MainWindow::~MainWindow()
{
    levelModel.reset();
    view2D.reset();
    viewText.reset();
    pController.reset();
    pEnemyControllers.clear();
}

void MainWindow::worldInit()
{
    // For restart, check if the model and views are deleted
    if (levelModel)
        levelModel.reset();
    if (view2D)
        view2D.reset();
    if (viewText)
        viewText.reset();
    if (pController)
        pController.reset();
    if (!pEnemyControllers.empty())
        pEnemyControllers.clear();

    // reset difficulty slider
    difficultySlider->setValue(5);

    //    if (!gameOverDialog)                   gameOverDialog.reset();

    // Create a levelModel that contains and manages the gameModels
    levelModel.reset(new LevelController());
    const std::unique_ptr<GameModel> &gameModel = levelModel->getCurrentModel();
    connect(levelModel.get(), SIGNAL(levelUpdated(int)), this, SLOT(onLevelChanged(int)));

    // Create a ProtagonistModel object with some parameters.
    const std::unique_ptr<ProtagonistModel> &protag = gameModel->getProtagonist();

    // Calculate the size of the tiles based on the height of the gView2D widget.
    int size = tab2D->size().height() / gameModel->getCols();

    // Adjust the widget size if it's smaller than the number of columns.
    if (tab2D->size().height() <= gameModel->getCols())
    {
        size = 1;
        tab2D->setFixedSize(gameModel->getCols(), gameModel->getRows());
    }

    // Create a View2D object using the GameModel and tile size.
    if (view2D)
    {
        tab2D->removeWidget(view2D.get());
    }
    view2D.reset(new View2D(gameModel.get(), size));

    // Add a 2D view tab to the tabWidget.
    tab2D->addWidget(view2D.get());

    // Set the background for the View2D using the gameModel's background image.
    QPixmap bgScaled = gameModel->getBackground()
                           ->scaled(gameModel->getCols() * view2D->getTileSize(),
                                    gameModel->getRows() * view2D->getTileSize());
    auto bg = view2D->getScene()->addPixmap(bgScaled);
    view2D->setBackgroundBrush(QBrush(bg->pixmap()));
    if (viewText)
    {
        tabText->removeWidget(viewText.get());
    }
    // Create a ViewText object using the GameModel and tile size.
    viewText.reset(new ViewText(gameModel.get(), size));

    // Add a text view tab to the tabWidget.
    tabText->addWidget(viewText.get());

    // Set the health and energy bars based on the protagonist's values.
    healthBar->setValue(protag->getHealth());
    qDebug() << healthBar->value();
    energyBar->setValue(protag->getEnergy());
    qDebug() << energyBar->value();

    // Connect signals from the protagonist to update the health and energy bars.
    connect(protag.get(), SIGNAL(healthChanged(int)), healthBar, SLOT(setValue(int)));
    connect(protag.get(), SIGNAL(energyChanged(int)), energyBar, SLOT(setValue(int)));

    // Connect the commandEntered signal from the view to the handleCommandEntered slot.
    pController.reset(new ProtagonistController(gameModel.get(), protag));

    connect(view2D.get(), SIGNAL(keyPressed(int)), pController.get(), SLOT(handleKeyPress(int)));
    connect(commandTextEdit, SIGNAL(enterKeyPressed(QString)), pController.get(), SLOT(handleCommand(QString)));
    connect(autoplayBtn, &QPushButton::clicked, pController.get(), &ProtagonistController::autoPlay);
    connect(view2D.get(), &View2D::tileClicked, pController.get(), &ProtagonistController::handleTileClick);
    // connect the slider to the protagController
    connect(difficultySlider, SIGNAL(sliderDragged(int)), pController.get(), SLOT(updateDifficulty(int)));

    // marking the path
    connect(pController.get(), &ProtagonistController::tileVisited, view2D.get(), &View2D::markVisited);
    connect(pController.get(), &ProtagonistController::tileVisited, viewText.get(), &ViewText::markVisited);
    connect(pController.get(), &ProtagonistController::tileCleaned, view2D.get(), &View2D::cleanupMarkedTiles);
    connect(pController.get(), &ProtagonistController::tileCleaned, viewText.get(), &ViewText::cleanupMarkedTiles);
    // game over logic
    connect(pController.get(), &ProtagonistController::protagDead, this, &MainWindow::checkGameOver);
    connect(pController.get(), &ProtagonistController::protagTired, this, &MainWindow::checkGameOver);

    connect(commandTextEdit, SIGNAL(tabKeyPressed(QString)), pController.get(), SLOT(handleTab(QString)));
    connect(pController.get(), SIGNAL(commandToComplete(QString)), commandTextEdit, SLOT(setCompletedCommand(QString)));

    // Connect the PEnemy model view and controller
    for (const auto &enemy : gameModel->getEnemies())
    {
        if (dynamic_cast<PEnemyModel *>(enemy.get()))
        {
            pEnemyControllers.emplace_back(new PEnemyController(dynamic_cast<PEnemyModel *>(enemy.get())));
        }
        if (dynamic_cast<XEnemy *>(enemy.get()))
        {
            connect(dynamic_cast<XEnemy *>(enemy.get()), SIGNAL(bounce()), pController.get(), SLOT(handleBounce()));
        }
    }
    this->update();
    view2D->setFocus();
    qDebug() << "World initialized and updated!";
}

void MainWindow::onTabChanged(int index)
{
    // Assuming the "Text" tab is the second tab (index 1)
    currentTab = index;
    bool isTextTabSelected = (index == 1);
    commandLabel->setVisible(isTextTabSelected);
    commandExamplesBrowser->setVisible(isTextTabSelected);
    commandTextEdit->setVisible(isTextTabSelected);
}

void MainWindow::onRestartButtonClicked()
{
    // gameOverScreen->setVisible(false);
    gameOver = false;
    worldInit();
}

void MainWindow::onLevelChanged(int preIndex)
{
    qDebug() << "LevelChanged, world updating...";
    const std::unique_ptr<GameModel> &currModel = levelModel->getCurrentModel();

    // Calculate the size of the tiles based on the height of the gView2D widget.
    int size = tab2D->size().height() / currModel->getCols();

    // Adjust the widget size if it's smaller than the number of columns.
    if (tab2D->size().height() <= currModel->getCols())
    {
        size = 1;
        tab2D->setFixedSize(currModel->getCols(), currModel->getRows());
    }

    // Create a View2D object using the GameModel and tile size.
    if (view2D)
    {
        tab2D->removeWidget(view2D.get());
    }
    view2D.reset(new View2D(currModel.get(), size));

    // Add a 2D view tab to the tabWidget.
    tab2D->addWidget(view2D.get());

    if (viewText)
    {
        tabText->removeWidget(viewText.get());
    }
    // Create a ViewText object using the GameModel and tile size.
    viewText.reset(new ViewText(currModel.get(), size));

    // Add a text view tab to the tabWidget.
    tabText->addWidget(viewText.get());

    // Set the health and energy bars based on the protagonist's values.
    healthBar->setValue(currModel->getProtagonist()->getHealth());
    qDebug() << healthBar->value();
    energyBar->setValue(currModel->getProtagonist()->getEnergy());
    qDebug() << energyBar->value();

    // Connect signals from the protagonist to update the health and energy bars.
    connect(currModel->getProtagonist().get(), SIGNAL(healthChanged(int)), healthBar, SLOT(setValue(int)));
    connect(currModel->getProtagonist().get(), SIGNAL(energyChanged(int)), energyBar, SLOT(setValue(int)));

    // Connect the commandEntered signal from the view to the handleCommandEntered slot.
    // Create a ProtagonistModel object with some parameters.
    const std::unique_ptr<ProtagonistModel> &protag = currModel->getProtagonist();

    pController.reset(new ProtagonistController(currModel.get(), protag));
    connect(view2D.get(), SIGNAL(keyPressed(int)), pController.get(), SLOT(handleKeyPress(int)));
    connect(commandTextEdit, SIGNAL(enterKeyPressed(QString)), pController.get(), SLOT(handleCommand(QString)));
    bool success_auto = connect(autoplayBtn, &QPushButton::clicked, pController.get(), &ProtagonistController::autoPlay);

    qDebug() << success_auto;
    if (!success_auto)
    {
        qDebug() << "Autplay connection failed";
    }
    else
        qDebug() << "Autoplay connection successful";
    bool success = connect(view2D.get(), &View2D::tileClicked, pController.get(), &ProtagonistController::handleTileClick);
    if (!success)
    {
        qDebug() << "Click move connection failed";
    }
    else
        qDebug() << "Click move connection successful";

    // marking the path
    connect(pController.get(), &ProtagonistController::tileVisited, view2D.get(), &View2D::markVisited);
    connect(pController.get(), &ProtagonistController::tileVisited, viewText.get(), &ViewText::markVisited);

    // game over logic
    connect(pController.get(), &ProtagonistController::protagDead, this, &MainWindow::checkGameOver);
    connect(pController.get(), &ProtagonistController::protagTired, this, &MainWindow::checkGameOver);

    connect(commandTextEdit, SIGNAL(tabKeyPressed(QString)), pController.get(), SLOT(handleTab(QString)));
    connect(pController.get(), SIGNAL(commandToComplete(QString)), commandTextEdit, SLOT(setCompletedCommand(QString)));

    // Connect the PEnemy model view and controller
    pEnemyControllers.clear();
    for (const auto &enemy : currModel->getEnemies())
    {
        if (dynamic_cast<PEnemyModel *>(enemy.get()))
        {
            pEnemyControllers.emplace_back(new PEnemyController(dynamic_cast<PEnemyModel *>(enemy.get())));
        }
    }
    this->update();
    view2D->setFocus();
    qDebug() << "World updated based on level!";
}

void MainWindow::checkGameOver()
{
    if (!gameOver)
    {
        gameOver = true;
        gameOverDialog = new GameOverDialog();
        gameOverDialog->setVisible(true);
        gameOverDialog->raise(); // Bring the dialog to the front
        gameOverDialog->activateWindow();
        connect(gameOverDialog, SIGNAL(restartGame()), this, SLOT(onRestartButtonClicked()));
    }
}

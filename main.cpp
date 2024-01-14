#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Create a QApplication object, which manages the application's control flow.
    MainWindow window;            // Create an instance of the MainWindow class, representing the main application window.
    window.show();                // Display the main window to the user.
    return app.exec();            // Start the event loop and execute the application, handling user interactions.
}

#include "gui.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

int qtWindow(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // create window
    QWidget window;
    window.setWindowTitle("Hello Qt");

    // Create a button
    QPushButton button("Click Me!", &window);
    button.setToolTip("Click this button");

    // Connect a slot to the button's clicked signal
    QObject::connect(&button, &QPushButton::clicked, &app, &QApplication::quit);

    // Set up the layout
    QVBoxLayout layout(&window);
    layout.addWidget(&button);
    window.setLayout(&layout);

    // Show the window
    window.show();

    // Run the app event loop
    return app.exec();
}

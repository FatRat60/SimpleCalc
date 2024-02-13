#include "gui.h"
#include <QtWidgets>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget w;
    w.show();

    return app.exec();
}

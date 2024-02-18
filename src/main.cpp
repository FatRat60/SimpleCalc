#include "gui.h"
#include <QtWidgets>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // UUID
    QSharedMemory* shared = new QSharedMemory("0a913a57-5f56-4a90-8bfd-7b2379157557");
    //shared->deleteLater();
    if (!shared->create(512, QSharedMemory::ReadWrite))
    {
        QMessageBox errorMsg;
        QApplication::beep();

        errorMsg.addButton(QMessageBox::Ok);
        errorMsg.setWindowTitle(QObject::tr("Error"));

        errorMsg.setText(QObject::tr("Already Running"));
        errorMsg.setInformativeText(QObject::tr("More than one instance of program not allowed"));

        errorMsg.exec();

        exit(0);
    }

    MainWidget w;
    w.show();

    int val = app.exec();
    shared->deleteLater();
    return val;
}

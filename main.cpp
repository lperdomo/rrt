#include <QApplication>
#include <QThread>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller controller;
    controller.run();

    return a.exec();
}

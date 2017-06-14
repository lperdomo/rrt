#include <QApplication>
#include <QThread>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller controller(500, 500, 5);
    controller.run();

    return a.exec();
}

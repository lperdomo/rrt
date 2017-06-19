#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *buttonRun = new QPushButton("Run", this);
    ui->mainToolBar->addWidget(buttonRun);

    QPushButton *buttonObs = new QPushButton("Obstacles", this);
    ui->mainToolBar->addWidget(buttonObs);
}

MainWindow::~MainWindow()
{
    delete ui;
}

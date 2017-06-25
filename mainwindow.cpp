#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttonRun = new QToolButton(this);
    buttonRun->setText("Run");
    ui->mainToolBar->addWidget(buttonRun);

    QLabel *labelMode = new QLabel(this);
    labelMode->setText("Mode:");
    ui->mainToolBar->addWidget(labelMode);

    comboMode = new QComboBox(this);
    comboMode->setFixedWidth(100);
    comboMode->addItem("Holonomic", QVariant(1));
    comboMode->addItem("NH-Dubins", QVariant(2));
    ui->mainToolBar->addWidget(comboMode);

    QLabel *labelK = new QLabel(this);
    labelK->setText("K:");
    ui->mainToolBar->addWidget(labelK);

    lineK = new QLineEdit(this);
    lineK->setFixedWidth(60);
    ui->mainToolBar->addWidget(lineK);

    QLabel *labelStep = new QLabel(this);
    labelStep->setText("Step:");
    ui->mainToolBar->addWidget(labelStep);

    lineStep = new QLineEdit(this);
    lineStep->setFixedWidth(60);
    ui->mainToolBar->addWidget(lineStep);

    QLabel *labelBias = new QLabel(this);
    labelBias->setText("Bias:");
    ui->mainToolBar->addWidget(labelBias);

    lineBias = new QLineEdit(this);
    lineBias->setFixedWidth(60);
    ui->mainToolBar->addWidget(lineBias);

    ui->mainToolBar->addSeparator();

    QLabel *labelObstacles = new QLabel(this);
    labelObstacles->setText("Obstacles:");
    ui->mainToolBar->addWidget(labelObstacles);

    lineObstacles = new QLineEdit(this);
    lineObstacles->setFixedWidth(60);
    ui->mainToolBar->addWidget(lineObstacles);

    buttonObs = new QToolButton(this);
    buttonObs->setText("Generate");
    ui->mainToolBar->addWidget(buttonObs);

    ui->mainToolBar->addSeparator();

    labelSearch = new QLabel(this);
    ui->statusBar->addWidget(labelSearch);

    this->connect(new QShortcut(QKeySequence(Qt::Key_Space), this), SIGNAL(activated()), buttonRun, SLOT(click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QToolButton *MainWindow::getButtonRun()
{
    return buttonRun;
}

QToolButton *MainWindow::getButtonObs()
{
    return buttonObs;
}

QLineEdit *MainWindow::getLineK()
{
    return lineK;
}

QLineEdit *MainWindow::getLineStep()
{
    return lineStep;
}

QLineEdit *MainWindow::getLineBias()
{
    return lineBias;
}

QLineEdit *MainWindow::getLineObstacles()
{
    return lineObstacles;
}

QComboBox *MainWindow::getComboMode()
{
    return comboMode;
}

void MainWindow::resetMessage()
{
    labelSearch->setText("Target:");
}

void MainWindow::searchMessage(bool success)
{
    if (success) {
        labelSearch->setText("Target: Found");
    } else {
        labelSearch->setText("Target: Not found");
    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QShortcut>
#include <QKeySequence>
#include <QComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QToolButton *getButtonRun();
    QToolButton *getButtonObs();
    QLineEdit *getLineK();
    QSpinBox *getSpinStep();
    QSpinBox *getSpinBias();
    QSpinBox *getSpinObstacles();
    QComboBox *getComboMode();
    void searchMessage(bool success);
    void resetMessage();
private:
    Ui::MainWindow *ui;
    QToolButton *buttonRun;
    QToolButton *buttonObs;
    QLineEdit *lineK;
    QSpinBox *spinStep;
    QSpinBox *spinBias;
    QSpinBox *spinObstacles;
    QComboBox *comboMode;
    QLabel *labelSearch;
};

#endif // MAINWINDOW_H

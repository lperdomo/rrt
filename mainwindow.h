#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
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
    QLineEdit *getLineStep();
    QLineEdit *getLineBias();
    QLineEdit *getLineObstacles();
    QComboBox *getComboMode();
    void searchMessage(bool success);
    void resetMessage();
private:
    Ui::MainWindow *ui;
    QToolButton *buttonRun;
    QToolButton *buttonObs;
    QLineEdit *lineK;
    QLineEdit *lineStep;
    QLineEdit *lineBias;
    QLineEdit *lineObstacles;
    QComboBox *comboMode;
    QLabel *labelSearch;
};

#endif // MAINWINDOW_H

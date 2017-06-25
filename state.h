#ifndef STATE_H
#define STATE_H

#include <QVector2D>

class State : public QVector2D
{
public:
    State();
    State(double x, double y, double th);
    void setTh(double th);
    double th();
    void operator =(QVector2D v);
private:
    double TH;
};

class StateInput
{
public:
    StateInput();
    void setTh(double th);
    double th();
    void setV(double v);
    double v();
private:
    double TH;
    double V;
};

#endif // STATE_H

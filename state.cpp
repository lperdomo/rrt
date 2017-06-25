#include "state.h"

State::State() :
    QVector2D()
{
    this->TH = 0;
}

State::State(double x, double y, double th) :
    QVector2D(x, y)
{
    this->TH = th;
}

void State::setTh(double th)
{
    this->TH = th;
}

double State::th()
{
    return TH;
}

void State::operator =(QVector2D v)
{
    this->setX(v.x());
    this->setY(v.y());
    TH = 0;
}

StateInput::StateInput()
{
    TH = 0;
    V = 0;
}

void StateInput::setTh(double th)
{
    TH = th;
}

double StateInput::th()
{
    return TH;
}

void StateInput::setV(double v)
{
    V = v;
}

double StateInput::v()
{
    return V;
}

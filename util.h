#ifndef UTIL_H
#define UTIL_H

#include <QVector2D>
#include <state.h>
#include <cmath>

class Util
{
public:
    static double euclideanDistance(QVector2D from, QVector2D to);
    static std::vector<QVector2D> bresenham(QVector2D p1, QVector2D p2);

    static std::vector<QVector2D> dubins(State p1, State p2, double step);
    static State dubinsTurn(State p1, double deltaAngle, State center);
    static std::vector<State> dubinsFoward(State p1, double distance);

private:
    Util();
};

#endif // UTIL_H

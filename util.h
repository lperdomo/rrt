#ifndef UTIL_H
#define UTIL_H

#include <QVector2D>

#include <cmath>


class Util
{
public:
    static double euclideanDistance(QVector2D from, QVector2D to);
private:
    Util();
};

#endif // UTIL_H

#ifndef UTIL_H
#define UTIL_H

#include <QPoint>

class Util
{
public:
    static double euclideanDistance(QPoint from, QPoint to);
private:
    Util();
};

#endif // UTIL_H
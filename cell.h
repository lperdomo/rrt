#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell(int x, int y);
    int getX();
    int getY();
    static double size;
private:
    int x;
    int y;
};

#endif // CELL_H

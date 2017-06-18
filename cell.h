#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell(int X, int Y);
    int x();
    int y();
    bool operator<(Cell &b);
    static double size;
private:
    int X;
    int Y;
};

#endif // CELL_H

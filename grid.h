#ifndef GRID_H
#define GRID_H
#include <QVector>

struct pixel {
    int R;
    int G;
    int B;
    int A;
};

struct grid
{
    QVector<QVector<pixel>> grid;
};

#endif // GRID_H

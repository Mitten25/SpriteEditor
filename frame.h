#ifndef FRAME_H
#define FRAME_H
#include <QVector>
#include <tuple>
#include "grid.h"

class Frame : public QObject
{
    Q_OBJECT
private:
    int height;
    int width;
    QVector<grid> layers;
    int currLayer;

public:
    Frame();
    std::tuple<int, int, int, int> getPixel();
    void setPixel(std::tuple <int, int, int, int>);

    int addLayer();
    int deleteLayer();
};
#endif // FRAME_H

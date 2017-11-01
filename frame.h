#ifndef FRAME_H
#define FRAME_H
#include <QVector>
#include <tuple>

class Frame
{

private:
    QVector <std::tuple<int, int, int, int>> layers;
    int height;
    int width;


public:
    Frame();
    std::tuple<int, int, int, int> getPixel();
    void setPixel(std::tuple <int, int, int, int>);
};

#endif // FRAME_H

#ifndef FRAME_H
#define FRAME_H
#include <QVector>
#include <tuple>

class Frame
{

private:
    int height;
    int width;

public:
    QVector <QVector<std::tuple<int, int, int, int>>> pixels;
    Frame();
    std::tuple<int, int, int, int> getPixel();
    void setPixel(std::tuple <int, int, int, int>);
};

#endif // FRAME_H

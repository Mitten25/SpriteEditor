#ifndef FRAME_H
#define FRAME_H
#include <QVector>
#include <QColor>
#include <QTableWidget>
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
	static Frame fromTableWidget(QTableWidget* tableWidget);
};

#endif // FRAME_H

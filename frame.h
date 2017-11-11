#ifndef FRAME_H
#define FRAME_H
#include <QVector>
#include <QColor>
#include <QTableWidget>
#include <QString>
#include <tuple>

class Frame
{

private:
    int row;
    int column;

public:
    QVector <QVector<std::tuple<int, int, int, int>>> pixels;
    Frame(int height, int width);
    Frame();
    std::tuple<int, int, int, int> getPixel(int x, int y);
    void setPixel(int x, int y);
    void setColor(std::tuple <int, int, int, int> c);
	static Frame fromTableWidget(QTableWidget* tableWidget);
    QString toString();

    std::tuple <int, int, int, int> color;
    std::tuple<int,int> getSize();
};

#endif // FRAME_H

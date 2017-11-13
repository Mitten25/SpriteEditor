#include "frame.h"

using namespace std;

Frame::Frame(int height, int width)
{
    row = height;
    column = width;
    color = std::tuple<int,int,int,int> (0,0,0,255);

    //Will set everything to transparent
    for (int y = 0; y < row; y++)
    {
        pixels.append(QVector<std::tuple<int,int,int,int>>(column));
        for (int x = 0; x < column; x++)
        {
            std::tuple<int,int,int,int> blank (255,255,255,0);
            pixels[y][x] = blank;
        }
    }
}

Frame::Frame()
{

}

tuple<int, int, int, int> Frame::getPixel(int x, int y)
{
    return pixels[x][y];
}

void Frame::setPixel(int x, int y)
{
    pixels[x][y] = color;
}

void Frame::erasePixel(int x, int y)
{
    pixels[x][y] = std::tuple<int, int, int, int> (255, 255, 255, 0);
}

void Frame::setColor(std::tuple <int, int, int, int> c)
{
    color = c;
}

std::tuple <int, int, int, int> Frame::getColor()
{
    return color;
}

Frame Frame::fromTableWidget(QTableWidget* tableWidget)
{
    int rows = tableWidget->rowCount();
    int columns = tableWidget->columnCount();
    Frame frame;
    QVector<std::tuple<int, int, int, int>> colors;

    for (int c = 0; c < columns; c++)
    {
        for (int r = 0; r < rows; r++)
        {
            QColor color = tableWidget->itemAt(r, c)->backgroundColor();
            std::tuple<int,int,int,int> mytuple (color.red(), color.green(), color.blue(), color.alpha());
            colors.push_back(mytuple);
        }
        frame.pixels.push_back(colors);
        colors.clear();
    }
    return frame;
}

QString Frame::toString()
{
    QString result;
    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < column; x++)
        {
            std::tuple <int, int, int, int> temp = getPixel(y, x);
            result += QString::number(std::get<0>(temp)) + " "
                    + QString::number(std::get<1>(temp)) + " "
                    + QString::number(std::get<2>(temp)) + " "
                    + QString::number(std::get<3>(temp)) + " ";

        }
        result += QString("\r\n");
    }
    return result;
}

std::tuple<int,int> Frame::getSize()
{
    std::tuple<int,int> temp(row, column);
    return temp;
}

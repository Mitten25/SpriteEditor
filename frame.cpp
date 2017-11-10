#include "frame.h"

using namespace std;

Frame::Frame(int height, int width)
{
    row = height;
    column = width;

    //Will set everything to white
    for (int y = 0; y < row; y++)
    {
        pixels.append(QVector<std::tuple<int,int,int,int>>(column));
        for (int x = 0; x < column; x++)
        {
            std::tuple<int,int,int,int> white (255,255,255,0);
            pixels[y][x] = white;
        }
    }
}

Frame::Frame()
{

}

tuple<int, int, int, int> Frame::getPixel(int x, int y) {
    //To be implemented, may not be using result variable, placed there just as filled to compile.
    return pixels[x][y];
}

void Frame::setPixel(int x, int y)
{
    //To be implemented
    pixels[x][y] = color;
}

void Frame::setColor(std::tuple <int, int, int, int> c)
{
    color = c;
}

Frame Frame::fromTableWidget(QTableWidget* tableWidget)
{
    int rows = tableWidget->rowCount();
    int columns = tableWidget->columnCount();
    Frame frame;
    QVector<std::tuple<int, int, int, int>> colors;

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            QColor color = tableWidget->itemAt(r, c)->backgroundColor();
            std::tuple<int,int,int,int> mytuple (color.red(), color.green(), color.blue(), color.alpha());
            colors.push_back(mytuple);
        }
        frame.pixels.push_back(colors);
        colors.clear();
    }
    //if (frames[currFrame].pixels.size() == 0)
    //    frames[currFrame].pixels = temp;
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
        result += QString("\n");
    }
    return result;
}

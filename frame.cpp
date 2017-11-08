#include "frame.h"

using namespace std;

Frame::Frame()
{

}

tuple<int, int, int, int> Frame::getPixel() {
    //To be implemented, may not be using result variable, placed there just as filled to compile.
    tuple<int, int, int, int> result;
    return result;
}

void Frame::setPixel(tuple <int, int, int, int>) {
    //To be implemented
}

Frame Frame::fromTableWidget(QTableWidget* tableWidget)
{
    int row = tableWidget->rowCount();
    int column = tableWidget->columnCount();
	Frame frame;
    QVector<std::tuple<int, int, int, int>> colors;

    for (int c = 0; c < column; c++) {
        for (int r = 0; r < row; r++) {
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

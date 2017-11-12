#include "model.h"

using namespace std;

Model::Model(QObject *parent) : QObject (parent)
{

}

void Model::newFrame(int height, int width)
{
    Frame temp(height, width);
    frames.append(temp);
    currFrame = frames.size() - 1;
}

void Model::saveFrame()
{
    // TODO:
    emit getFrame(frames);
    //need else for layer number
}

void Model::resetFrame()
{
    frames.clear();
}

void Model::exportGif(QString file_name, int rows, int columns)
{
    if(speed == 0)
    {
        speed = 1;
    }
    int tempSpeed = -1*(1/speed);
    QGifImage file(file_name);
    QVector<QImage> images = framesToImages(rows, columns);
    for(int i = 0; i < images.length(); i++)
    {
        file.addFrame(images[i], tempSpeed);
    }
    file.save(file_name);
}

void Model::currentFrame(int x, int y)
{
    currFrame = x;
}

QVector<QImage> Model::framesToImages(int rows, int columns)
{
    QVector<QImage> images;
    int i, j, k;
    int mult = 8;
    for(i = 0; i < frames.length(); i++)
    {
        QImage temp(QSize(columns*mult, rows*mult), QImage::Format_ARGB32);
        for(k = 0; k < columns; k++)
        {
            for(j = 0; j < rows; j++)
            {
                tuple<int, int, int, int> values;
                values = frames[i].pixels[j][k];
                QRgb value = qRgb(std::get<0>(values), std::get<1>(values), std::get<2>(values));
                colorSection(mult, &temp, k, j, value);
            }
        }
        images.append(temp);
    }
    return images;
}

void Model::colorSection(int mult, QImage *image, int row, int column, QRgb value)
{
    int finalX = row*mult + mult;
    int finalY = column*mult + mult;
    for(int placeX = row*mult; placeX < finalX; placeX++)
    {
        for(int placeY = column*mult; placeY < finalY; placeY++)
        {
            image->setPixel(placeX, placeY, value);
        }
    }
}

void Model::bucketCommand(int y, int x) {


}

void Model::setFramePixel(int x, int y)
{
    frames[currFrame].setPixel(x, y);
}

void Model::setColor(tuple<int, int, int, int> c)
{
    frames[currFrame].setColor(c);
}


void Model::updatePreview()
{
    if(frames.length()>0)
        emit getImages(framesToImages(std::get<0>(frames[0].getSize()), std::get<1>(frames[0].getSize())));
}

void Model::updateSpeed(int pace)
{
    speed = pace;
}

void Model::paintBucket(int x, int y) {
    tuple<int, int, int, int> currentPixel = frames[currFrame].getPixel(x, y);
    tuple<int, int, int, int> currentColor = frames[currFrame].getColor();

    if(currentPixel == currentColor)
        return;

    setFramePixel(x, y);

    int x1 = x - 1;
    int x2 = x + 1;
    int y1 = y - 1;
    int y2 = y + 1;

    if (frames[currFrame].getPixel(x1, y) == currentPixel) {

    }


    }

void Model::currentTool(bool isBucketOn) {

}







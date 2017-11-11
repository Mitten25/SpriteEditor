#include "model.h"

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
                std::tuple<int, int, int, int> values;
                values = frames[i].pixels[k][j];
                QRgb value = qRgb(std::get<0>(values), std::get<1>(values), std::get<2>(values));
                colorSection(mult, &temp, j, k, value);
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

//void Model::getTable(QTableWidget table)
//{
//    currentTable = &table;
//}

void Model::setFramePixel(int x, int y)
{
    frames[currFrame].setPixel(x, y);
}

void Model::setColor(std::tuple<int, int, int, int> c)
{
    frames[currFrame].setColor(c);
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
       return QString("%1, %2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    }
    return QVariant();
}


bool Model::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        QString result = value.toString();
        emit editCompleted( result );
    }
    return true;
}


Qt::ItemFlags Model::flags(const QModelIndex & /*index*/) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

void Model::updatePreview()
{
    emit getImages(framesToImages(std::get<0>(frames[0].getSize()), std::get<1>(frames[0].getSize())));
}

void Model::updateSpeed(int pace)
{
    speed = pace;
}

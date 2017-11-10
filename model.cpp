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

void Model::exportGif(QString file_name, int rows, int columns)
{
    std::cout<< "here" << std::endl;
    QGifImage file(file_name);
    QVector<QImage> images = framesToImages(rows, columns);
    for(int i = 0; i < images.length(); i++)
    {
        file.addFrame(images[i]);
    }
    file.save(file_name);
}

QVector<QImage> Model::framesToImages(int rows, int columns)
{
    QVector<QImage> images;
    int i, j, k;
    for(i = 0; i < frames.length(); i++)
    {
        QImage temp(QSize(rows, columns), QImage::Format_ARGB32);
        for(j = 0; j < rows; j++)
        {
            for(k = 0; k < columns; k++)
            {
                std::tuple<int, int, int, int> values;
                values = frames[i].pixels[k][j];
                QRgb value = qRgb(std::get<0>(values), std::get<1>(values), std::get<2>(values));
                temp.setPixel(j, k, value);
            }
        }
        images.append(temp);
    }
    return images;
}

Frame Model::loadFrame()
{
    // TODO: 
    Frame placeholder;
    return placeholder;
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

void Model::updateFPS(int f)
{
    fps = f;
}

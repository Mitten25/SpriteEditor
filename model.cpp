#include "model.h"

Model::Model(QObject *parent) : QObject (parent)
{

}
void Model::outputFramesData(Frame data)
{
	// TODO: what is this method even supposed to do?
    //QVector<QVector<std::tuple<int,int,int,int>>> frameData;
    //frameData << data;

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

void Model::setFramePixel(int x, int y)
{
    frames[currFrame].setPixel(x, y);
}

void Model::setColor(std::tuple<int, int, int, int> c)
{
    frames[currFrame].setColor(c);
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

void Model::exportGifFile(QString fileName, int rows, int columns)
{
   //const std::string name = fileName.toStdString();
   //QVector<Magick::Image> images = framesToImages(rows, columns);
   //Magick::writeImages(images.begin(), images.end(), name + ".gif");
}

QVector<Magick::Image> Model::framesToImages(int rows, int columns)
{
    QVector<Magick::Image> images;
    int i, j, k;
    //Magick::Geometry size = Magick::Geometry(rows + "x" + columns);
    //Magick::Color color = Magick::Color(0, 0, 0, 0);
    for(i = 0; i < frames.length(); i++)
    {
        //Magick::Image temp(size, color);
        //QImage temp(QSize(rows*size, columns*size), QImage::Format_ARGB32);
        //QPainter painter(&temp);
        for(j = 0; j < rows; j++)
        {
            for(k = 0; k < columns; k++)
            {
                std::tuple<int, int, int, int> values;
                values = frames[i].pixels[j*k][k];
                //temp.pixelColor(j, k, Magick::Color(std::get<0>(values), std::get<1>(values), std::get<2>(values), std::get<3>(values)));
                //painter.setBrush(QBrush(QColor(std::get<0>(values), std::get<1>(values), std::get<2>(values), std::get<3>(values))));
                //painter.fillRect(QRectF(j*size, (k-1)*size, j*size, k*size), QColor(std::get<0>(values), std::get<1>(values), std::get<2>(values), std::get<3>(values)));
            }
        }
        //images.append(Magick::Image(temp));
    }
    return images;
}

Qt::ItemFlags Model::flags(const QModelIndex & /*index*/) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}






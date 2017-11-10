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

void Model::exportGif() 
{
    // TODO: 
}

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

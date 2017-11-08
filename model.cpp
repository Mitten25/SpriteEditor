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
void Model::newFrame()
{
    Frame temp;
    frames.push_back(temp);
    currFrame = frames.size() - 1;
}

void Model::saveFrame()
{
    // TODO:

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




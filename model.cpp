#include "model.h"


Model::Model(QAbstractTableModel *parent) : QAbstractTableModel(parent)
{

}



void Model::saveFrame() 
{
    // TODO: 
}

Frame Model::loadFrame() 
{
    // TODO: 
    Frame placeholder;
    return placeholder;
}

void Model::exportGif() 
{
    // TODO: 
}

int Model::rowCount(const QModelIndex & /*parent*/) const
{
   return spriteSize;
}

int Model::columnCount(const QModelIndex & /*parent*/) const
{
    return spriteSize;
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




#include "model.h"

Model::Model(QObject *parent) : QObject (parent)
{

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
    int row = currentTable->rowCount();
    int column = currentTable->columnCount();
    QVector<QVector<std::tuple<int, int, int, int>>> temp;

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            QColor color = currentTable->itemAt(r, c)->backgroundColor();
            std::tuple<int,int,int,int> mytuple (color.red(), color.green(), color.blue(), color.alpha());
            temp[r][c] = mytuple;
        }
    }
    if (frames[currFrame].pixels.size() == 0)
        frames[currFrame].pixels = temp;
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




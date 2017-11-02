#include "model.h"


Model::Model(QAbstractTableModel *parent) : QAbstractTableModel(parent)
{

}


void Model::saveFrame() {
    //To be implemented
}

Frame Model::loadFrame() {
    //To be implemented
    Frame placeholder;
    return placeholder;
}

void Model::exportGif() {
    //To be implemented
}

void Model::checkCol(int col) {
    this->columns_ = col;
}

void Model::checkRow(int row) {
    this->rows_ = row;
}



int Model::rowCount(const QModelIndex & /*parent*/) const
{
   return rows_;
}

int Model::columnCount(const QModelIndex & /*parent*/) const
{
    return columns_;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    }
    return QVariant();
}



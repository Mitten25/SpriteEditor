#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <cstdlib>
#include <QVector>
#include "frame.h"



class Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Model(QAbstractTableModel *parent);

signals:

public slots:

private:
    QVector<Frame> frames;
    int fps;
    void saveFrame();
    Frame loadFrame();
    void exportGif();

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;


};

#endif // MODEL_H

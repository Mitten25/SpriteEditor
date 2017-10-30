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
    explicit Model(QAbstractTableModel *parent = Q_NULLPTR);

signals:

public slots:

private:
    QVector<Frame> frames;
    int fps;
    QVariant data;
    void saveFrame();
    Frame loadFrame();
    void exportGif();
    int rowCount();
    int columnCount();

};

#endif // MODEL_H

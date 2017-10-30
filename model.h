#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <cstdlib>
#include "frame.h"



class Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Model(QAbstractTableModel *parent = Q_NULLPTR);

signals:

public slots:

private:

};

#endif // MODEL_H

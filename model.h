#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <cstdlib>
#include <QVector>
#include "frame.h"

const int SPRITE_SIZE = 32;

class Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Model(QAbstractTableModel *parent);

signals:
	void editCompleted(const QString &);

public slots:

private:
    QVector<Frame> frames;
	int currFrame;
	int spriteSize = SPRITE_SIZE;

    int fps;
    void saveFrame();
    Frame loadFrame();
    void exportGif();

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
	QString m_gridData[SPRITE_SIZE][SPRITE_SIZE];

};

#endif // MODEL_H

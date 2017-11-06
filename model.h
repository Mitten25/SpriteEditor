#ifndef MODEL_H
#define MODEL_H

#include <QTableWidget>
#include <QObject>
#include <cstdlib>
#include <QVector>
#include <tuple>
#include "frame.h"

const int SPRITE_SIZE = 32;

class Model : public QObject
{
    Q_OBJECT
public:
	int spriteSize = SPRITE_SIZE;
    explicit Model(QObject *parent);
    void addLayer();
    void deleteLayer();

signals:
	void editCompleted(const QString &);
    void addLayerSig(int);
    void deleteLayerSig(int);

public slots:
//    void getTable(QTableWidget);

private:
    QVector<Frame> frames;
    int currFrame;
    QTableWidget *currentTable;


    int fps;
    void newFrame();
    void saveFrame();
    Frame loadFrame();
    void exportGif();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
	QString m_gridData[SPRITE_SIZE][SPRITE_SIZE];

};

#endif // MODEL_H

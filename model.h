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

signals:
	void editCompleted(const QString &);

public slots:
//    void getTable(QTableWidget);
    void newFrame();
    void newCell();
    void updateTableColor(int row, int column);
    void outputFramesData(QVector<QVector<std::tuple<int,int,int,int>>> data);
private:
    QVector<Frame> frames;
    int currFrame;
    QTableWidget *currentTable;
    int pixelCount;

    int fps;
    //void newFrame();
    void saveFrame();
    Frame loadFrame();
    void exportGif();

    //QVector<QVector<std::tuple<int,int,int,int>>> frameData;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
	QString m_gridData[SPRITE_SIZE][SPRITE_SIZE];

};

#endif // MODEL_H

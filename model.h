#ifndef MODEL_H
#define MODEL_H

#include <QTableWidget>
#include <QObject>
#include <cstdlib>
#include <QVector>
#include <tuple>
#include <QFile>
#include <iostream>
#include "frame.h"
#include "qgifglobal.h"
#include "qgifimage.h"

const int SPRITE_SIZE = 32;

class Model : public QObject
{
    Q_OBJECT
public:
	int spriteSize = SPRITE_SIZE;
    explicit Model(QObject *parent);

signals:
	void editCompleted(const QString &);
     void getFrame(QVector<Frame> frame);

public slots:
//    void getTable(QTableWidget);
    void newFrame(int height, int width);
    void setFramePixel(int x, int y);
    void setColor(std::tuple<int, int, int, int> c);
    void saveFrame();
    void updateFPS(int f);
    void exportGif(QString file_name, int rows, int columns);
    void currentFrame(int,int);
    void resetFrame();

private:
    QVector<Frame> frames;
    int currFrame;
    QTableWidget *currentTable;
    int pixelCount;

    int fps;

    QVector<QImage> framesToImages(int rows, int columns);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
	QString m_gridData[SPRITE_SIZE][SPRITE_SIZE];

};

#endif // MODEL_H

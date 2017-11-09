#ifndef MODEL_H
#define MODEL_H

#include <QTableWidget>
#include <QObject>
#include <cstdlib>
#include <QVector>
#include <tuple>
#include <QImage>
#include <QPainter>
#include "frame.h"
#include "ImageMagick-6.8.5/include/ImageMagick-6/Magick++.h"

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
    void outputFramesData(Frame data);
    void exportGifFile(QString fileName, int rows, int columns);
private:
    QVector<Frame> frames;
    int currFrame;
    QTableWidget *currentTable;
    int pixelCount;

    int fps;
    void saveFrame();
    Frame loadFrame();
    QVector<Magick::Image> framesToImages(int rows, int columns);


    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
	QString m_gridData[SPRITE_SIZE][SPRITE_SIZE];

};

#endif // MODEL_H

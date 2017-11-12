#ifndef MODEL_H
#define MODEL_H

#include <QTableWidget>
#include <QObject>
#include <cstdlib>
#include <QVector>
#include <tuple>
#include <QtConcurrent/QtConcurrent>
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
    void getImages(QVector<QImage> images);
public slots:
    void newFrame(int height, int width);
    void setFramePixel(int x, int y);
    void setColor(std::tuple<int, int, int, int> c);
    void saveFrame();
    void updatePreview();
    void exportGif(QString file_name, int rows, int columns);
    void currentFrame(int,int);
    void resetFrame();
    void updateSpeed(int);
    void bucketCommand(int, int);
    void currentTool(bool);

private:
    QVector<Frame> frames;
    int currFrame;
    int speed;

    QVector<QImage> framesToImages(int rows, int columns);
    void colorSection(int mult, QImage *image, int row, int column, QRgb value);

    void paintBucket(int, int);

};

#endif // MODEL_H

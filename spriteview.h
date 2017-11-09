#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPalette>
#include <QColor>
#include <QColorDialog>
#include <QtDebug>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <tuple>
#include <iostream>
#include "model.h"
#include "frame.h"
#include "form.h"

const QString COLOR_STYLE("QPushButton { background-color : %1; }");


namespace Ui {
class SpriteView;
}

class SpriteView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpriteView(Model& model, QWidget *parent = 0);
    ~SpriteView();

signals:
    void frameCreated(Frame frame);
<<<<<<< HEAD
    void createFrame(int height, int width);
    void pixelColor(std::tuple<int,int,int,int> c);
=======
    void exportGif(QString fileName, int rows, int columns);
>>>>>>> c1423051e12ab3c09295791310316f1739807279

private slots:
    void on_colorButton_clicked();
    void colorCell(int row, int column);
    void on_eraseButton_clicked();
<<<<<<< HEAD
    void newFile();
    void saveFile(QVector<Frame>);
    void openFile();
=======

    void on_actionNew_File_triggered();

    void saveFile();

    void loadFile();

    void exportGifFileWindow();

>>>>>>> c1423051e12ab3c09295791310316f1739807279
    void initNewFrame();
    void onFrameSelected(QTableWidgetItem *item);

private:
    Ui::SpriteView *ui;
	// the widget for the currently active frame
	QTableWidget* currentTableWidget; 
	int tableSize;
	QColor activeColor;
	QColor blankColor;
    int frameCount;
    int currentFrameNum;
    QVector<Frame> frames;
    Form *popup;
    int rows_;
    int columns_;

    void initMainDrawBoxItems(int, int);
    void initFrameItem(QTableWidget *newFrame);
    void setActiveColor(QColor color);
    void copyQTableWidgetContents(QTableWidget* from, QTableWidget* to);
    QColor getActiveColor();
};

#endif // SPRITEVIEW_H

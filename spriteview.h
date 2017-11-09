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
    void createFrame(int height, int width);
    void pixelColor(std::tuple<int,int,int,int> c);
    void exportGif(QString fileName, int rows, int columns);

private slots:

    void on_colorButton_clicked();
    void colorCell(int row, int column);
    void on_eraseButton_clicked();
    void newFile();
    void saveFile(QVector<Frame>);
    void openFile();
    void initNewFrame();
    void onFrameSelected(QTableWidgetItem *item);
    void exportGifFileWindow();

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
    int rows_;
    int columns_;

    void initMainDrawBoxItems(int, int);
    void initFrameItem(QTableWidget *newFrame);
    void setActiveColor(QColor color);
    void copyQTableWidgetContents(QTableWidget* from, QTableWidget* to);
    QColor getActiveColor();
};

#endif // SPRITEVIEW_H

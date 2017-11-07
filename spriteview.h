#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPalette>
#include <QColor>
#include <QColorDialog>
#include "model.h"
#include "frame.h"

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
    void frameCreated(QVector<QVector<std::tuple<int, int, int, int>>> frames);
private slots:
    void on_colorButton_clicked();

    void on_tableWidget_pressed(const QModelIndex &index);

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_cellEntered(int row, int column);

    void on_eraseButton_clicked();

    void on_okButton_clicked();

    void on_actionNew_File_triggered();

    void saveFile();

    void loadFile();

    void on_addFrameButton_clicked();

    void initNewFrame();

private:
    Ui::SpriteView *ui;
    QTableWidget* tableWidget;
    int tableSize;
    QColor activeColor;
    int frameCount;
    int currentFrameNum;
    void initTableItems(int, int);
    void initFrameItem(QTableWidget *newFrame);
    void setActiveColor(QColor color);
    QColor getActiveColor();

    QVector<QVector<std::tuple<int, int, int, int>>> getFrame();
};

#endif // SPRITEVIEW_H

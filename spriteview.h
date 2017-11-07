#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPalette>
#include <QColor>
#include <QColorDialog>
#include <QtDebug>
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
    QVector<QVector<std::tuple<int, int, int, int>>> frames;
    QString ASCII_text;

    Form popup;
	
    QVector<QVector<std::tuple<int, int, int, int>>> getFrame();
    void setSizeVisible(bool);
};

#endif // SPRITEVIEW_H

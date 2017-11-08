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

private slots:
    void on_colorButton_clicked();

    void on_tableWidget_cellEntered(int row, int column);

    void on_eraseButton_clicked();

    void on_okButton_clicked();

    void on_actionNew_File_triggered();

    void saveFile();

    void loadFile();

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
    void initMainDrawBoxItems(int, int);
    void initFrameItem(QTableWidget *newFrame);
	void setActiveColor(QColor color);
	void copyQTableWidgetContents(QTableWidget* from, QTableWidget* to); 
	QColor getActiveColor();
	QVector<Frame> frames;
    QString ASCII_text;

    Form *popup;
    int rows_;
    int columns_;
};

#endif // SPRITEVIEW_H

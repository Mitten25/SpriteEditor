#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QColorDialog>
#include "model.h"

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

private slots:
    void on_colorButton_clicked();
    void on_tableWidget_activated(const QModelIndex &index);

    void on_tableWidget_pressed(const QModelIndex &index);

    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::SpriteView *ui;
	QTableWidget* tableWidget;
	QColor activeColor;
	void setActiveColor(QColor color);
	QColor getActiveColor();
	
    void update();
};

#endif // SPRITEVIEW_H

#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>
#include <QTableView>
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
    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_pressed(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::SpriteView *ui;
	QColor activeColor;
	void setActiveColor(QColor color);
	QColor getActiveColor();
    // int size;  // not sure what this is supposed to be used for
	
    void update();
};

#endif // SPRITEVIEW_H

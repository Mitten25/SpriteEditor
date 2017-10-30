#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>
#include <QTableView>
#include "model.h"

namespace Ui {
class SpriteView;
}

class SpriteView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpriteView(Model& model, QWidget *parent = 0);
    ~SpriteView();

private:
    Ui::SpriteView *ui;
    int size; //UML Diagram shows that size should be a 2D Array, doesnt seem right?
    QTableView tableview;
    // Update()
    // Updated is commented out due to unknown return type.
};

#endif // SPRITEVIEW_H

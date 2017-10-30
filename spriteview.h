#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>

namespace Ui {
class SpriteView;
}

class SpriteView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpriteView(QWidget *parent = 0);
    ~SpriteView();

private:
    Ui::SpriteView *ui;
};

#endif // SPRITEVIEW_H

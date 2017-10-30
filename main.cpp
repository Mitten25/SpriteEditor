#include "spriteview.h"
#include "model.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    Model m;
    SpriteView w(m);
    w.show();

    return a.exec();
}

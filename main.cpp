#include "spriteview.h"
#include "model.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	// TODO: add back this line (was failing compile)
    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Model m(0);
    SpriteView w(m);
    w.show();

    return a.exec();
}

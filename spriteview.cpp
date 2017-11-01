#include "spriteview.h"
#include "ui_spriteview.h"

SpriteView::SpriteView(Model& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpriteView)
{
    ui->setupUi(this);
	ui->tableView->setModel( &model );
	ui->tableView->show();
}

SpriteView::~SpriteView()
{
    delete ui;
}

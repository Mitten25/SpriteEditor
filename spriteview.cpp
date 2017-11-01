#include "spriteview.h"
#include "ui_spriteview.h"

SpriteView::SpriteView(Model& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpriteView)
{
    spriteModel = &model;
    ui->setupUi(this);
    ui->frame->setVisible(false);
}

SpriteView::~SpriteView()
{
    delete ui;
}

void SpriteView::on_actionNew_triggered()
{
    ui->frame->setVisible(true);
}
void SpriteView::on_okButton_clicked()
{
    spriteModel->rows = 5;
    spriteModel->columns = 5;
    ui->tableView->setModel( spriteModel );
    ui->tableView->show();
    ui->frame->setVisible(false);
}

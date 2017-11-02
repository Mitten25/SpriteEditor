#include "spriteview.h"
#include "ui_spriteview.h"

SpriteView::SpriteView(Model& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpriteView)
{
    spriteModel = &model;
    ui->setupUi(this);
    ui->frame->setVisible(false);
    connect(ui->spinBox, SIGNAL(valueChanged(int)), &model, SLOT(checkRow(int)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), &model, SLOT(checkCol(int)));
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

    //connect(ui->spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), &spriteModel, &Model::checkCol);
    //spriteModel->rows_ = ui->spinBox->value();
    // spriteModel->columns_ = ui->spinBox_2->value();
    ui->tableView->setModel( spriteModel );
    ui->tableView->show();
    ui->frame->setVisible(false);
}

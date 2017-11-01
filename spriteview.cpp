#include "spriteview.h"
#include "ui_spriteview.h"
#include <QtDebug>

SpriteView::SpriteView(Model& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpriteView)
{
    ui->setupUi(this);
	//ui->tableWidget->setModel( &model );
	tableWidget = ui->tableWidget;
	tableWidget->setRowCount(model.spriteSize);
	tableWidget->setColumnCount(model.spriteSize);

	QColor startColor("black");
	ui->colorButton->setStyleSheet(COLOR_STYLE.arg(startColor.name()));
	activeColor = startColor;
}


void SpriteView::update() 
{

}

SpriteView::~SpriteView()
{
    delete ui;
}

void SpriteView::setActiveColor(QColor color) 
{
	activeColor = color;
	ui->colorButton->setStyleSheet(COLOR_STYLE.arg(activeColor.name()));
	ui->colorButton->setAutoFillBackground(true);
	ui->colorButton->setFlat(true);
}


void SpriteView::on_colorButton_clicked()
{
	QColor chosenColor = QColorDialog::getColor();
	// if user didn't cancel the dialog, set the color to the chosen
	if (chosenColor.isValid()) {
		setActiveColor(chosenColor);
	}
	//qDebug() << chosenColor.name();
}

void SpriteView::on_tableWidget_activated(const QModelIndex &index)
{
	qDebug() << index;
}

void SpriteView::on_tableWidget_pressed(const QModelIndex &index)
{
	qDebug() << "press " << index;

}

void SpriteView::on_tableWidget_clicked(const QModelIndex &index)
{
	qDebug() << "click " << index;

}

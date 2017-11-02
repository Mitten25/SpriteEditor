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

	//QPalette palette = tableWidget->palette();
	//palette.setBrush(QPalette::Highlight,QBrush(Qt::white));
	//palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
	//tableWidget->setPalette(palette);

	QColor startColor("black");
	ui->colorButton->setStyleSheet(COLOR_STYLE.arg(startColor.name()));
	activeColor = startColor;
	int size = model.spriteSize;
	initTableItems(size);

	// TODO: we should probably set up more signals and slots so that
	// the model can control more

    //connect(this, SIGNAL(startGame ()),
    //        &simonGame, SLOT(setSequence()));

    //connect(this, SIGNAL(buttonClick(int)),
    //        &simonGame, SLOT( buttonClick(int)));

    //connect(&simonGame,SIGNAL(resetBoard()),
    //        this, SLOT(drawGameOver()));

    //connect(&simonGame, SIGNAL(updateProgress(float)),
    //        this, SLOT(drawProgress(float)));

    //connect(&simonGame, SIGNAL(sendSequence(std::pair<int, std::vector<int> >)),
    //        this, SLOT(drawSequence(std::pair<int, std::vector<int> >)));



}

void SpriteView::initTableItems(int size) 
{
	tableWidget->setRowCount(size);
	tableWidget->setColumnCount(size);
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			tableWidget->setItem(r, c, new QTableWidgetItem);
			//TODO: set to alpha = 0
		}
	}
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


void SpriteView::on_tableWidget_pressed(const QModelIndex &index)
{
	qDebug() << "press " << index;

}

void SpriteView::on_tableWidget_clicked(const QModelIndex &index)
{
	qDebug() << "click " << index;

}

void SpriteView::on_tableWidget_cellEntered(int row, int column)
{
	tableWidget->item(row, column)->setBackground(activeColor);

}

void SpriteView::on_eraseButton_clicked()
{
	setActiveColor(QColor(0, 0, 0, 0));

}

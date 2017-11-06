#include "spriteview.h"
#include "ui_spriteview.h"
#include <QtDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <iostream>
using namespace std;

SpriteView::SpriteView(Model& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpriteView)
{
    ui->setupUi(this);
    //ui->tableWidget->setModel( &model );
    tableWidget = ui->tableWidget;
    ui->frame->setVisible(false);

    //QPalette palette = tableWidget->palette();
    //palette.setBrush(QPalette::Highlight,QBrush(Qt::white));
    //palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
    //tableWidget->setPalette(palette);

    QColor startColor("black");
    ui->colorButton->setStyleSheet(COLOR_STYLE.arg(startColor.name()));
    activeColor = startColor;
    frameCount = 0;
    currentFrameNum = 0;
    //initTableItems(0);

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

    //
    //connect(ui->addFrameButton, &QPushButton::clicked, &model, &Model::newFrame);
    //

    connect(ui->actionSave_File, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionLoad_File, SIGNAL(triggered(bool)), this, SLOT(loadFile()));

}

void SpriteView::saveFile()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                tr("Save Sprite Sheet"), "",
                                                tr("Sprite Sheet (*.ssp);;All Files (*)"));
    if (file_name.isEmpty())
        return;
    else
    {
        QFile file(file_name);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_9);
        //out << frames; // to save data to file
    }
}

void SpriteView:: loadFile()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                                tr("Open Sprite Sheet"), "",
                                                tr("Sprite Sheet (*.ssp);;All Files (*)"));
    if (file_name.isEmpty())
        return;
    else
    {
        QFile file(file_name);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_9);

        /*
        in << frames; // to load data to file
        if (frames.isEmpty())
        {
            QMessageBox::information(this, tr("No frames in file"),
                                     tr("The file you are attempting to open contains no frames"));
        }
        else
        {
            // Set frames here to file
        }
        */
    }
}

void SpriteView::initTableItems(int row, int column)
{
    tableWidget->setRowCount(row);
    tableWidget->setColumnCount(column);
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            tableWidget->setItem(r, c, new QTableWidgetItem);
            //TODO: set to alpha = 0
        }
    }
}

//creates and initializes a new frame in central widget
void SpriteView::initNewFrame()
{
    QTableWidgetItem *newRow = new QTableWidgetItem();
    ui->framesTable->setRowCount(frameCount+1);
    ui->framesTable->setColumnCount(1);
    ui->framesTable->setItem(frameCount+1,1, newRow);
    ui->framesTable->verticalHeader()->resizeSection(frameCount, 125);
    ui->framesTable->horizontalHeader()->resizeSection(frameCount, 200);
    ui->framesTable->horizontalHeader()->setVisible(false);
    QTableWidget *newFrame = new QTableWidget();
    newFrame->setObjectName("tableWidget"+QString::number(frameCount));

    initFrameItem(newFrame);

    ui->framesTable->setCellWidget(frameCount,0,newFrame);
    frameCount++;
}

void SpriteView::initFrameItem(QTableWidget *newFrame)
{
    int rows = ui->heightBox->value();
    int columns = ui->widthBox->value();

    //initialize items in table
    newFrame->verticalHeader()->setVisible(false);
    newFrame->horizontalHeader()->setVisible(false);
    newFrame->setRowCount(rows);
    newFrame->setColumnCount(columns);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newFrame->setItem(r, c, newItem);
            newFrame->verticalHeader()->resizeSection(r, 100/rows);
            newFrame->horizontalHeader()->resizeSection(c, 100/columns);
            //disable selecting and editing cells
            newFrame->setEditTriggers(QAbstractItemView::NoEditTriggers);
            newFrame->setFocusPolicy(Qt::NoFocus);
            newFrame->setSelectionMode(QAbstractItemView::NoSelection);
        }
    }
}
QVector<QVector<std::tuple<int, int, int, int>>> SpriteView::getFrame()
{
    int row = tableWidget->rowCount();
    int column = tableWidget->columnCount();
    QVector<QVector<std::tuple<int, int, int, int>>> temp;

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            QColor color = tableWidget->itemAt(r, c)->backgroundColor();
            std::tuple<int,int,int,int> mytuple (color.red(), color.green(), color.blue(), color.alpha());
            temp[r][c] = mytuple;
        }
    }
    //if (frames[currFrame].pixels.size() == 0)
    //    frames[currFrame].pixels = temp;
    return temp;
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
    //qDebug() << "press " << index;

}

void SpriteView::on_tableWidget_clicked(const QModelIndex &index)
{
    //qDebug() << "click " << index;

}

void SpriteView::on_tableWidget_cellEntered(int row, int column)
{
    tableWidget->item(row, column)->setBackground(activeColor);
    QTableWidget *cframe = this->findChild<QTableWidget *>("tableWidget"+QString::number(frameCount-1));
    cframe->item(row,column)->setBackground(activeColor);
}

void SpriteView::on_eraseButton_clicked()
{
    setActiveColor(QColor(255, 255, 255, 255));
}

void SpriteView::on_okButton_clicked()
{
   ui->frame->setVisible(false);
   initTableItems(ui->heightBox->value(), ui->widthBox->value());
   initNewFrame();
}



void SpriteView::on_actionNew_File_triggered()
{
   ui->frame->setVisible(true);
}

void SpriteView::on_addFrameButton_clicked()
{
    initNewFrame();
}

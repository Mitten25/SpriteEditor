#include "spriteview.h"
#include "ui_spriteview.h"

SpriteView::SpriteView(Model& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpriteView)
{
    ui->setupUi(this);
	//ui->tableWidget->setModel( &model );
	tableWidget = ui->tableWidget;
    setSizeVisible(false);
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

    //frames
    connect(ui->addFrameButton, SIGNAL(clicked(bool)), this, SLOT(initNewFrame()));
    connect(this, SIGNAL(frameCreated(QVector<QVector<std::tuple<int,int,int,int>>>)), &model, SLOT(outputFramesData(QVector<QVector<std::tuple<int,int,int,int>>>)));

    connect(ui->actionSave_File, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionOpen_File, SIGNAL(triggered(bool)), this, SLOT(loadFile()));

}

void SpriteView::saveFile()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                tr("Save Sprite Sheet"), "",
                                                tr("Sprite Sheet (*.ssp);;All Files (*)"));

    frames = getFrame();
    ASCII_text.clear();

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

        // Write down in ASCII Text
        // Writing down Height and Width
        ASCII_text += QString(tableWidget->rowCount()) + " " + QString(tableWidget->columnCount()) + QString("\n");
        // Writing down Pixels
        for(auto i = frames.begin(); i != frames.end(); i++)
        {
            for (auto j = i->begin(); j != i->end(); j++)
            {
                std::tuple<int, int, int, int> temp = *j;
                ASCII_text += QString(std::get<0>(temp)) + " " + QString(std::get<1>(temp)) + " " + QString(std::get<2>(temp)) + " " + QString(std::get<3>(temp)) + " ";
            }
            ASCII_text += QString("\n");
        }

        qDebug() << ASCII_text;

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_9);
        out << ASCII_text; // to save data to file
    }
}

void SpriteView::loadFile()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                                tr("Open Sprite Sheet"), "",
                                                tr("Sprite Sheet (*.ssp);;All Files (*)"));
    if (file_name.isEmpty())
        return;
    else
    {
        QFile file(file_name);
        // Check if you can open file
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        // Start reading information from file.
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_9);
        frames.clear();
        //in >> frames; // to load data to file

        // Check if there is anything in the file.
        if (frames.isEmpty())
        {
            QMessageBox::information(this, tr("No frames in file"),
                                     tr("The file you are attempting to open contains no frames"));
        }
        else
        {
            // Set frames here to file
        }
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
    //void sendData(){emit redirectData(edit->text());}
    emit frameCreated(getFrame());
}

void SpriteView::initFrameItem(QTableWidget *newFrame)
{
    int rows = ui->heightBox->value();
    int columns = ui->widthBox->value();
    int itemSizeD = rows;
    if(rows < columns){itemSizeD = columns;}
    //initialize items in table
    newFrame->verticalHeader()->setVisible(false);
    newFrame->horizontalHeader()->setVisible(false);
    newFrame->setRowCount(rows);
    newFrame->setColumnCount(columns);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newFrame->setItem(r, c, newItem);
            newFrame->verticalHeader()->resizeSection(r, 100/itemSizeD);
            newFrame->horizontalHeader()->resizeSection(c, 100/itemSizeD);
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
    QVector<std::tuple<int, int, int, int>> colors;

    for (int c = 0; c < column; c++) {
        for (int r = 0; r < row; r++) {
            QColor color = tableWidget->itemAt(r, c)->backgroundColor();
            std::tuple<int,int,int,int> mytuple (color.red(), color.green(), color.blue(), color.alpha());
            colors.push_back(mytuple);
        }
        temp.push_back(colors);
        colors.clear();
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
   setSizeVisible(false);
   initTableItems(ui->heightBox->value(), ui->widthBox->value());
   ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   initNewFrame();
}

void SpriteView::on_actionNew_File_triggered()
{
   setSizeVisible(true);
}

void SpriteView::setSizeVisible(bool mode) {
    ui->sizeLabel->setVisible(mode);
    ui->widthLabel->setVisible(mode);
    ui->heightLabel->setVisible(mode);
    ui->widthBox->setVisible(mode);
    ui->heightBox->setVisible(mode);
    ui->okButton->setVisible(mode);
}

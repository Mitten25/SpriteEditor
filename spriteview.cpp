#include "spriteview.h"
#include "ui_spriteview.h"

SpriteView::SpriteView(Model& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpriteView)
{
    ui->setupUi(this);
	//tableWidget = ui->tableWidget;
    setSizeVisible(true);
	// Color for blank background
	QColor blankColor("white");
	// Initialize color picker button
    QColor startColor("black");
    ui->colorButton->setStyleSheet(COLOR_STYLE.arg(startColor.name()));
    activeColor = startColor;

    frameCount = 0;
    currentFrameNum = 0;

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
    connect(this, SIGNAL(frameCreated(Frame)), &model, SLOT(outputFramesData(Frame)));

    connect(ui->actionSave_File, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionOpen_File, SIGNAL(triggered(bool)), this, SLOT(loadFile()));

}

void SpriteView::saveFile()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                tr("Save Sprite Sheet"), "",
                                                tr("Sprite Sheet (*.ssp);;All Files (*)"));

	Frame frame;
	frame = Frame::fromTableWidget(ui->tableWidget);
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
        ASCII_text += QString(ui->tableWidget->rowCount()) + " " + QString(ui->tableWidget->columnCount()) + QString("\n");
        // Writing down Pixels
        for(auto i = frame.pixels.begin(); i != frame.pixels.end(); i++)
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
        //out.setVersion(QDataStream::Qt_5_9);
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
        //in.setVersion(QDataStream::Qt_5_9);
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
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setColumnCount(column);
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            ui->tableWidget->setItem(r, c, new QTableWidgetItem);
		}
	}
}

void SpriteView::initNewFrame()
{
    QTableWidgetItem *newRow = new QTableWidgetItem();
    ui->framesTable->setRowCount(frameCount+1);
    ui->framesTable->setColumnCount(1);
    ui->framesTable->setItem(frameCount+1, 1, newRow);
    ui->framesTable->verticalHeader()->resizeSection(frameCount, 125);
    ui->framesTable->horizontalHeader()->resizeSection(frameCount, 200);
    ui->framesTable->horizontalHeader()->setVisible(false);

    QTableWidget *newFrame = new QTableWidget();
    newFrame->setObjectName("tableWidget"+QString::number(frameCount));

    initFrameItem(newFrame);
	// clear the current drawing frame
	initTableItems(ui->heightBox->value(), ui->widthBox->value());

    ui->framesTable->setCellWidget(frameCount, 0, newFrame);
    frameCount++;
    //void sendData(){emit redirectData(edit->text());}
    emit frameCreated(Frame::fromTableWidget(ui->tableWidget));

	currentTableWidget = newFrame;
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

    connect(newFrame, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onFrameSelected(QTableWidgetItem*)));

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newFrame->setItem(r, c, newItem);
			newItem->setBackground(QColor("white"));
            newFrame->verticalHeader()->resizeSection(r, 100/itemSizeD);
            newFrame->horizontalHeader()->resizeSection(c, 100/itemSizeD);

            //disable selecting and editing cells
            newFrame->setEditTriggers(QAbstractItemView::NoEditTriggers);
            newFrame->setFocusPolicy(Qt::NoFocus);
            newFrame->setSelectionMode(QAbstractItemView::NoSelection);
        }
    }
}



void SpriteView::copyQTableWidgetContents(QTableWidget* from, QTableWidget* to) {
	// throw an error if they are not the same size
	if (from->rowCount() != to->rowCount() || from->columnCount() != to->columnCount()) {
		throw;
	}

	int row = from->rowCount();
	int column = from->columnCount();
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
			QColor fromColor = from->item(r, c)->background().color();
			to->item(r, c)->setBackground(fromColor);
		}
	}
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


/*
 * User clicked to change color of pen
 */
void SpriteView::on_colorButton_clicked()
{
	QColor chosenColor = QColorDialog::getColor();
	// if user didn't cancel the dialog, set the color to the one chosen 
	if (chosenColor.isValid()) {
		setActiveColor(chosenColor);
	}
}

/*
 * User is clicking and dragging in the drawing box
 */
void SpriteView::on_tableWidget_cellEntered(int row, int column)
{
	// change the color of the currently displayed drawing
	ui->tableWidget->item(row, column)->setBackground(activeColor);

	// also change the cell of the frame on the side
    //QTableWidget *cframe = this->findChild<QTableWidget *>("tableWidget"+QString::number(frameCount-1));
    currentTableWidget->item(row,column)->setBackground(activeColor);
}

void SpriteView::on_eraseButton_clicked()
{
    setActiveColor(QColor(255, 255, 255, 255));
}

void SpriteView::on_okButton_clicked()
{
   setSizeVisible(false);
   initTableItems(ui->heightBox->value(), ui->widthBox->value());
   //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   //ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   initNewFrame();
}

void SpriteView::on_actionNew_File_triggered()
{
    popup.show();
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

void SpriteView::onFrameSelected(QTableWidgetItem *item)
{
    qDebug() << "cell";
	QTableWidget* parent = item->tableWidget(); 
	copyQTableWidgetContents(parent, ui->tableWidget); 
	currentTableWidget = parent;
}


#include "spriteview.h"
#include "ui_spriteview.h"

SpriteView::SpriteView(Model& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpriteView)
{
    //popup = new Form();
    ui->setupUi(this);
	//tableWidget = ui->tableWidget;
	// Color for blank background
	QColor blankColor("white");
	// Initialize color picker button
    QColor startColor("black");
    ui->colorButton->setStyleSheet(COLOR_STYLE.arg(startColor.name()));
    activeColor = startColor;

    rows_ = 8;
    columns_ = 8;
    frameCount = 0;
    currentFrameNum = 0;

	// TODO: we should probably set up more signals and slots so that
	// the model can control more

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
		// NOTE: sorry, i was running qt4 and this wouldn't compile - Matt
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
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        // Start reading information from file.
        QTextStream in(&file);
        // NOTE: sorry, i was running qt4 and this wouldn't compile - Matt
        frames.clear();
        //in >> frames; // to load data to file

        QStringList height_and_width = in.readLine().split(" ");
        int height = height_and_width[0].toInt();
        int width = height_and_width[1].toInt();

        //initTableItems(height, width);

        QString frame = in.readLine();

        int num_of_frames = frame.toInt();
        int current_frame = 0;
        // Looping to draw each frame
        while (current_frame < num_of_frames)
        {
            int y = 0;
            // Looping to draw all of the pixels
            while (y < height)
            {
                int x = 0;
                QString current_line = in.readLine();
                QStringList colors = current_line.split(" ");

                // To set each pixel with the correct color
                for (int i = 0; i <= colors.size() - 4; i += 4)
                {
                    //tableWidget->item(y, x)->setBackgroundColor(QColor(colors[i].toInt(),colors[i+1].toInt(),colors[i+2].toInt(),colors[i+3].toInt()));
                    x++;
                }
                y++;
            }
            current_frame++;
        }
    }
}


// Initialize the items in the main draw box so that we can
// change the color of them
void SpriteView::initMainDrawBoxItems(int row, int column)
{
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setColumnCount(column);
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            ui->tableWidget->setItem(r, c, new QTableWidgetItem);
		}
	}
}

/*
 * Creates a new frame and adds it to the frame viewer on the side
 */
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
    initMainDrawBoxItems(rows_, columns_);

    ui->framesTable->setCellWidget(frameCount, 0, newFrame);
    frameCount++;
    //void sendData(){emit redirectData(edit->text());}
    emit frameCreated(Frame::fromTableWidget(ui->tableWidget));

	// Set this to be the current frame(/TableWidget)
	currentTableWidget = newFrame;
}

/*
 * Initialize a new frame in the side bar
 */ 
void SpriteView::initFrameItem(QTableWidget *newFrame)
{
    int rows = rows_;
    int columns = columns_;
    int itemSizeD = rows;
    if(rows < columns){itemSizeD = columns;}
    //initialize items in table
    newFrame->verticalHeader()->setVisible(false);
    newFrame->horizontalHeader()->setVisible(false);
    newFrame->setRowCount(rows);
    newFrame->setColumnCount(columns);

	// Connect this itemClicked signal to trigger the onFrameSelected
	// (used for later clicking to set this to the current frame) 
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



/*
 * Copy all of the colors in one QTableWidget to another
 * (this is used for copying from side panel frame to main draw window)
 */ 
void SpriteView::copyQTableWidgetContents(QTableWidget* from, QTableWidget* to) {
	// throw an error if they are not the same size
	if (from->rowCount() != to->rowCount() || from->columnCount() != to->columnCount()) {
		throw;
	}

	int rowCount = from->rowCount();
	int columnCount = from->columnCount();
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < columnCount; c++) {
			QColor fromColor = from->item(r, c)->background().color();
			to->item(r, c)->setBackground(fromColor);
		}
	}
}


/*
 * Change the active pen color and the color displayed in the box
 */
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
 *
 * so color both the QWidgetTable for the main drawing box and the current frame
 */
void SpriteView::on_tableWidget_cellEntered(int row, int column)
{
	// change the color of the currently displayed drawing
	ui->tableWidget->item(row, column)->setBackground(activeColor);

	// also change the color of the current selected frame
    currentTableWidget->item(row,column)->setBackground(activeColor);
}

void SpriteView::on_eraseButton_clicked()
{
    setActiveColor(QColor(255, 255, 255, 255));
}

void SpriteView::on_okButton_clicked()
{
   // NOTE: sorry. not sure what these were for and they failed to compile
   // with Qt4
   ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   initNewFrame();
}

/*
 * New File button is clicked on 
 */
void SpriteView::on_actionNew_File_triggered()
{
    Form popup;
    if(popup.exec() == QDialog::Accepted)
    {
        initMainDrawBoxItems(popup.getHeight(), popup.getWidth());
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        initNewFrame();
    }
}


/*
 * Called when any of the cells in the frame preview is clicked
 *
 * (note: to change the current frame, the user has to click in the cell area
 * of the frame preview)
 */
void SpriteView::onFrameSelected(QTableWidgetItem *item)
{
	// Grab the parent QTableWidget* of the cell that was clicked on 
	QTableWidget* parent = item->tableWidget(); 
	// Copy the contents of this frame to the main draw box 
	copyQTableWidgetContents(parent, ui->tableWidget); 
	currentTableWidget = parent;
}


SpriteView::~SpriteView()
{
    delete ui;
}

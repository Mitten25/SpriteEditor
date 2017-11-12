#include "spriteview.h"
#include "ui_spriteview.h"
#include <QShortcut>

SpriteView::SpriteView(Model& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpriteView)
{
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
    currentPrev= 0;

    // Short Cuts
    QShortcut *eraser = new QShortcut(QKeySequence("Ctrl+E"), this);
    connect(eraser, SIGNAL(activated()), this, SLOT(on_eraseButton_clicked()));

    // Add Frame
    connect(ui->addFrameButton, SIGNAL(clicked(bool)), this, SLOT(initNewFrame()));

    // File Menu
    connect(ui->actionSave_File, SIGNAL(triggered(bool)), &model, SLOT(saveFrame()));
    connect(&model, SIGNAL(getFrame(QVector<Frame>)), this, SLOT(saveFile(QVector<Frame>)));

    connect(ui->actionOpen_File, SIGNAL(triggered(bool)), &model, SLOT(resetFrame()));
    connect(ui->actionOpen_File, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(this, SIGNAL(loadColor(int,int)), &model, SLOT(setFramePixel(int,int)));

    connect(ui->actionNew_File, SIGNAL(triggered(bool)), &model, SLOT(resetFrame()));
    connect(ui->actionNew_File, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    connect(ui->actionExport_GIF, SIGNAL(triggered(bool)), this, SLOT(exportGifWindow()));
    connect(this, SIGNAL(exportGifSig(QString, int, int)), &model, SLOT(exportGif(QString, int, int)));
    connect(this, SIGNAL(updateSpeed(int)), &model, SLOT(updateSpeed(int)));

    // Create Frame in Model
    connect(this, SIGNAL(createFrame(int,int)), &model, SLOT(newFrame(int,int)));
    connect(ui->framesTable, SIGNAL(cellEntered(int,int)), &model, SLOT(currentFrame(int,int)));
    connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(colorCell(int,int)));
    connect(this, SIGNAL(pixelColor(std::tuple<int,int,int,int>)), &model, SLOT(setColor(std::tuple<int,int,int,int>)));
    connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), &model, SLOT(setFramePixel(int,int)));

    // Preview Animation
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(previewAnim()));
    connect(ui->tableWidget, SIGNAL(cellEntered(int,int)), &model, SLOT(updatePreview()));
    connect(this, SIGNAL(createFrame(int,int)), &model, SLOT(updatePreview()));
    connect(ui->fpsSlider, SIGNAL(valueChanged(int)), &model, SLOT(updatePreview()));
    connect(&model, SIGNAL(getImages(QVector<QImage>)), this, SLOT(updatePrevImages(QVector<QImage>)));
    connect(ui->fpsSlider, SIGNAL(valueChanged(int)), this, SLOT(changeFPS(int)));

    //Onion Skinning
    connect(ui->onionButton, SIGNAL(clicked(bool)), this, SLOT(showOnionSkins()));

}

void SpriteView::saveFile(QVector<Frame> f)
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                tr("Save Sprite Sheet"), "",
                                                tr("Sprite Sheet (*.ssp);;All Files (*)"));

    Frame frame;
    frame = Frame::fromTableWidget(ui->tableWidget);
    QString ASCII_text;

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
        ASCII_text += QString::number(rows_) + " " + QString::number(columns_) + QString("\n");
        // Writing down Number of Frames
        ASCII_text += QString::number(frameCount) + QString("\n");
        // Writing down Pixels
        foreach (Frame p, f)
        {
            ASCII_text += p.toString();
        }

        QTextStream stream(&file);
        stream << ASCII_text; // to save data to file
    }
}

void SpriteView::openFile()
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

        //frames.clear();
        //ui->framesTable->clearContents();

        QStringList height_and_width = in.readLine().split(" ");
        rows_ = height_and_width[0].toInt();
        columns_ = height_and_width[1].toInt();

        //initTableItems(height, width);
        cleanUp();
        initStartFrame();

        QString frame = in.readLine();

        int num_of_frames = frame.toInt();
        int current_frame = 0;
        // Looping to draw each frame
        while (current_frame < num_of_frames)
        {
            int y = 0;
            // Looping to draw all of the pixels
            while (y < rows_)
            {
                int x = 0;
                QString current_line = in.readLine();
                QStringList colors = current_line.split(" ");

                // To set each pixel with the correct color
                for (int i = 0; i <= colors.size() - 4; i += 4)
                {
                    activeColor = QColor(colors[i].toInt(),colors[i+1].toInt(),colors[i+2].toInt(),colors[i+3].toInt());
                    colorCell(y, x);
                    emit loadColor(y, x);
                    x++;
                }
                y++;
            }
            // Check to see if there are more frames before adding another frame
            if (!in.atEnd())
            {
                // Add Frame here
                initNewFrame();
            }
            ui->previewLabel->clear();
            current_frame++;
        }
        // Reset activeColor
        setActiveColor(QColor(0, 0, 0, 255));
    }
}

/*
 * New File button is clicked on
 */
void SpriteView::newFile()
{
    Form popup;
    if(popup.exec() == QDialog::Accepted)
    {
        rows_ = popup.getHeight();
        columns_ = popup.getWidth();
        cleanUp();
        initStartFrame();
        ui->previewLabel->clear();
    }
}

/*
 * Helper method in order to load or make a new file
 */
void SpriteView::initStartFrame()
{
    // Reset UI
    frameCount = 0;
    ui->framesTable->setRowCount(0);
    ui->framesTable->setColumnCount(0);
    ui->addFrameButton->setEnabled(true);
    ui->fpsSlider->setEnabled(true);
    ui->fpsSlider->setValue(0);
    prevImages.clear();
    ui->onionButton->setEnabled(true);
    initMainDrawBoxItems(rows_, columns_);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    initNewFrame();
    initPreview();
    initOnionTables();
    timer->stop();
}

void SpriteView::exportGifWindow()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                tr("Export GIF"), "",
                                                tr("GIF (*.gif)"));
    if (file_name.isEmpty())
        return;
    else
    {
        emit exportGifSig(file_name, rows_, columns_);
    }
}

/*
 * Initialize the items in the main draw box so that we can
 * change the color of them
 */
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
    ui->framesTable->verticalHeader()->resizeSection(frameCount, 135);
    ui->framesTable->horizontalHeader()->resizeSection(frameCount, 220);
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
    emit createFrame(rows_, columns_);
}

/*
 * Initialize a new frame in the side bar
 */ 
void SpriteView::initFrameItem(QTableWidget *newFrame)
{
    int itemSizeD = rows_;
    if(rows_ < columns_){itemSizeD = columns_;}
    int pixSize = ceil(125/itemSizeD);
    if(pixSize<=1)
        pixSize=1;
    //initialize items in table
    newFrame->verticalHeader()->setVisible(false);
    newFrame->horizontalHeader()->setVisible(false);
    newFrame->setRowCount(rows_);
    newFrame->setColumnCount(columns_);
    newFrame->verticalHeader()->setDefaultSectionSize(pixSize);
    newFrame->horizontalHeader()->setDefaultSectionSize(pixSize);
    newFrame->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    newFrame->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //disable selecting and editing cells
    newFrame->setEditTriggers(QAbstractItemView::NoEditTriggers);
    newFrame->setFocusPolicy(Qt::NoFocus);
    newFrame->setSelectionMode(QAbstractItemView::NoSelection);

    // Connect this itemClicked signal to trigger the onFrameSelected
	// (used for later clicking to set this to the current frame) 
    connect(newFrame, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onFrameSelected(QTableWidgetItem*)));

    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < columns_; c++) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setBackground(QColor(0,0,0,0));
            newFrame->setItem(r, c, newItem);
        }
    }
}

/*
 * Initializes the animation preview table
 */
void SpriteView::initPreview()
{
    ui->previewLabel->setFixedWidth(250);
    ui->previewLabel->setFixedHeight(250);
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
void SpriteView::colorCell(int row, int column)
{
	// change the color of the currently displayed drawing
    ui->tableWidget->item(row, column)->setBackground(activeColor);
	// also change the color of the current selected frame
    currentTableWidget->item(row,column)->setBackground(activeColor);
    std::tuple<int, int, int, int> color (activeColor.red(), activeColor.green(), activeColor.blue(), activeColor.alpha());
    emit pixelColor(color);
}

void SpriteView::on_eraseButton_clicked()
{
    setActiveColor(QColor(255, 255, 255, 0));
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

/*
 * Called according to the timer and fps
 * Copies frames and plays animation
 */
void SpriteView::previewAnim()
{
    int ratioNum;
    QImage temp;
    if(rows_<columns_)
    {
        ratioNum = ceil((double)250/columns_);
        temp = prevImages[currentPrev].scaled(250, rows_*ratioNum);
        ui->previewLabel->setPixmap(QPixmap::fromImage(temp));

    }
    else if(columns_<rows_)
    {
        ratioNum = ceil((double)250/rows_);
        temp = prevImages[currentPrev].scaled(columns_*ratioNum,250);
        ui->previewLabel->setPixmap(QPixmap::fromImage(temp));
    }
    else
    {
        temp = prevImages[currentPrev].scaled(250,250);
        ui->previewLabel->setPixmap(QPixmap::fromImage(temp));
    }
    ui->previewLabel->show();
    if(currentPrev < frameCount-1)
        currentPrev++;
    else
        currentPrev = 0;
}

/*
 * Updates images for preview animation when frame is changed
 */
void SpriteView::updatePrevImages(QVector<QImage> images)
{
    prevImages = images;
}
/*
 * Updates the fps when fps slider is changed
 */
void SpriteView::changeFPS(int fps)
{
    int speed;
    if(fps!=0)
    {
        speed = 1000/fps;
        timer->start(speed);
    }
    else
    {
        timer->stop();
        speed = 0;
    }
    emit updateSpeed(speed);
}

/*
 * Shows/hides onion skin when onion skin button is clicked
 */
void SpriteView::showOnionSkins()
{
    int currentFrameI = getCurrentFrameIndex();
    if(onionTables[0]->isVisible())
        for(int i = 0; i < 3; i++)
            onionTables[i]->hide();
    else
    {
        if(currentFrameI != 0)
        {
            int j = 0;
            int i = currentFrameI-1;
            while( i >= 0 && i != currentFrameI-4)//for(int i= currentFrameI-1; 0 <= i; i--)
            {
                QTableWidget *temp = (QTableWidget*)ui->framesTable->cellWidget(i, 0);
                for (int r = 0; r < rows_; r++) {
                    for (int c = 0; c < columns_; c++) {
                        QColor fromColor =temp->item(r,c)->background().color();
                        if(fromColor.alpha()!=0)
                            fromColor.setAlpha(50);
                        onionTables[j]->item(r, c)->setBackground(fromColor);
                    }
                }
                onionTables[j]->show();
                j++;
                i--;
            }
        }
    }

}
/*
 * Initialize onion tables
 */
void SpriteView::initOnionTables()
{
    stackedLayout = new QStackedLayout;
    ui->horizontalLayout->addLayout(stackedLayout,0);
    stackedLayout->addWidget(ui->tableWidget);
    stackedLayout->setStackingMode(QStackedLayout::StackAll);
    for(int i = 0; i < 3; i++)
    {
        onionTables[i] = new QTableWidget();
        onionTables[i]->setRowCount(rows_);
        onionTables[i]->setColumnCount(columns_);
        onionTables[i]->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        onionTables[i]->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        onionTables[i]->verticalHeader()->setVisible(false);
        onionTables[i]->horizontalHeader()->setVisible(false);
        onionTables[i]->setObjectName("onionTable"+QString::number(i));
        onionTables[i]->setStyleSheet("background-color:rgba(0,0,0,0)");
        onionTables[i]->hide();
        stackedLayout->addWidget(onionTables[i]);
        for (int r = 0; r < rows_; r++) {
            for (int c = 0; c < columns_; c++) {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                onionTables[i]->setItem(r, c, newItem);
            }
        }
    }
}

int SpriteView::getCurrentFrameIndex()
{
    int currentFrameIndex = 0;
    for(int i = 0; i < frameCount; i++)
    {
        if(currentTableWidget == ui->framesTable->cellWidget(i,0))
            currentFrameIndex = i;
    }
    return currentFrameIndex;
}

/*
 * Clean up when new file is made, file is opened, or closing app
 */
void SpriteView::cleanUp()
{
    //Main Table
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < columns_; c++) {
            delete ui->tableWidget->item(r,c);
        }
    }

    //Frames
    for(int i = 0; i < frameCount; i++)
    {
        for (int r = 0; r < rows_; r++) {
            for (int c = 0; c < columns_; c++) {
                delete ((QTableWidget*)ui->framesTable->cellWidget(i,0))->item(r,c);
            }
        }
        delete ui->framesTable->item(i, 0);
    }

    //Onion Skinning
    if(onionTables[0] != NULL)
    {
        for(int i = 0; i < 3; i++)
        {
            onionTables[i]->hide();
            for (int r = 0; r < rows_; r++)
            {
                for (int c = 0; c < columns_; c++) {
                    delete onionTables[i]->item(r,c);
                }
            }
            delete onionTables[i];
        }
    }
    delete stackedLayout;
}
SpriteView::~SpriteView()
{
    cleanUp();
    delete timer;
    delete ui;
}

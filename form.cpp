#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Form::accept);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

Form::~Form()
{
    delete ui;
}

/*
 * Gets inputed width
 */
int Form::getWidth()
{
    return width;
}

/*
 * Gets inputed height
 */
int Form::getHeight()
{
    return height;
}

void Form::setSize()
{
    if(ui->sizeBox->currentText() == "8x8")
    {
        width = 8;
        height = 8;
    }
    else if(ui->sizeBox->currentText() == "16x16")
    {
        width = 16;
        height = 16;
    }
    else if(ui->sizeBox->currentText() == "32x32")
    {
        width = 32;
        height = 32;
    }
    else if(ui->sizeBox->currentText() == "64x64")
    {
        width = 64;
        height = 64;
    }
}

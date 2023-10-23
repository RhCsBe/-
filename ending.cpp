#include "ending.h"
#include "ui_ending.h"

Ending::Ending(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ending)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);
}

Ending::~Ending()
{
    delete ui;
}

Ui::Ending *Ending::getUi()
{
    return ui;
}

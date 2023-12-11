#include "ending.h"
#include "ui_ending.h"

Ending::Ending(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ending)
{
    ui->setupUi(this);
    //隐藏删除键
    setWindowFlag(Qt::WindowCloseButtonHint, false);
    //设置固定宽高
    this->setFixedSize(this->width(),this->height());
}

Ending::~Ending()
{
    delete ui;
}

Ui::Ending *Ending::getUi()
{
    return ui;
}

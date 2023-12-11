#include "rule.h"
#include "ui_rule.h"

Rule::Rule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rule)
{
    ui->setupUi(this);
    connect(ui->returnBeginning,&QPushButton::clicked,this,&Rule::close);
    //设置固定宽高
    this->setFixedSize(this->width(),this->height());
}

Rule::~Rule()
{
    delete ui;
}

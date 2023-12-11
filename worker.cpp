#include "worker.h"
#include "ui_worker.h"

Worker::Worker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Worker)
{
    ui->setupUi(this);
    ui->name_1->setStyleSheet("color:yellow;");
    ui->name_2->setStyleSheet("color:yellow;");
    ui->name_3->setStyleSheet("color:yellow;");
    ui->name_4->setStyleSheet("color:yellow;");
    connect(ui->returnBeginning,&QPushButton::clicked,this,&Worker::close);
}

Worker::~Worker()
{
    delete ui;
}

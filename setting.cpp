#include "setting.h"
#include "ui_setting.h"

//Setting::Setting(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::Setting)
//{
//    ui->setupUi(this);
//}

Setting::Setting(QBrush* brush_red,QBrush* brush_black,QPen* background_pen,QWidget *parent):
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    //初始化背景刷和画笔
    this->brush_black=brush_black;
    this->brush_red=brush_red;
    this->background_pen=background_pen;
    //初始化按键组
    redGroup=new QButtonGroup(this);
    blackGroup=new QButtonGroup(this);
    boardGroup=new QButtonGroup(this);
    //添加红方按键组按键
    redGroup->addButton(ui->yellow_1,0);
    redGroup->addButton(ui->white_1,1);
    redGroup->addButton(ui->green_1,2);
    redGroup->addButton(ui->blue_1,3);
    //添加黑方按键组按键
    blackGroup->addButton(ui->yellow_2,0);
    blackGroup->addButton(ui->white_2,1);
    blackGroup->addButton(ui->green_2,2);
    blackGroup->addButton(ui->blue_2,3);
    //添加棋盘按键组按键
    boardGroup->addButton(ui->black_3,0);
    boardGroup->addButton(ui->red_3,1);
    boardGroup->addButton(ui->pink_3,2);
    boardGroup->addButton(ui->orange_3,3);
    connect(ui->ok,QPushButton::clicked,this,[&](){
//        if(ui->yellow_1->isChecked()||ui->white_1->isChecked()||ui->green_1->isChecked()||ui->blue_1->isChecked())
//        {}
//        else
//        {
//            QMessageBox::information(this,"提示","请选择一个红方背景色");
//            return;
//        }
//        if(ui->yellow_2->isChecked()||ui->white_2->isChecked()||ui->green_2->isChecked()||ui->blue_2->isChecked())
//        {}
//        else
//        {
//            QMessageBox::information(this,"提示","请选择一个黑方背景色");
//            return;
//        }
//        if(ui->black_3->isChecked()||ui->red_3->isChecked()||ui->pink_3->isChecked()||ui->orange_3->isChecked())
//        {}
//        else
//        {
//            QMessageBox::information(this,"提示","请选择一个棋盘线条颜色");
//            return;
//        }
        int id_1=redGroup->checkedId();
        int id_2=blackGroup->checkedId();
        int id_3=boardGroup->checkedId();
//        qDebug()<<"id_1="<<id_1;
//        qDebug()<<"id_2="<<id_2;
//        qDebug()<<"id_3="<<id_3;
        switch(id_1)
        {
        case 0:
            this->brush_red->setColor(QColor(Qt::yellow));
            break;
        case 1:
            this->brush_red->setColor(QColor(Qt::white));
            break;
        case 2:
            this->brush_red->setColor(QColor(0x7FFFD4));
            break;
        case 3:
            this->brush_red->setColor(QColor(0x87CEEB));
            break;
        default:
            break;
        }
        switch(id_2)
        {
        case 0:
            this->brush_black->setColor(Qt::yellow);
            break;
        case 1:
            this->brush_black->setColor(Qt::white);
            break;
        case 2:
            this->brush_black->setColor(QColor(0x7FFFD4));
            break;
        case 3:
            this->brush_black->setColor(QColor(0x87CEEB));
            break;
        default:
            break;
        }
        switch(id_3)
        {
        case 0:
            this->background_pen->setColor(Qt::black);
            break;
        case 1:
            this->background_pen->setColor(Qt::red);
            break;
        case 2:
            this->background_pen->setColor(QColor(0xFF1493));
            break;
        case 3:
            this->background_pen->setColor(QColor(255, 165, 0));
            break;
        default:
            break;
        }
        this->close();
    });
    //设置固定宽高
    this->setFixedSize(this->width(),this->height());
}

//Setting::Setting(int *id, QWidget *parent):
//    QDialog(parent),
//    ui(new Ui::Setting)
//{
//    ui->setupUi(this);
//    this->id=id;
//    //初始化背景刷和画笔
////    this->brush_black=brush_black;
////    this->brush_red=brush_red;
////    this->background_pen=background_pen;
//    //初始化按键组
//    redGroup=new QButtonGroup(this);
//    blackGroup=new QButtonGroup(this);
//    boardGroup=new QButtonGroup(this);
//    //添加红方按键组按键
//    redGroup->addButton(ui->yellow_1,0);
//    redGroup->addButton(ui->white_1,1);
//    redGroup->addButton(ui->green_1,2);
//    redGroup->addButton(ui->blue_1,3);
//    //添加黑方按键组按键
//    blackGroup->addButton(ui->yellow_2,0);
//    blackGroup->addButton(ui->white_2,1);
//    blackGroup->addButton(ui->green_2,2);
//    blackGroup->addButton(ui->blue_2,3);
//    //添加棋盘按键组按键
//    boardGroup->addButton(ui->black_3,0);
//    boardGroup->addButton(ui->red_3,1);
//    boardGroup->addButton(ui->pink_3,2);
//    boardGroup->addButton(ui->orange_3,3);
//    connect(ui->ok,QPushButton::clicked,this,[&](){
//        qDebug()<<"Yes";
//        int id_1=redGroup->checkedId();
//        int id_2=blackGroup->checkedId();
//        int id_3=boardGroup->checkedId();
//        qDebug()<<"id_1="<<id_1;
//        qDebug()<<"id_2="<<id_2;
//        qDebug()<<"id_3="<<id_3;
//        this->id[0]=id_1;
//        this->id[1]=id_2;
//        this->id[2]=id_3;
//        qDebug()<<"id[0]"<<this->id[0];
//        qDebug()<<"id[1]"<<this->id[1];
//        qDebug()<<"id[2]"<<this->id[2];
//        //qDebug()<<id;
//        this->close();
//    });
//}


Setting::~Setting()
{
    delete ui;
}

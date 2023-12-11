#include "forbidchess.h"
#include "ui_forbidchess.h"

ForbidChess::ForbidChess(Chess* chess,int** pos,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForbidChess)
{
    ui->setupUi(this);
    this->chess=chess;
    this->pos=pos;
    ui->label->setStyleSheet("color:#FF6100");
    ui->blackGroup->setStyleSheet("color:gold");
    ui->redGroup->setStyleSheet("color:red;");
    //初始化按键组指针
    chessGroup=new QButtonGroup(this);
    chessGroup->setExclusive(false);
    //添加按键
    //setRedChess();
    //setBlackChess();
    setChessGroup();
    connect(ui->ok,QPushButton::clicked,this,[this](){this->setForbidden();this->forbid();this->close();});
    //设置固定宽高
    this->setFixedSize(this->width(),this->height());
}

void ForbidChess::resetForbidden()
{
    for(int i=0;i<30;i++)
    {
        forbidden[i]=false;
    }
}

void ForbidChess::setChessGroup()
{
    chessGroup->addButton(ui->black_jv_1,0);
    chessGroup->addButton(ui->black_ma_1,1);
    chessGroup->addButton(ui->black_xiang_1,2);
    chessGroup->addButton(ui->black_shi_1,3);
    chessGroup->addButton(ui->black_shi_2,4);
    chessGroup->addButton(ui->black_xiang_2,5);
    chessGroup->addButton(ui->black_ma_2,6);
    chessGroup->addButton(ui->black_jv_2,7);
    chessGroup->addButton(ui->black_pao_1,8);
    chessGroup->addButton(ui->black_pao_2,9);
    chessGroup->addButton(ui->black_bing_1,10);
    chessGroup->addButton(ui->black_bing_2,11);
    chessGroup->addButton(ui->black_bing_3,12);
    chessGroup->addButton(ui->black_bing_4,13);
    chessGroup->addButton(ui->black_bing_5,14);
    chessGroup->addButton(ui->red_bing_1,15);
    chessGroup->addButton(ui->red_bing_2,16);
    chessGroup->addButton(ui->red_bing_3,17);
    chessGroup->addButton(ui->red_bing_4,18);
    chessGroup->addButton(ui->red_bing_5,19);
    chessGroup->addButton(ui->red_pao_1,20);
    chessGroup->addButton(ui->red_pao_2,21);
    chessGroup->addButton(ui->red_jv_1,22);
    chessGroup->addButton(ui->red_ma_1,23);
    chessGroup->addButton(ui->red_xiang_1,24);
    chessGroup->addButton(ui->red_shi_1,25);
    chessGroup->addButton(ui->red_shi_2,26);
    chessGroup->addButton(ui->red_xiang_2,27);
    chessGroup->addButton(ui->red_ma_2,28);
    chessGroup->addButton(ui->red_jv_2,29);
}

void ForbidChess::setForbidden()
{
    for(int i=0;i<30;i++)
    {
        if(chessGroup->button(i)->isChecked())
            forbidden[i]=true;
        else
            forbidden[i]=false;
    }
}

void ForbidChess::checkChess(int** pos)
{
    //因为chessBoard的pos数组是动态申请的，会发生地址迁移，原因：未知
    //所以要在每次设置禁用棋子时要重新设置forbidChess的pos指针，确保它和chessBoard的指针保持一致
    this->pos=pos;
    for(int i=0;i<4;i++)
    {
        if(forbidden[i]!=chess[i].dead)
        {
            chessGroup->button(i)->setEnabled(false);
        }
        else
        {
            chessGroup->button(i)->setEnabled(true);
        }
    }
    for(int i=4;i<27;i++)
    {
        if(forbidden[i]!=chess[i+1].dead)
        {
            chessGroup->button(i)->setEnabled(false);
        }
        else
        {
            chessGroup->button(i)->setEnabled(true);
        }
    }
    for(int i=27;i<30;i++)
    {
        if(forbidden[i]!=chess[i+2].dead)
        {
            chessGroup->button(i)->setEnabled(false);
        }
        else
        {
            chessGroup->button(i)->setEnabled(true);
        }
    }
    for(int i=0;i<30;i++)
    {
        if(forbidden[i])
            chessGroup->button(i)->setChecked(true);
        else
            chessGroup->button(i)->setChecked(false);
    }
}

void ForbidChess::forbid()
{
    for(int i=0;i<4;i++)
    {
        if(forbidden[i])
        {
            chess[i].dead=true;
            pos[chess[i].row][chess[i].line]=-1;
        }
        else
        {
            if(!chessGroup->button(i)->isEnabled())
                return;
            chess[i].dead=false;
            pos[chess[i].row][chess[i].line]=i;
        }
    }
    for(int i=4;i<27;i++)
    {
        if(forbidden[i])
        {
            chess[i+1].dead=true;
            pos[chess[i+1].row][chess[i+1].line]=-1;
        }
        else
        {
            if(!chessGroup->button(i)->isEnabled())
                return;
            chess[i+1].dead=false;
            pos[chess[i+1].row][chess[i+1].line]=i+1;
        }
    }
    for(int i=27;i<30;i++)
    {
        if(forbidden[i])
        {
            chess[i+2].dead=true;
            pos[chess[i+2].row][chess[i+2].line]=-1;
        }
        else
        {
            if(!chessGroup->button(i)->isEnabled())
                return;
            chess[i+2].dead=false;
            pos[chess[i+2].row][chess[i+2].line]=i+2;
        }
    }
}

ForbidChess::~ForbidChess()
{
    delete ui;
}

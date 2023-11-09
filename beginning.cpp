#include "beginning.h"
#include "ui_beginning.h"

Beginning::Beginning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Beginning)
{
    ui->setupUi(this);
    QImage* image=new QImage();
    image->load(":/img/img/AHU.png");
    //QPixmap pixmap(":/img/img/AHU.png");
    ui->AHU->setPixmap(QPixmap::fromImage(*image).scaled(ui->AHU->size(), Qt::KeepAspectRatio));
    singlePlay=new SinglePlay();
    chessBoard=new ChessBoard();
    networkPlay=new NetworkPlay();
    //因为show函数响应的时间较长，所以要延迟beginning关闭的时间，否则主进程检测到所有页面全面关闭，会自动结束程序
    //不能给singlePlay和chessBoard设置父对象，否则beginning关闭时会把他们一起关闭
    connect(ui->singlePlay,QPushButton::clicked,this,[this](){singlePlay->reFresh();singlePlay->show();QTimer::singleShot(1000,this,Beginning::close);});
    connect(ui->doublePlay,QPushButton::clicked,this,[this](){chessBoard->reFresh();chessBoard->show();QTimer::singleShot(1000,this,Beginning::close);});
    connect(ui->networkPlay,QPushButton::clicked,this,[this](){networkPlay->reFresh();networkPlay->show();QTimer::singleShot(1000,this,Beginning::close);});
    //连接chessBoard和singlePlayer返回按键和开始页面
    connect(chessBoard->getUi()->returnBeginning,QPushButton::clicked,this,[this](){this->show();QTimer::singleShot(500,chessBoard,ChessBoard::close);});
    connect(singlePlay->getUi()->returnBeginning,QPushButton::clicked,this,[this](){this->show();QTimer::singleShot(500,singlePlay,SinglePlay::close);});
    connect(networkPlay->getUi()->returnBeginning,QPushButton::clicked,this,[this](){this->show();QTimer::singleShot(500,networkPlay,[this](){networkPlay->leave();
networkPlay->clear();networkPlay->close();});});
    //连接beginnign的show函数和networkPlayer的showBeginning信号
    connect(networkPlay,&NetworkPlay::showBeginning,this,[this](){this->show();});
}

Beginning::~Beginning()
{
    delete ui;
}

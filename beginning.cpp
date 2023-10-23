#include "beginning.h"
#include "ui_beginning.h"

Beginning::Beginning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Beginning)
{
    ui->setupUi(this);
    //因为show函数响应的时间较长，所以要延迟beginning关闭的时间，否则主进程检测到所有页面全面关闭，会自动结束程序
    //不能给singlePlay和chessBoard设置父对象，否则beginning关闭时会把他们一起关闭
    connect(ui->singlePlay,QPushButton::clicked,this,[this](){SinglePlay* singlePlay=new SinglePlay();singlePlay->show();QTimer::singleShot(1000,this,Beginning::close);});
    connect(ui->doublePlay,QPushButton::clicked,this,[this](){ChessBoard* chessBoard=new ChessBoard();chessBoard->show();QTimer::singleShot(1000,this,Beginning::close);});
}

Beginning::~Beginning()
{
    delete ui;
}

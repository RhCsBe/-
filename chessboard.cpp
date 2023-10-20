#include "chessboard.h"
#include "ui_chessboard.h"

ChessBoard::ChessBoard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChessBoard)
{
    ui->setupUi(this);
    setChess();
    setPos();
}

ChessBoard::~ChessBoard()
{
    delete ui;
}

void ChessBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    paintBoard(painter);
    paintChess(painter);
    painter.end();
}

void ChessBoard::paintBoard(QPainter &painter)
{
    QPen pen(Qt::black,1);
    painter.setPen(pen);
    //painter.setRenderHint(QPainter::Antialiasing, false);
    for(int i=0;i<10;i++)
    {
        painter.drawLine(2*radius,2*radius+2*i*radius,18*radius,2*radius+2*i*radius);
    }
    for(int i=0;i<9;i++)
    {
        if(i==0||i==8)
        painter.drawLine(2*radius+2*i*radius,2*radius,2*radius+2*i*radius,20*radius);
        else
        {
            painter.drawLine(2*radius+2*i*radius,2*radius,2*radius+2*i*radius,10*radius);
            painter.drawLine(2*radius+2*i*radius,12*radius,2*radius+2*i*radius,20*radius);
        }
    }
    painter.drawLine(8*radius,2*radius,12*radius,6*radius);
    painter.drawLine(12*radius,2*radius,8*radius,6*radius);
    painter.drawLine(8*radius,20*radius,12*radius,16*radius);
    painter.drawLine(12*radius,20*radius,8*radius,16*radius);
    painter.setFont(QFont("Arial",radius,500));
    painter.drawText(2*radius+2*radius,2*radius+8*radius,2*radius,2*radius,Qt::AlignCenter,"楚");
    painter.drawText(2*radius+4*radius,2*radius+8*radius,2*radius,2*radius,Qt::AlignCenter,"河");
    painter.drawText(2*radius+10*radius,2*radius+8*radius,2*radius,2*radius,Qt::AlignCenter,"汉");
    painter.drawText(2*radius+12*radius,2*radius+8*radius,2*radius,2*radius,Qt::AlignCenter,"界");
}

void ChessBoard::paintChess(QPainter &painter)
{
    QPen pen(Qt::black,1.25);
    painter.setPen(pen);
    painter.setFont(QFont("Arial",radius,500));
    for(int i=0;i<32;i++)
    {
        if(chess[i].dead)
            continue;
        painter.setBrush(Qt::yellow);
        if(i==select)
        {
            painter.setBrush(Qt::gray);
        }
        if(i==16)
        {
            painter.setPen(QPen(Qt::red,1.25));
        }
        QPoint point(chess[i].line*2*radius+2*radius,chess[i].row*2*radius+2*radius);
        painter.drawEllipse(point,radius,radius);
        switch(chess[i].identity)
        {
        case jv:
            painter.drawText(chess[i].line*2*radius+2*radius-radius,chess[i].row*2*radius+2*radius-radius,
                2*radius,2*radius,Qt::AlignCenter,"车");
            break;
        case ma:
            painter.drawText(chess[i].line*2*radius+2*radius-radius,chess[i].row*2*radius+2*radius-radius,
                2*radius,2*radius,Qt::AlignCenter,"马");
            break;
        case xiang:
            painter.drawText(chess[i].line*2*radius+2*radius-radius,chess[i].row*2*radius+2*radius-radius,
                2*radius,2*radius,Qt::AlignCenter,"相");
            break;
        case shi:
            painter.drawText(chess[i].line*2*radius+2*radius-radius,chess[i].row*2*radius+2*radius-radius,
                2*radius,2*radius,Qt::AlignCenter,"士");
            break;
        case jiang:
            painter.drawText(chess[i].line*2*radius+2*radius-radius,chess[i].row*2*radius+2*radius-radius,
                2*radius,2*radius,Qt::AlignCenter,"将");
            break;
        case pao:
            painter.drawText(chess[i].line*2*radius+2*radius-radius,chess[i].row*2*radius+2*radius-radius,
                2*radius,2*radius,Qt::AlignCenter,"炮");
            break;
        case bing:
            painter.drawText(chess[i].line*2*radius+2*radius-radius,chess[i].row*2*radius+2*radius-radius,
                2*radius,2*radius,Qt::AlignCenter,"兵");
            break;
        default:
            break;
        }
    }
}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    int x=event->pos().rx();
    int y=event->pos().ry();
    if(x<radius||x>19*radius||y<radius||y>21*radius)
    {
        return;
    }
    cmpPos(x,y);
    if(select==-1)
    {
        select=pos[x+y*9];
    }
    else
    {
        moveTo(select,x,y);
    }
    update();
}

void ChessBoard::setChess()
{
    for(int i=0;i<4;i++)
    {
        chess[i].row=0;
        chess[i].line=i;
        chess[i].color=0;
        chess[i].num=i;
        chess[8-i].row=0;
        chess[8-i].line=8-i;
        chess[8-i].color=0;
        chess[8-i].num=8-i;
        chess[31-i].row=9;
        chess[31-i].line=8-i;
        chess[31-i].color=1;
        chess[31-i].num=31-i;
        chess[23+i].row=9;
        chess[23+i].line=i;
        chess[23+i].color=1;
        chess[23+i].num=23+i;
        switch(i)
        {
        case 0:
            chess[i].identity=status::jv;
            chess[8-i].identity=status::jv;
            chess[31-i].identity=status::jv;
            chess[23+i].identity=status::jv;
            break;
        case 1:
            chess[i].identity=status::ma;
            chess[8-i].identity=status::ma;
            chess[31-i].identity=status::ma;
            chess[23+i].identity=status::ma;
            break;
        case 2:
            chess[i].identity=status::xiang;
            chess[8-i].identity=status::xiang;
            chess[31-i].identity=status::xiang;
            chess[23+i].identity=status::xiang;
            break;
        case 3:
            chess[i].identity=status::shi;
            chess[8-i].identity=status::shi;
            chess[31-i].identity=status::shi;
            chess[23+i].identity=status::shi;
            break;
        default:
            break;
        }
    }
    chess[9].row=2;
    chess[9].line=1;
    chess[9].color=0;
    chess[9].num=9;
    chess[9].identity=status::pao;
    chess[10].row=2;
    chess[10].line=7;
    chess[10].color=0;
    chess[10].num=10;
    chess[10].identity=status::pao;
    for(int i=11;i<16;i++)
    {
        chess[i].row=3;
        chess[i].line=0+(i-11)*2;
        chess[i].color=0;
        chess[i].num=i;
        chess[i].identity=status::bing;
    }
    for(int i=16;i<21;i++)
    {
        chess[i].row=6;
        chess[i].line=0+(i-16)*2;
        chess[i].color=1;
        chess[i].num=i;
        chess[i].identity=status::bing;
    }
    chess[21].row=7;
    chess[21].line=1;
    chess[21].color=1;
    chess[21].num=21;
    chess[21].identity=status::pao;
    chess[22].row=7;
    chess[22].line=7;
    chess[22].color=1;
    chess[22].num=22;
    chess[22].identity=status::pao;

    chess[4].row=0;
    chess[4].line=4;
    chess[4].color=0;
    chess[4].num=4;
    chess[4].identity=status::jiang;

    chess[27].row=9;
    chess[27].line=4;
    chess[27].color=1;
    chess[27].num=27;
    chess[27].identity=status::jiang;
}

void ChessBoard::setPos()
{
    for(int i=0;i<9;i++)
    {
        pos[i]=i;
    }
    for(int i=9;i<81;i++)
    {
        pos[i]=-1;
    }
    pos[19]=9;
    pos[25]=10;
    for(int i=27;i<36;i+=2)
    {
        pos[i]=11+(i-27)/2;
    }
    for(int i=54;i<63;i+=2)
    {
        pos[i]=16+(i-54)/2;
    }
    pos[64]=21;
    pos[70]=22;
    for(int i=81;i<90;i++)
    {
        pos[i]=23+i-81;
    }
    for(int i=0;i<90;i++)
    {
        if(i%9==0&&i!=0)
            qDebug();
        qDebug()<<pos[i];

    }
}

void ChessBoard::cmpPos(int &posX, int &posY)
{
    posX=(posX-radius)/(2*radius);
    posY=(posY-radius)/(2*radius);

}

void ChessBoard::moveTo(int num, int posX, int posY)
{
    int x=chess[num].line;
    int y=chess[num].row;
    pos[x+y*9]=-1;
    if(pos[posX+posY*9]!=-1&&pos[posX+posY*9]!=select)
    {
        chess[pos[posX+posY*9]].dead=true;
    }
    pos[posX+posY*9]=select;
    chess[num].moveTo(posX,posY);
    select=-1;

}


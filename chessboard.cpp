#include "chessboard.h"
#include "ui_chessboard.h"

ChessBoard::ChessBoard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChessBoard)
{
    ui->setupUi(this);
    setChess();
    setPos();
    setAudio();
    setFunctionStyle();
    ending=new Ending(this);
    //qDebug()<<id;
    setting=new Setting(brush_red,brush_black,background_pen,this);
    //setting=new Setting(id,this);
    //这段代码有点问题，记得解决
    //点击再来一局按键后将user设置为0是因为槽函数响应完后主进程回到setEnding函数后继续执行，下一行代码user=!user会将0设置为1
    connect(ending->getUi()->nextOne,QPushButton::clicked,this,[this](){this->setChess();this->setPos();user=0;select=-1;ending->close();});
    connect(ending->getUi()->over,QPushButton::clicked,this,[this](){ending->close();this->close();});
    //connect(ui->personalSetting,QPushButton::clicked,this,[this](){this->setting->exec();setColor();update();});
    //使用队列连接方式，防止在人机模式时与主程序发生冲突
    connect(ui->personalSetting,QPushButton::clicked,this,[this](){this->setting->exec();update();},Qt::QueuedConnection);
    //connect(ui->beginning,QPushButton::clicked,this,ChessBoard::setBegin);
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
    //QPen pen(Qt::black,1);
    painter.setPen(*background_pen);
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
        if(i==16)
        {
            painter.setPen(QPen(Qt::red,1.25));
        }
        if(chess[i].dead)
            continue;
        if(i<16)
        {
            painter.setBrush(*brush_black);
        }
        else
        {
            painter.setBrush(*brush_red);
        }
        if(i==select)
        {
            painter.setBrush(Qt::gray);
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
        if(user&&pos[y][x]<16||!user&&pos[y][x]>15)
        {
            return;
        }
        select=pos[y][x];
        selectChess->play();
    }
    else
    {
        if(select>15&&pos[y][x]>15||select<16&&pos[y][x]<16&&pos[y][x]!=-1)
        {
            if(select==pos[y][x])
                select=-1;
            else
            {
                select=pos[y][x];
                selectChess->play();
            }
        }
        else
        {
            if(judge(select,x,y))
            {
                //要先存储玩家的走法，否则走棋后再存储的数据是错误的，或者可以先生成Step，直接存储Step，就无所谓先走后走
                vector.push_back(new Step(select,x-chess[select].line,y-chess[select].row,pos[y][x]));
                moveChess->play();
                moveTo(select,x,y);
                if(judgment.judge_jiangjun(chess,user,pos))
                {
                    jiangJun->play();
                }
                if(judgment.judge_kill(chess[4],chess[27]))
                    setEnding();
                user=!user;
                userChange();
            }
            else
                return;
        }
    }
    //qDebug()<<user;
    update();
}

void ChessBoard::setAudio()
{
    //分配多媒体指针
    moveChess=new QMediaPlayer(this);
    selectChess=new QMediaPlayer(this);
    killChess=new QMediaPlayer(this);
    jiangJun=new QMediaPlayer(this);
    gameWin=new QMediaPlayer(this);
    gameLose=new QMediaPlayer(this);
    //分配音频输出指针
    audio_moveChess=new QAudioOutput(this);
    audio_selectChess=new QAudioOutput(this);
    audio_killChess=new QAudioOutput(this);
    audio_jiangJun=new QAudioOutput(this);
    audio_gameWin=new QAudioOutput(this);
    audio_gameLose=new QAudioOutput(this);
    //连接多媒体和音频输出
    moveChess->setAudioOutput(audio_moveChess);
    selectChess->setAudioOutput(audio_selectChess);
    killChess->setAudioOutput(audio_killChess);
    jiangJun->setAudioOutput(audio_jiangJun);
    gameWin->setAudioOutput(audio_gameWin);
    gameLose->setAudioOutput(audio_gameLose);
    //设置多媒体资源
    moveChess->setSource(QUrl("qrc:/audio/audio/go.mp3"));
    selectChess->setSource(QUrl("qrc:/audio/audio/select.mp3"));
    killChess->setSource(QUrl("qrc:/audio/audio/eat.mp3"));
    jiangJun->setSource(QUrl("qrc:/audio/audio/Man_jiangjun.mp3"));
    gameWin->setSource(QUrl("qrc:audio/audio/gamewin.mp3"));
    gameLose->setSource(QUrl("qrc:/audio/audio/gamelose.mp3"));    
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

    for(int i=0;i<32;i++)
    {
        chess[i].dead=false;
    }
}

void ChessBoard::setPos()
{
    pos=new int*[10];
    for(int i=0;i<10;i++)
    {
        pos[i]=new int[9];
    }
    for(int i=0;i<9;i++)
    {
        pos[0][i]=i;
    }
    for(int i=1;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            pos[i][j]=-1;
        }
    }
    pos[2][1]=9;
    pos[2][7]=10;
    for(int i=0;i<9;i+=2)
    {
        pos[3][i]=11+i/2;
    }
    for(int i=0;i<9;i+=2)
    {
        pos[6][i]=16+i/2;
    }
    pos[7][1]=21;
    pos[7][7]=22;
    for(int i=0;i<9;i++)
    {
        pos[9][i]=23+i;
    }
//    for(int i=0;i<10;i++)
//    {
//        qDebug();
//        for(int j=0;j<9;j++)
//        {
//            qDebug()<<pos[i][j];
//        }
    //    }
}

void ChessBoard::setFunctionStyle()
{
    ui->pattern->setStyleSheet("color:red;");
    ui->pattern->setText("双人对战");
    ui->user->setStyleSheet("color:red;");
    //ui->regret->setEnabled(false);
    connect(ui->regret,QPushButton::clicked,this,ChessBoard::regretChess);
    //ui->level->setStyleSheet("QComboBox{text-align:center;}");
    ui->level->setEnabled(false);
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
    pos[y][x]=-1;
    if(pos[posY][posX]!=-1&&pos[posY][posX]!=select)
    {
        chess[pos[posY][posX]].dead=true;
        killChess->play();
    }
    pos[posY][posX]=num;
    chess[num].moveTo(posX,posY);
    select=-1;
}

bool ChessBoard::judge(int moveId, int x, int y)
{
    switch(chess[moveId].identity)
    {
    case status::jv:
        return judgment.judge_jv(chess[moveId],x,y,pos);
        break;
    case status::ma:
        return judgment.judge_ma(chess[moveId],x,y,pos);
        break;
    case status::xiang:
        return judgment.judge_xiang(chess[moveId],x,y,pos);
        break;
    case status::shi:
        return judgment.judge_shi(chess[moveId],x,y,pos);
        break;
    case status::jiang:
        return judgment.judge_jiang(chess[moveId],x,y,pos);
        break;
    case status::bing:
        return judgment.judge_bing(chess[moveId],x,y,pos);
        break;
    case status::pao:
        return judgment.judge_pao(chess[moveId],x,y,pos);
        break;
    default:
        break;
    }
}

void ChessBoard::advance(Step *step)
{
    int x=chess[step->moveId].line;
    int y=chess[step->moveId].row;
    pos[y][x]=-1;
    if(pos[y+step->dy][x+step->dx]!=-1)
    {
        chess[pos[y+step->dy][x+step->dx]].dead=true;
    }
    pos[y+step->dy][x+step->dx]=step->moveId;
    chess[step->moveId].moveTo(x+step->dx,y+step->dy);
}

void ChessBoard::retreat(Step *step)
{
    int x=chess[step->moveId].line;
    int y=chess[step->moveId].row;
    if(step->killId!=-1)
    {
        chess[step->killId].dead=false;
    }
    pos[y][x]=step->killId;
    pos[y-step->dy][x-step->dx]=step->moveId;
    chess[step->moveId].moveTo(x-step->dx,y-step->dy);
}

void ChessBoard::setEnding()
{
    if(chess[4].dead)
    {
        QPixmap pixmap(":/img/img/redwin.jpg");
        ending->getUi()->result->setPixmap(pixmap.scaled(ending->getUi()->result->size(), Qt::KeepAspectRatio));
        gameWin->play();
    }
    else
    {
        QPixmap pixmap(":/img/img/blackwin.jpg");
        ending->getUi()->result->setPixmap(pixmap.scaled(ending->getUi()->result->size(), Qt::KeepAspectRatio));
        gameWin->play();
    }
    ending->exec();
}

void ChessBoard::userChange()
{
    if(user)
    {
        ui->user->setText("红方");
    }
    else
    {
        ui->user->setText("黑方");
    }
}

void ChessBoard::reFresh()
{
    this->setChess();
    this->setPos();
    user=1;
    select=-1;
}

//void ChessBoard::setColor()
//{
//    //qDebug()<<id;
//    qDebug()<<id[0];
//    qDebug()<<id[1];
//    qDebug()<<id[2];
//    switch(id[0])
//    {
//    case 0:
//        brush_red->setColor(Qt::yellow);
//        break;
//    case 1:
//        brush_red->setColor(Qt::white);
//        break;
//    case 2:
//        brush_red->setColor(Qt::green);
//        break;
//    case 3:
//        brush_red->setColor(QColor(Qt::blue));
//        break;
//    default:
//        break;
//    }
//    switch(id[1])
//    {
//    case 0:
//        brush_black->setColor(Qt::yellow);
//        break;
//    case 1:
//        brush_black->setColor(Qt::white);
//        break;
//    case 2:
//        brush_black->setColor(Qt::green);
//        break;
//    case 3:
//        brush_black->setColor(Qt::blue);
//        break;
//    default:
//        break;
//    }
//    qDebug()<<"C";
//    switch(id[2])
//    {
//    case 0:
//        background_pen->setColor(Qt::black);
//        break;
//    case 1:
//        background_pen->setColor(Qt::red);
//        break;
//    case 2:
//        background_pen->setColor(QColor(255, 192, 203));
//        break;
//    case 3:
//        background_pen->setColor(QColor(255, 165, 0));
//        break;
//    default:
//        break;
//    }
//}

Ui::ChessBoard *ChessBoard::getUi()
{
    return ui;
}

//void ChessBoard::setBegin()
//{
//    begin=true;
//    ui->beginning->setEnabled(false);
//    ui->personalSetting->setEnabled(false);
//    ui->level->setEnabled(false);
//}

void ChessBoard::regretChess()
{
    if(vector.empty())
        return;
    Step* step=vector.back();
    vector.pop_back();
    retreat(step);
    user=!user;
    update();
}


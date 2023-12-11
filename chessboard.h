#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPainter>
#include "chess.h"
#include <QDebug>
#include <QMouseEvent>
#include "judgment.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include "ending.h"
#include "ui_ending.h"
#include <QVector>
#include "step.h"
#include "setting.h"
#include "forbidchess.h"
#include <QTimer>
#include <QTime>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class ChessBoard; }
QT_END_NAMESPACE

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();
    enum status{
        jiang,shi,xiang,ma,jv,pao,bing
    };//棋子类型枚举俩
    int radius=25;//棋子半径
    Chess chess[32];//棋子数组
    int** pos=nullptr;//底层棋盘数据指针
    int select=-1;//选中的棋子编号
    bool user=true;//当前走棋者
    int hour=0;//小时数
    int minute=0;//分钟数
    int second=0;//秒数
    qint64 beginTime=0;
    QTimer* timer=nullptr;//计时定时器指针
    QVector<Step*> vector;//存储走棋步数
    Judgment judgment;//判定器对象
    QMediaPlayer* moveChess=nullptr;//移动棋子音频
    QMediaPlayer* selectChess=nullptr;//选择棋子音频
    QMediaPlayer* killChess=nullptr;//击杀棋子音频
    QMediaPlayer* jiangJun=nullptr;//将军音频
    QMediaPlayer* gameWin=nullptr;//获胜音频
    QMediaPlayer* gameLose=nullptr;//失败音频
    QAudioOutput* audio_moveChess=nullptr;
    QAudioOutput* audio_selectChess=nullptr;
    QAudioOutput* audio_killChess=nullptr;
    QAudioOutput* audio_jiangJun=nullptr;
    QAudioOutput* audio_gameWin=nullptr;
    QAudioOutput* audio_gameLose=nullptr;
    QBrush* brush_red=new QBrush(Qt::yellow);//红方画刷
    QBrush* brush_black=new QBrush(Qt::yellow);//黑方画刷
    QPen* background_pen=new QPen(Qt::black,1);//棋盘画笔
    //int id[3]={0};//setting对象修改的设置参数
    Ending* ending=nullptr;//游戏结束界面
    Setting* setting=nullptr;//个性化设置界面
    ForbidChess* forbidChess=nullptr;//禁用棋子界面
    void paintEvent(QPaintEvent *event);//绘图事件
    void paintBoard(QPainter& painter);//绘制棋盘
    void paintChess(QPainter& painter);//绘制棋子
    void paintCorner(QPainter& painter,int posX,int posY);//绘制拐角
    void mousePressEvent(QMouseEvent *event);//鼠标按压事件
    void setAudio();//设置音频
    void setChess();//设置棋子
    void setPos();//设置底层的棋盘数据
    void setFunctionStyle();//设置功能区样式
    void cmpPos(int &posX,int &posY);//计算鼠标点击点对应棋盘坐标
    void moveTo(int num,int posX,int posY);//移动棋子并修改底层数据
    bool judge(int moveId,int x,int y);//判断能否走棋
    void advance(Step* step);//前进一步
    void retreat(Step* step);//后退一步
    void setEnding();//游戏结束设置
    void userChange();//使用者转换函数
    void reFresh();//恢复棋盘，再来一把
    Ui::ChessBoard* getUi();//获取ui指针
public slots:
    void addTime();//计时功能
    void regretChess();//悔棋
private:
    Ui::ChessBoard *ui;
};
#endif // CHESSBOARD_H

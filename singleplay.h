#ifndef SINGLEPLAY_H
#define SINGLEPLAY_H

#include "chessboard.h"
#include <QTimer>
#include "ui_chessboard.h"

class SinglePlay : public ChessBoard
{
public:
    explicit SinglePlay(QWidget *parent = nullptr);
    int level=4;//人机计算步数
    int cmpScore();//计算局面分
    Step* getComputerMove();//获取计算机的走法
    void computerMove();//计算机走棋
    //为了开发双人对战的悔棋功能，将前进和后退函数移到了父类ChessBoard中
    void cmpStepSum(QVector<Step*>& stepVector,bool user);//计算所有可能的走法
    int cmpMaxScore(int level,int maxNum);//计算最大局面分
    int cmpMinScore(int level,int minnum);//计算最小局面分
    void mousePressEvent(QMouseEvent* event);//重写父类的鼠标按压事件
    void setEnding();//重写父类的游戏结束设置函数
    void setFunctionStyle();//重写父类的设施功能区样式函数
public slots:
    //不能给槽函数设置默认参数，在信号槽机制调度时，如果信号没有传递对应的参数，则该参数设置为0
    void regretChess();//悔棋
};

#endif // SINGLEPLAY_H

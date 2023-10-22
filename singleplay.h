#ifndef SINGLEPLAY_H
#define SINGLEPLAY_H

#include "chessboard.h"
#include <QVector>
#include "step.h"
#include <QTimer>

class SinglePlay : public ChessBoard
{
public:
    SinglePlay();
    int level=4;
    QVector<Step*> vector;//存储走棋步数
    int cmpScore();//计算局面分
    Step* getComputerMove();//获取计算机的走法
    void computerMove();//计算机走棋
    void advance(Step* step);//前进一步
    void retreat(Step* step);//后退一步
    void cmpStepSum(QVector<Step*>& stepVector,bool user);//计算所有可能的走法
    int cmpMaxScore(int level);//计算最大局面分
    int cmpMinScore(int level);//计算最小局面分
    void mousePressEvent(QMouseEvent* event);//重写父类的鼠标按压事件
    //void setEnding();
};

#endif // SINGLEPLAY_H

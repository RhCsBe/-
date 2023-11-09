#ifndef FORBIDCHESS_H
#define FORBIDCHESS_H

#include <QDialog>
#include <QButtonGroup>
#include "chess.h"

namespace Ui {
class ForbidChess;
}

class ForbidChess : public QDialog
{
    Q_OBJECT

public:
    explicit ForbidChess(Chess* chess,int** pos,QWidget *parent = nullptr);
    Chess* chess=nullptr;
    int **pos=nullptr;
    bool forbidden[30]={0};//按键状态数组
    QButtonGroup* chessGroup=nullptr;//按键组指针
    void resetForbidden();//将按键状态数组初始化
    void setChessGroup();//设置棋子多选按键组
    void setForbidden();//设置按键状态数组
    //在checkChess函数中重新设置pos指针
    void checkChess(int** pos);//检查棋子是否在被禁掉之前就已经死亡
    void forbid();//禁用选中的棋子
    ~ForbidChess();

private:
    Ui::ForbidChess *ui;
};

#endif // FORBIDCHESS_H

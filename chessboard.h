#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPainter>
#include "chess.h"
#include <QDebug>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class ChessBoard; }
QT_END_NAMESPACE

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();
    enum status{
        jiang,shi,xiang,ma,jv,pao,bing
    };
    int radius=25;
    Chess chess[32];
    int pos[90];
    int select=-1;
    void paintEvent(QPaintEvent *event);//绘图事件
    void paintBoard(QPainter& painter);//绘制棋盘
    void paintChess(QPainter& painter);//绘制棋子
    void mousePressEvent(QMouseEvent *event);//鼠标按压事件
    void setChess();//设置棋子
    void setPos();//设置底层的棋盘数据
    void cmpPos(int &posX,int &posY);//计算鼠标点击点对应棋盘坐标
    void moveTo(int num,int posX,int posY);//移动棋子并修改底层数据
private:
    Ui::ChessBoard *ui;
};
#endif // CHESSBOARD_H

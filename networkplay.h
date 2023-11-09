#ifndef NETWORKPLAY_H
#define NETWORKPLAY_H

#include "chessboard.h"
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QNetworkInterface>
#include <QTime>
#include <QThread>
#include "ui_chessboard.h"

//一个ip不能同时多次加入同一个组播，要使用两台电脑进行测试
class NetworkPlay : public ChessBoard
{
    //连接信号和槽函数不需要添加Q_OBJECT，但是使用signals要添加，否则编译器会报错
    Q_OBJECT

//警告：千万不要连校园网进行测试，这傻逼校园网不知道设置了什么东西，无法进行组播和广播通信
public:
    NetworkPlay();
    QHostAddress myAddress;//本机的IPV4地址
    QHostAddress otherAddress;//对方的IPV4地址
    int port=8086;//端口号
    QUdpSocket linkUdp;//通信的UDP套接字
    QTimer timer;//定时器
    int random_num1=0;//随机数1
    int random_num2=0;//随机数2
    Step step;//自己的走法
    void setMyAddress();//设置本机地址
    void setTimer();//设置定时器
    void setOtherAddress();//设置对方的地址
    void setUser();//设置User
    void setFunctionStyle();//重写父类的设施功能区样式函数
    void setEnding();//重写父类的结束设置函数
    void setStep(Step* temp);//设置走法
    void mousePressEvent(QMouseEvent *event);//重写父类的鼠标按压事件
    void sendStep();//发送走法
    Step shiftStep(char* str);//将对方的走法转换成自己棋盘数据对应的走法
    void userChange();//重写父类的userChange方法
    void beginGame();//完成开始游戏设置
    void reFresh();//重写父类的再来一把函数
    void clear();//退出游戏或者游戏结束，清除数据
    void leave();//通知对方你已退出当前游戏
signals:
    void showBeginning();
};

#endif // NETWORKPLAY_H

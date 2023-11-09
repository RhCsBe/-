#include "networkplay.h"

NetworkPlay::NetworkPlay()
{
    //linkUdp=new QUdpSocket(this);
    if(linkUdp.bind(QHostAddress::AnyIPv4,port))
        qDebug()<<"AA";
    //打开IO设备，QT6要设置，QT5好像不需要
    if(linkUdp.open(QIODevice::ReadWrite))
        qDebug()<<"YES";
    //设置功能区样式
    setFunctionStyle();
    //设置本地IP
    setMyAddress();
    //打印本地IP
    qDebug()<<"myAddress:"<<myAddress.toString();
    //设置定时器，以及后续的一系列匹配对手、设置user工作
    //setTimer();
    user=false;
    //解除chessBoard中为ending的nextOne绑定的处理函数
    disconnect(ending->getUi()->nextOne,&QPushButton::clicked,this,0);
    connect(ending->getUi()->nextOne,&QPushButton::clicked,this,[this](){this->clear();this->reFresh();ending->close();});
}

void NetworkPlay::setMyAddress()
{
    for(auto address:QNetworkInterface::allAddresses())//对于所有检测到的地址
    {
        //添加本地IPV4地址,剔除127.0.0.1
        if (address != QHostAddress::LocalHost && address.toIPv4Address())
            myAddress=address;
    }
}

void NetworkPlay::setTimer()
{
    //timer=new QTimer();
    //周期性往组播地址发送本地的IP地址，直到捕获别人的IP地址
    connect(&timer,&QTimer::timeout,this,[this](){
        QByteArray address=myAddress.toString().toUtf8();
        linkUdp.writeDatagram(address,QHostAddress("239.0.0.1"),port);
        //qDebug()<<myAddress.toString();
        //qDebug()<<"write";
    });
}

void NetworkPlay::setOtherAddress()
{
    //启动定时器，周期性发送组播信息
    //timer->start(500);
    if(linkUdp.joinMulticastGroup(QHostAddress("239.0.0.1")))
        //不了解为什么在这里使用会导致linkUdp的readyread信号无法触发，导致后点击的一方接收不到对方发送的Ip，必须要两个客户端同时点击才行，因此取消该方式的通知
        //QMessageBox::information(this,"提示","UDP已连接");
        qDebug()<<"JOIN";
    //启动定时器，周期性发送组播信息
    //一定要先加入组播，然后再发送数据报，否则无法触发readyRead信号，千万要记住，下次再错去博北找个楼跳了
    setTimer();
    timer.start(1000);
    //绑定readyRead信号和处理函数
    connect(&linkUdp,&QUdpSocket::readyRead,this,[this](){
        while(linkUdp.hasPendingDatagrams())
        {
            char str[1024]={0};
            QHostAddress address;
            quint16 senderPort;
            linkUdp.readDatagram(str,sizeof(str),&address,&senderPort);
            //qDebug()<<QString(str);
            //过滤掉自己发的信息
            if(address==myAddress||senderPort!=port)
            {
                continue;
            }
            otherAddress=QHostAddress(QString(str));
            //qDebug()<<"otherAddress:"<<otherAddress.toString();
            //linkUdp->writeDatagram(myAddress.toString().toUtf8(),otherAddress,port);
            //获取到别人的IP地址后退出组播
            //之前尝试过在singleShot里进行退出组播，但不知道为什么会导致无法接收到后续发送的随机数，代码能跑就行，别他妈瞎调
            linkUdp.leaveMulticastGroup(QHostAddress("239.0.0.1"));
            //解除linkUdp的所有信号绑定的槽函数
            disconnect(&linkUdp,0,this,0);
            //延时暂停定时器，防止未发送本地Ip就接收到他人IP的情况发生
            QTimer::singleShot(1000,this,[this](){
                timer.stop();
                //linkUdp.leaveMulticastGroup(QHostAddress("239.0.0.1"));
                qDebug()<<"otherAddress:"<<otherAddress.toString();
                getUi()->user->setText("随机");
                //嵌套设置，控制程序流程，使setUser函数一定发生在获取IP后
                setUser();
            });
        }
    });

    //下面这部分是样例拷贝过来的代码
//    if(linkUdp.joinMulticastGroup(QHostAddress("239.0.0.1")))
//        qDebug()<<"JOIN";
//    connect(&timer,&QTimer::timeout,this,[this](){
//        linkUdp.writeDatagram(myAddress.toString().toUtf8(),QHostAddress("239.0.0.1"),port);
//        //linkUdp.waitForReadyRead(100);
//    });
//    //    connect(&timer,&QTimer::timeout,this,[this](){
//    //        linkUdp.writeDatagram(myAddress.toString().toUtf8(),QHostAddress::Broadcast,port);
//    //    });
//    timer.start(1000);
//    connect(&linkUdp,&QUdpSocket::readyRead,this,[this](){
//        while(linkUdp.hasPendingDatagrams())
//        {
//            char str[1024]={0};
//            QHostAddress address;
//            quint16 senderPort;
//            linkUdp.readDatagram(str,sizeof(str),&address,&senderPort);
//            //if(QHostAddress(QString(str))!=myAddress)
//            //ui->textEdit->append(str);
//            qDebug()<<str;
//            if(address==myAddress||senderPort!=port)
//            {
//                continue;
//            }
//            otherAddress=QHostAddress(QString(str));
//            //qDebug()<<"otherAddress:"<<otherAddress.toString();
//            //linkUdp->writeDatagram(myAddress.toString().toUtf8(),otherAddress,port);
//            //获取到别人的IP地址后退出组播
//            //linkUdp->leaveMulticastGroup(QHostAddress("239.0.0.1"));
//            //解除linkUdp的所有信号绑定的槽函数
//            disconnect(&linkUdp,0,this,0);
//            //延时暂停定时器，防止未发送本地Ip就接收到他人IP的情况发生
//            QTimer::singleShot(1000,this,[this](){
//                timer.stop();
//                linkUdp.leaveMulticastGroup(QHostAddress("239.0.0.1"));
//            });
//        }
//    });
}

void NetworkPlay::setUser()
{
    //网络对战的双方的user都为false，根据生成的随机数决定谁先走
    //设置随机数种子
    std::srand(QTime::currentTime().msec());
    random_num1=std::rand();
    //连接readyRead信号和获取随机数处理函数
    connect(&linkUdp,&QUdpSocket::readyRead,this,[this](){
        char str[1024]={0};
        linkUdp.readDatagram(str,sizeof(str));
        random_num2=QString(str).toInt();
        qDebug()<<random_num2;
        if(random_num1>random_num2)
        {
            user=true;
            getUi()->user->setText("我方");
        }
        else
        {
            getUi()->user->setText("对方");
        }
        //解除绑定，确保该函数只触发一次
        disconnect(&linkUdp,0,this,0);
        //因为随机数处理函数要等待信号触发，将beginGame函数设置在这控制程序流程正确，只有设置完user后才会开始游戏准备设置
        QTimer::singleShot(1000,this,&NetworkPlay::beginGame);
        });
    //当前进程休眠1秒，保证对战双方都已处理完对方的IP，进入等待随机数环节
    //QThread::sleep(1);
    QTimer::singleShot(1000,this,[this](){
    QByteArray array=QString::number(random_num1).toUtf8();
    linkUdp.writeDatagram(array,otherAddress,port);
    });
}

void NetworkPlay::setFunctionStyle()
{
    //设置网络对战的功能区样式，以及禁用一些无关功能
    getUi()->pattern->setText("网络对战");
    //getUi()->user->setText("随机");
    //getUi()->level->setEnabled(false);
    getUi()->regret->setEnabled(false);
    getUi()->forbidChess->setEnabled(false);
}

void NetworkPlay::setEnding()
{
    if(chess[4].dead)
    {
        QPixmap pixmap(":/img/img/gamewin.jpg");
        ending->getUi()->result->setPixmap(pixmap.scaled(ending->getUi()->result->size(), Qt::KeepAspectRatio));
        gameWin->play();
    }
    else
    {
        QPixmap pixmap(":/img/img/gamelose.jpg");
        ending->getUi()->result->setPixmap(pixmap.scaled(ending->getUi()->result->size(), Qt::KeepAspectRatio));
        gameLose->play();
    }
    ending->exec();
}

void NetworkPlay::setStep(Step* temp)
{
    //每走一步就要记录走法
    step.moveId=temp->moveId;
    step.dx=temp->dx;
    step.dy=temp->dy;
    step.killId=temp->killId;
}

void NetworkPlay::mousePressEvent(QMouseEvent *event)
{
    //当前user不是自己时无法走棋
    if(!user)
        return;
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
                setStep(vector.back());//记录自己的走法
                moveChess->play();
                moveTo(select,x,y);
                if(judgment.judge_jiangjun(chess,user,pos))
                {
                    jiangJun->play();
                }
                if(judgment.judge_kill(chess[4],chess[27]))
                    setEnding();
                user=!user;
                userChange();//更换user
                sendStep();//发送自己的走法给对方
            }
            else
                return;
        }
    }
    //qDebug()<<user;
    update();
}

void NetworkPlay::sendStep()
{
    //因为utf-8传输负数时会出现数据错误的问题，所以要将setp的数据全部转化成字符传输，不能像样例那样直接用一个char变量记录一个数据
    char str[8];
    QString str1=QString::number(step.moveId);
    QString str2=QString::number(step.dx);
    QString str3=QString::number(step.dy);
    QString str4=QString::number(step.killId);
    str[0]=str1[0].toLatin1();
    str[1]=str1[1].toLatin1();
    if(step.dx>=0)
    {
        str[2]='0';
        str[3]=str2[0].toLatin1();
    }
    else
    {
        str[2]=str2[0].toLatin1();
        str[3]=str2[1].toLatin1();
    }
    if(step.dy>=0)
    {
        str[4]='0';
        str[5]=str3[0].toLatin1();
    }
    else
    {
        str[4]=str3[0].toLatin1();
        str[5]=str3[1].toLatin1();
    }
    if(step.killId<10&&step.killId!=-1)
    {
        str[6]='0';
        str[7]=str4[0].toLatin1();
    }
    else
    {
        str[6]=str4[0].toLatin1();
        str[7]=str4[1].toLatin1();
    }
//    str[0]=step.moveId;
//    str[1]=step.dx;
//    str[2]=step.dy;
//    str[3]=step.killId;
    //打印走法
    //qDebug()<<"send:"<<step.moveId<<"\t"<<step.dx<<"\t"<<step.dy<<"\t"<<step.killId;
    linkUdp.writeDatagram(QString(str).toUtf8(),otherAddress,port);
}

Step NetworkPlay::shiftStep(char* str)
{
//    int moveId=str[0];
//    int dx=str[1];
//    int dy=str[2];
//    int killId=str[3];
    QString str1="";
    QString str2="";
    QString str3="";
    QString str4="";
    str1+=str[0];
    str1+=str[1];
    str2+=str[2];
    str2+=str[3];
    str3+=str[4];
    str3+=str[5];
    str4+=str[6];
    str4+=str[7];
    int moveId=str1.toInt();
    int dx=str2.toInt();
    int dy=str3.toInt();
    int killId=str4.toInt();
    //为了优化游戏体验，要把对战双方都设置为红方，所以对于对方传过来的走法要进行镜像转换，换成黑方的走法
    moveId=31-moveId;
    dx=-dx;
    dy=-dy;
    if(killId!=-1)
        killId=31-killId;
    //打印走法
    //qDebug()<<"shift:"<<moveId<<"\t"<<dx<<"\t"<<dy<<"\t"<<killId;
    return Step(moveId,dx,dy,killId);
}

void NetworkPlay::userChange()
{
    if(user)
    {
        getUi()->user->setText("我方");
    }
    else
    {
        getUi()->user->setText("对方");
    }
}

void NetworkPlay::beginGame()
{
    //连接readyRead信号和走棋信息接收处理函数
    connect(&linkUdp,&QUdpSocket::readyRead,this,[this](){
        char str[8]={0};
        linkUdp.readDatagram(str,sizeof(str));
        if(QString(str)=="leave")
        {
            QMessageBox::information(this,"提示","对方已退出游戏");
            //不能直接调用返回按键的点击事件，否则你往对战方发送了一份数据报后，他也会给你发送一份数据报，当你在一次点击网络对战时
            //linkUdp会直接读取他发给你的那分份数据报，并尝试转换成QHostAddress,导致程序因此卡住
            //getUi()->returnBeginning->click();
            emit showBeginning();
            QTimer::singleShot(500,this,[this](){clear();close();});
            return;
        }
        Step temp=shiftStep(str);
        moveChess->play();
        advance(&temp);
        if(judgment.judge_jiangjun(chess,user,pos))
        {
            jiangJun->play();
        }
        if(judgment.judge_kill(chess[4],chess[27]))
            setEnding();
        user=!user;
        userChange();
        update();
    });
}

void NetworkPlay::reFresh()
{
    //重写父类的再来一把函数
    //恢复棋子
    this->setChess();
    //恢复棋盘数据
    this->setPos();
    //恢复禁用棋子状态数组
    forbidChess->resetForbidden();
    select=-1;
    user=false;
    getUi()->user->setText("匹配中");
    //获取对方IP
    this->setOtherAddress();
}

void NetworkPlay::clear()
{
    disconnect(&linkUdp,0,this,0);
    random_num1=0;
    random_num2=0;
    otherAddress.clear();
}

void NetworkPlay::leave()
{
    linkUdp.writeDatagram(QString("leave").toUtf8(),otherAddress,port);
}

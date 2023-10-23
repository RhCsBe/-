#include "singleplay.h"

SinglePlay::SinglePlay(QWidget *parent)
{
    setFunctionStyle();
}

int SinglePlay::cmpScore()
{
    int score[7]={10000,50,70,100,250,120,20};
    int sum=0;
    for(int i=0;i<16;i++)
    {
        if(chess[i].dead)
            continue;
        else
        {
            switch(chess[i].identity)
            {
            case status::jiang:
                sum+=score[0];
                break;
            case status::shi:
                sum+=score[1];
                break;
            case status::xiang:
                sum+=score[2];
                break;
            case status::ma:
                sum+=score[3];
                break;
            case status::jv:
                sum+=score[4];
                break;
            case status::pao:
                sum+=score[5];
                break;
            case status::bing:
                sum+=score[6];
                break;
            default:
                break;
            }
        }
    }
    for(int i=16;i<32;i++)
    {
        if(chess[i].dead)
            continue;
        else
        {
            switch(chess[i].identity)
            {
            case status::jiang:
                sum-=score[0];
                break;
            case status::shi:
                sum-=score[1];
                break;
            case status::xiang:
                sum+=score[2];
                break;
            case status::ma:
                sum-=score[3];
                break;
            case status::jv:
                sum-=score[4];
                break;
            case status::pao:
                sum-=score[5];
                break;
            case status::bing:
                sum-=score[6];
                break;
            default:
                break;
            }
        }
    }
    return sum;
}

Step* SinglePlay::getComputerMove()
{
    QVector<Step*> vector;
    cmpStepSum(vector,0);
//    for(int i=0;i<vector.size();i++)
//    {
//        qDebug()<<vector[i]->moveId<<"\t"<<vector[i]->dx<<"\t"<<vector[i]->dy<<"\t"<<vector[i]->killId;
//    }
    int maxScore=-100000;
    int score;
    Step* step=nullptr;
    Step* lastStep=nullptr;
    while(vector.size())
    {
        step=vector.front();
        vector.pop_front();
        advance(step);
        score=cmpMinScore(level-1,maxScore);
        retreat(step);
        if(score>maxScore)
        {
            maxScore=score;
            delete lastStep;
            lastStep=step;
        }
        else
        {
            delete step;
        }
    }
    return lastStep;
}

void SinglePlay::computerMove()
{
    Step* step=getComputerMove();
    moveChess->play();
    moveTo(step->moveId,chess[step->moveId].line+step->dx,chess[step->moveId].row+step->dy);
    vector.push_back(step);
    if(judgment.judge_jiangjun(chess,user,pos))
    {
        jiangJun->play();
    }
    if(judgment.judge_kill(chess[4],chess[27]))
        setEnding();
    user=!user;
    update();
}

void SinglePlay::cmpStepSum(QVector<Step *> &stepVector,bool user)
{
    int minimum,maximum;
    if(user)
    {
        minimum=16;
        maximum=32;
    }
    else
    {
        minimum=0;
        maximum=16;
    }
    for(int i=minimum;i<maximum;i++)
    {
        if(chess[i].dead)
            continue;
        else
        {
            for(int j=0;j<10;j++)
            {
                for(int k=0;k<9;k++)
                {
                    if(judge(i,k,j))
                        stepVector.push_back(new Step(i,k-chess[i].line,j-chess[i].row,pos[j][k]));
                }
            }
        }
    }
    //qDebug("\\\\");
}

int SinglePlay::cmpMaxScore(int level,int minNum)
{
    if(!level)
        return cmpScore();
    QVector<Step*> vector;
    cmpStepSum(vector,0);
    int maxScore=-100000;
    int score;
    while(vector.size())
    {
        Step* step=vector.front();
        vector.pop_front();
        advance(step);
        score=cmpMinScore(level-1,minNum);
        retreat(step);
        delete step;
        if(score>minNum)
        {
            for(auto item:vector)
            {
                delete item;
            }
            return score;
        }
        if(score>maxScore)
            maxScore=score;

    }
    return maxScore;
}

int SinglePlay::cmpMinScore(int level,int maxNum)
{
    if(!level)
        return cmpScore();
    QVector<Step*> vector;
    cmpStepSum(vector,1);
    int minScore=100000;
    int score;
    while(vector.size())
    {
        Step* step=vector.front();
        vector.pop_front();
        advance(step);
        score=cmpMaxScore(level-1,maxNum);
        retreat(step);
        delete step;
        if(score<maxNum)
        {
            for(auto item:vector)
            {
                delete item;
            }
            return score;
        }
        if(score<minScore)
            minScore=score;
    }
    return minScore;
}

void SinglePlay::mousePressEvent(QMouseEvent *event)
{
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
        if(pos[y][x]<16)
        {
            return;
        }
        select=pos[y][x];
        selectChess->play();
    }
    else
    {
        if(pos[y][x]>15)
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
                QTimer::singleShot(1000,this,SinglePlay::computerMove);
            }
            else
                return;
        }
    }
    update();
}

void SinglePlay::setEnding()
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

void SinglePlay::setFunctionStyle()
{
    disconnect(getUi()->regret,QPushButton::clicked,this,ChessBoard::regretChess);
    getUi()->pattern->setStyleSheet("color:red");
    getUi()->pattern->setText("人机对战");
    getUi()->regret->setEnabled(true);
    //为了避免突然中断导致程序崩溃或者底层数据错乱，所以使用队列连接方式
    connect(getUi()->regret,QPushButton::clicked,this,SinglePlay::regretChess,Qt::QueuedConnection);
}

void SinglePlay::regretChess()
{
    if(vector.empty())
        return;
    Step* step=nullptr;
    for(int i=0;i<2;i++)
    {
        step=vector.back();
        vector.pop_back();
        retreat(step);
        user=!user;
    }
    update();
}


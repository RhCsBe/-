#include "singleplay.h"

SinglePlay::SinglePlay()
{

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
        score=cmpMinScore(level-1);
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
    if(judgment.judge_jiangjun(chess,user,pos))
    {
        jiangJun->play();
    }
    user=!user;
    update();
}

void SinglePlay::advance(Step *step)
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

void SinglePlay::retreat(Step *step)
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

int SinglePlay::cmpMaxScore(int level)
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
        score=cmpMinScore(level-1);
        retreat(step);
        if(score>maxScore)
            maxScore=score;
        delete step;
    }
    return maxScore;
}

int SinglePlay::cmpMinScore(int level)
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
        score=cmpMaxScore(level-1);
        retreat(step);
        if(score<minScore)
            minScore=score;
        delete step;
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
                moveChess->play();
                moveTo(select,x,y);
                if(judgment.judge_jiangjun(chess,user,pos))
                {
                    jiangJun->play();
                }
                user=!user;
                QTimer::singleShot(1000,this,SinglePlay::computerMove);
            }
            else
                return;
        }
    }
    update();
}


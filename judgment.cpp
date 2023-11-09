#include "judgment.h"

Judgment::Judgment()
{

}

bool Judgment::judge_bing(const Chess& chess,int x,int y,int** pos)
{
    //不能自己吃自己
    if(chess.line==x&&chess.row==y)
        return false;
    //不能吃相同阵营的棋子
    if(chess.num>15&&pos[y][x]>15||chess.num<16&&pos[y][x]<16&&pos[y][x]!=-1)
        return false;
    if(chess.color)
    {
        if(chess.line==x&&chess.row==y)
            return false;
        if(pos[y][x]>15)
        {
            return false;
        }
        if(chess.row<5)
        {
            if(std::abs(chess.line-x)==1&&chess.row-y==0||chess.line-x==0&&chess.row-y==1)
                return true;
            else
                return false;
        }
        else
        {
            if(chess.row-y==1&&chess.line-x==0)
                return true;
            else
                return false;
        }
    }
    else
    {
        if(pos[y][x]<16&&pos[y][x]!=-1)
        {
            return false;
        }
        if(chess.row<5)
        {
            if(y-chess.row==1&&x-chess.line==0)
                return true;
            else
                return false;
        }
        else
        {
            if(std::abs(x-chess.line)==1&&y-chess.row==0||y-chess.row==1&&x-chess.line==0)
                return true;
            else
                return false;
        }
    }
}

bool Judgment::judge_pao(const Chess &chess, int x, int y, int **pos)
{
    //不能自己吃自己
    if(chess.line==x&&chess.row==y)
        return false;
    //不能吃相同阵营的棋子
    if(chess.num>15&&pos[y][x]>15||chess.num<16&&pos[y][x]<16&&pos[y][x]!=-1)
        return false;
    if(std::abs(x-chess.line)==0||std::abs(y-chess.row)==0)
    {
        int minimum,maximum;
        if(x-chess.line==0)
        {
            minimum=std::min(y,chess.row);
            maximum=std::max(y,chess.row);
            if(pos[y][x]==-1)
            {
                for(int i=minimum+1;i<maximum;i++)
                {
                    if(pos[i][x]!=-1)
                        return false;
                }
                return true;
            }
            else
            {
                int sum=0;
                for(int i=minimum+1;i<maximum;i++)
                {
                    if(pos[i][x]!=-1)
                        sum++;
                }
                if(sum==1)
                    return true;
                else
                    return false;
            }
        }
        if(y-chess.row==0)
        {
            minimum=std::min(x,chess.line);
            maximum=std::max(x,chess.line);
            if(pos[y][x]==-1)
            {
                for(int i=minimum+1;i<maximum;i++)
                {
                    if(pos[y][i]!=-1)
                    {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                int sum=0;
                for(int i=minimum+1;i<maximum;i++)
                {
                    if(pos[y][i]!=-1)
                        sum++;
                }
                if(sum==1)
                    return true;
                else
                    return false;
            }
        }
    }
    else
        return false;
}

bool Judgment::judge_jiang(const Chess &chess, int x, int y, int **pos)
{
    qDebug()<<"jiang";
    //不能自己吃自己
    if(chess.line==x&&chess.row==y)
        return false;
    //不能吃相同阵营的棋子
    if(chess.num>15&&pos[y][x]>15||chess.num<16&&pos[y][x]<16&&pos[y][x]!=-1)
        return false;
    if(chess.color)
    {
        //判断是否能飞将
        if(pos[y][x]==4)
        {
            for(int i=chess.row-1;i>=y;i--)
            {
                if(i==y)
                    return true;
                if(pos[i][x]!=-1)
                {
                    break;
                }
            }
        }
        //将不能走出九宫格
        if(x<3||x>5||y<7)
        {
            return false;
        }
        else
        {
            if(std::abs(chess.line-x)==1&&chess.row-y==0||std::abs(chess.row-y)==1&&chess.line-x==0)
                return true;
            else
                return false;
        }
    }
    else
    {
        //判断是否能飞将
        if(pos[y][x]==27)
        {
            for(int i=chess.row+1;i<=y;i++)
            {
                if(i==y)
                    return true;
                if(pos[i][x]!=-1)
                {
                    break;
                }
            }
        }
        //将不能走出九宫格
        if(x<3||x>5||y>2)
        {
            return false;
        }
        else
        {
            if(std::abs(chess.line-x)==1&&chess.row-y==0||std::abs(chess.row-y)==1&&chess.line-x==0)
                return true;
            else
                return false;
        }
    }
}

bool Judgment::judge_shi(const Chess &chess, int x, int y, int **pos)
{
    //不能自己吃自己
    if(chess.line==x&&chess.row==y)
        return false;
    //不能吃相同阵营的棋子
    if(chess.num>15&&pos[y][x]>15||chess.num<16&&pos[y][x]<16&&pos[y][x]!=-1)
        return false;
    if(chess.color)
    {
        if(x<3||x>5||y<7)
        {
            return false;
        }
        else
        {
            if(std::abs(chess.line-x)==1&&std::abs(chess.row-y)==1)
                return true;
            else
                return false;
        }
    }
    else
    {
        if(x<3||x>5||y>2)
        {
            return false;
        }
        else
        {
            if(std::abs(chess.line-x)==1&&std::abs(chess.row-y)==1)
                return true;
            else
                return false;
        }
    }
}

bool Judgment::judge_xiang(const Chess &chess, int x, int y, int **pos)
{
    //不能自己吃自己
    if(chess.line==x&&chess.row==y)
        return false;
    //不能吃相同阵营的棋子
    if(chess.num>15&&pos[y][x]>15||chess.num<16&&pos[y][x]<16&&pos[y][x]!=-1)
        return false;
    if(chess.color)
    {
        if(y<5)
        {
            return false;
        }
        else
        {
            int dx=x-chess.line;
            int dy=y-chess.row;
            if(std::abs(dx)==2&&std::abs(dy)==2&&pos[chess.row+dy/2][chess.line+dx/2]==-1)
                return true;
            else
                return false;
        }
    }
    else
    {
        if(y>4)
        {
            return false;
        }
        else
        {
            int dx=x-chess.line;
            int dy=y-chess.row;
            if(std::abs(dx)==2&&std::abs(dy)==2&&pos[chess.row+dy/2][chess.line+dx/2]==-1)
                return true;
            else
                return false;
        }
    }
}

bool Judgment::judge_ma(const Chess &chess, int x, int y, int **pos)
{
    //不能自己吃自己
    if(chess.line==x&&chess.row==y)
        return false;
    //不能吃相同阵营的棋子
    if(chess.num>15&&pos[y][x]>15||chess.num<16&&pos[y][x]<16&&pos[y][x]!=-1)
        return false;
    int dx=x-chess.line;
    int dy=y-chess.row;
    if(std::abs(dx)==1&&std::abs(dy)==2||std::abs(dx)==2&&std::abs(dy)==1)
    {
        if(std::abs(dx)==1)
        {
            if(pos[chess.row+dy/2][chess.line]==-1)
                return true;
            else
                return false;
        }
        else
        {
            if(pos[chess.row][chess.line+dx/2]==-1)
                return true;
            else
                return false;
        }
    }
    else
        return false;
}

bool Judgment::judge_jv(const Chess &chess, int x, int y, int **pos)
{
    //不能自己吃自己
    if(chess.line==x&&chess.row==y)
        return false;
    //不能吃相同阵营的棋子
    if(chess.num>15&&pos[y][x]>15||chess.num<16&&pos[y][x]<16&&pos[y][x]!=-1)
        return false;
    if(x-chess.line==0||y-chess.row==0)
    {
        int minimum,maximum;
        if(x-chess.line==0)
        {
            minimum=std::min(y,chess.row);
            maximum=std::max(y,chess.row);
            for(int i=minimum+1;i<maximum;i++)
            {
                if(pos[i][x]!=-1)
                    return false;
            }
            return true;
        }
        if(y-chess.row==0)
        {
            minimum=std::min(x,chess.line);
            maximum=std::max(x,chess.line);
            for(int i=minimum+1;i<maximum;i++)
            {
                if(pos[y][i]!=-1)
                {
                    return false;
                }
            }
            return true;
        }
    }
    else
        return false;
}

bool Judgment::judge_kill(const Chess &chess1, const Chess &chess2)
{
    if(chess1.dead||chess2.dead)
        return true;
    else
        return false;
}

bool Judgment::judge_jiangjun(const Chess *chess, bool user, int **pos)
{
    int minimum,maximum,target;
    if(user)
    {
        minimum=16;
        maximum=32;
        target=4;
    }
    else
    {
        minimum=0;
        maximum=16;
        target=27;
    }
    for(int i=minimum;i<maximum;i++)
    {
        if(chess[i].dead)
            continue;
        switch(chess[i].identity)
        {
        case 0:
            if(judge_jiang(chess[i],chess[target].line,chess[target].row,pos))
                return true;
            break;
        case 1:
            if(judge_shi(chess[i],chess[target].line,chess[target].row,pos))
                return true;
            break;
        case 2:
            if(judge_xiang(chess[i],chess[target].line,chess[target].row,pos))
                return true;
            break;
        case 3:
            if(judge_ma(chess[i],chess[target].line,chess[target].row,pos))
                return true;
            break;
        case 4:
            if(judge_jv(chess[i],chess[target].line,chess[target].row,pos))
                return true;
            break;
        case 5:
            if(judge_pao(chess[i],chess[target].line,chess[target].row,pos))
                return true;
            break;
        case 6:
            if(judge_bing(chess[i],chess[target].line,chess[target].row,pos))
                return true;
            break;
        default:
            break;
        }
    }
    return false;
}

#include "judgment.h"

Judgment::Judgment()
{

}

bool Judgment::judge_bing(Chess& chess,int x,int y,int** pos)
{
    if(chess.color)
    {
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

bool Judgment::judge_pao(Chess &chess, int x, int y, int **pos)
{
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

bool Judgment::judge_jiang(Chess &chess, int x, int y, int **pos)
{
    if(chess.color)
    {
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

bool Judgment::judge_shi(Chess &chess, int x, int y, int **pos)
{
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

bool Judgment::judge_xiang(Chess &chess, int x, int y, int **pos)
{
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

bool Judgment::judge_ma(Chess &chess, int x, int y, int **pos)
{
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

bool Judgment::judge_jv(Chess &chess, int x, int y, int **pos)
{
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

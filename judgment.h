#ifndef JUDGMENT_H
#define JUDGMENT_H
#include "chess.h"
#include <cmath>
#include <QDebug>

class Judgment
{
public:
    Judgment();
    bool judge_bing(const Chess& chess,int x,int y,int** pos);
    bool judge_pao(const Chess& chess,int x,int y,int** pos);
    bool judge_jiang(const Chess& chess,int x,int y,int** pos);
    bool judge_shi(const Chess& chess,int x,int y,int** pos);
    bool judge_xiang(const Chess& chess,int x,int y,int** pos);
    bool judge_ma(const Chess& chess,int x,int y,int** pos);
    bool judge_jv(const Chess& chess,int x,int y,int** pos);
    bool judge_kill(const Chess& chess1,const Chess& chess2);
    bool judge_jiangjun(const Chess* chess,bool user,int** pos);
};

#endif // JUDGMENT_H

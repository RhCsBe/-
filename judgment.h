#ifndef JUDGMENT_H
#define JUDGMENT_H
#include "chess.h"
#include <cmath>
#include <QDebug>

class Judgment
{
public:
    Judgment();
    bool judge_bing(Chess& chess,int x,int y,int** pos);
    bool judge_pao(Chess& chess,int x,int y,int** pos);
    bool judge_jiang(Chess& chess,int x,int y,int** pos);
    bool judge_shi(Chess& chess,int x,int y,int** pos);
    bool judge_xiang(Chess& chess,int x,int y,int** pos);
    bool judge_ma(Chess& chess,int x,int y,int** pos);
    bool judge_jv(Chess& chess,int x,int y,int** pos);
};

#endif // JUDGMENT_H

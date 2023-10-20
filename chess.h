#ifndef CHESS_H
#define CHESS_H


class Chess
{
public:
    Chess();
    int row;
    int line;
    int num;
    bool color;
    bool dead=false;
    int identity;
    void moveTo(int x,int y);
};

#endif // CHESS_H

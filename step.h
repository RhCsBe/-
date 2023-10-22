#ifndef STEP_H
#define STEP_H


class Step
{
public:
    Step();
    Step(int moveId,int dx,int dy,int killId);
    int moveId;
    int dx;
    int dy;
    int killId;
};

#endif // STEP_H

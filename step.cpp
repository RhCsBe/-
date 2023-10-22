#include "step.h"

Step::Step()
{

}

Step::Step(int moveId, int dx, int dy, int killId)
{
    this->moveId=moveId;
    this->dx=dx;
    this->dy=dy;
    this->killId=killId;
}

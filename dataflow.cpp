#include "dataflow.h"



void Dataflow::getLandpt(double &x, double &y, double &z)
{
    x = landptx;
    y = landpty;
    z = landptz;

}


void Dataflow::getActionpose(double &x, double &y, double &z)
{
    x = action_nx;
    y = action_ny;
    z = action_nz;

}

void Dataflow::getActionvel(double &x, double &y, double &z)
{
    x = action_vx;
    y = action_vy;
    z = action_vz;

}

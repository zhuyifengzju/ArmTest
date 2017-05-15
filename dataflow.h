#ifndef DATAFLOW_H
#define DATAFLOW_H

class Dataflow
{
  public:

    void getLandpt(double &x, double &y, double &z);
    void getActionpose(double &x, double &y, double &z);
    void getActionvel(double &x, double &y, double &z);

  private:
    double landptx, landpty, landptz;
    double action_nx, action_ny, action_nz;
    double action_vx, action_vy, action_vz;





};






#endif // DATAFLOW_H

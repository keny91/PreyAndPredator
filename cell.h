#ifndef CELL_H
#define CELL_H


#include <vector>
#include <QDebug>
#include <QTime>
#include <windows.h>
//#include <grid.h>

using namespace std;

class cell
{
public:
    cell();
    ~cell();
    int state;
    int PropagationProbability, InfectedCellsInNeighboorhood,HealthyCellsInNeighboorhood;
    int TurnsInfected,  LifeSpanTurns, RollLimit;
    int* color;
    void GetsInfectedRoll();
    void SetInfected();
    void SetDeath();
    void SetRegular();
    void IncreaseInfection();
//    void PropagateInfection();
    void Createneighbourdhood(); // to avoid reading 1 by one
    void CountInfectedNeighbourhood(int count);

};

#endif // CELL_H

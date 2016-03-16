#ifndef PREYCELL_H
#define PREYCELL_H

#include "cell.h"

class PreyCell: public cell
{
public:
    PreyCell();
    void GetsInfectedRoll();
    void SetInfected();
    void SetDeath();
    void SetRegular();
    void IncreaseInfection();
    void Createneighbourdhood(); // to avoid reading 1 by one
    void CountInfectedNeighbourhood(int count);

//private:


};

#endif // PREYCELL_H

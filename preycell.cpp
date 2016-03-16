#include "preycell.h"


 PreyCell::PreyCell():cell()
{

    TurnsInfected = 0;
    LifeSpanTurns = 6;
    RollLimit = 8;
    InfectedCellsInNeighboorhood = 0;
    PropagationProbability = 8;
    color = new int[2]; //RGB
    state = 0;
    //SetInfected();
    TurnsInfected = 0;
    color[0]=0;
    color[1]=0;
    color[2]=200;
}


 void PreyCell::SetInfected(){


 }

//void PreyCell::SetDeath(){


//}


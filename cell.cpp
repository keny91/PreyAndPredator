#include "cell.h"


/*-----Process Order:
1st-> Check&Count STATUSW around a regular cell
2nd-> Breed.
3rd-> Die
4th-> Recount
-> Next Round (next generation)
----------------------------*/



/*-----Possible Status:
0->Empty Cell
1->Prey Cell
2->Predator Cell
----------------------------*/


cell::cell()
{
//    state = 0; //Empty
//    TurnsInfected = 0;
//    LifeSpanTurns = 6;
//    RollLimit = 8;
//    InfectedCellsInNeighboorhood = 0;
//    PropagationProbability = 8;
//    color = new int[2]; //RGB
//    color[0] = 0;
//    color[1] = 0;
//    color[2] = 0;

    SetEmpty();

}


void cell::SetEmpty(){
    status = 0;
    age = -1;
    BreedingAge = -1;
    OldAge = -1;
    BreedingNeighboursRequired = 4;
    BreedingNeighboursRequiredOnAge = 3;
    RandomDeathProbability = 0;
    RollLimit = 0;
    color = new int[2]; //RGB
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;

    //Neighbourhood operations
    predatorsInNeighbourhood = 0;
    preyInNeighbourhood = 0;
    maturePreyInNeighbourhood = 0;
    maturePredatorInNeighbourhood = 0;
    EmptyInNeighbourhood = 0;
}

void cell::SetPredator(){
    age = 1;  // original age for sharks is 1
    BreedingAge = 3;
    OldAge = 20;
    status = 2;
    BreedingNeighboursRequired = 4;
    BreedingNeighboursRequiredOnAge = 3;
    RandomDeathProbability = 1/32;
    RollLimit = 32;
    color = new int[2]; //RGB
    color[0] = 200;
    color[1] = 30;
    color[2] = 30;

    //Neighbourhood operations
    predatorsInNeighbourhood = 0;
    preyInNeighbourhood = 0;
    maturePreyInNeighbourhood = 0;
    maturePredatorInNeighbourhood = 0;
    EmptyInNeighbourhood = 0;
}

void cell::SetPrey(){
    status = 1;
    age = 1;
    BreedingAge = 2;
    BreedingNeighboursRequired = 4;
    BreedingNeighboursRequiredOnAge = 3;
    OldAge = 10;
    RandomDeathProbability = 0;
    RollLimit = 0;
    color = new int[2]; //RGB
    color[0] = 255;
    color[1] = 255;
    color[2] = 0;

    //Neighbourhood operations
    predatorsInNeighbourhood = 0;
    preyInNeighbourhood = 0;
    maturePreyInNeighbourhood = 0;
    maturePredatorInNeighbourhood = 0;
    EmptyInNeighbourhood = 0;
}

cell::~cell()
{

    //delete color;
    //qDebug()<< "Cell Destructor Call";
    delete this;
}




/*---------------------------
Prey Death: 8 neighbours == prey || 5<= neighbours are predators || OldAge<=Age
Predator Death:   6 or more neighbours are predators && prey = 0 || Random chance || OldAge<=Age

Random death is
----------------------------*/
void cell::Dies(int r){

    // Case: 1 predator
    if(status == 2){
        if((predatorsInNeighbourhood>=6 && preyInNeighbourhood == 0))
            SetEmpty();
        else if(age>=OldAge)
            SetEmpty();
        else if(GetsRandomDeathRoll(r,RollLimit))
            SetEmpty();
        else
            IncreaseAge(1);
        }


    // Case: 2 prey
    else if(status == 1){
        if((predatorsInNeighbourhood>=5 || preyInNeighbourhood == 8))
            SetEmpty();
        else if(age>=OldAge)
            SetEmpty();
        else
            IncreaseAge(1);
    }
}


/*---------------------------
IncreaseAge:  age + unit
----------------------------*/
void cell::IncreaseAge(int generations){
    age = generations +age;
}


/*---------------------------
Breed:  same species in neigbourhoods >= 4
----------------------------*/
void cell::Breed(){
    if(status == 0){  // Only if Cell is Empty
        // Case: 1 predator
        if(maturePreyInNeighbourhood >= BreedingNeighboursRequiredOnAge &&  preyInNeighbourhood >=BreedingNeighboursRequired && predatorsInNeighbourhood<4){
//           qDebug() << "set prey";
//           qDebug() << maturePreyInNeighbourhood;
           SetPrey();
        }
        // Case: 2 prey
        else if(maturePredatorInNeighbourhood >= BreedingNeighboursRequiredOnAge &&  predatorsInNeighbourhood >=BreedingNeighboursRequired && preyInNeighbourhood<4){
           SetPredator();
        }
    }

}


/*---------------------------
Check Status functions:  returns True if the type of cell has a correspondance
----------------------------*/
bool cell::isPredator(){
    if(status==2)
        return true;
    else
        return false;

    return (status ==2);
}
bool cell::isPrey(){
    if(status==1)
        return true;
    else
        return false;
}
bool cell::isEmpty(){
    if(status==0)
        return true;
    else
        return false;
}




//*---------------------------
//GetsRandomDeathRoll:
//    Rolls a dice. If we get over the set probability TH, returns true.
//----------------------------*/

bool cell::GetsRandomDeathRoll(int r, int rollLim){

    QTime now = QTime::currentTime();
    qsrand(now.msec()+r);
    r++;
    int roll = qrand()% RollLimit + 1;
    //        qDebug()<< "RollLimit: " << RollLimit ;
    //        qDebug()<< "Roll: " << roll;
    //            Sleep((1)); //WAIT FOR 1 ms to generate a new seed
    if(r >= 30000)  //Reset randSeed
        r=0;

    if(roll >= RollLimit)
        return true;
    else
        return false;

    return false;

}


//*IncreaseInfection: ---------------------------

//----------------------------------*/
//void cell::IncreaseInfection(){

//    if(state == 1){
//        TurnsInfected++;

//        if (TurnsInfected>LifeSpanTurns){  //dies
//            SetDeath();
//            TurnsInfected = 0;
//        }
//    }

//}




///*---------------------------

//----------------------------*/
//void cell::SetDeath(){
//    state = 2;
//    TurnsInfected = 0;
//    color[0] = 10;
//    color[1] = 10;
//    color[2] = 10;
//}



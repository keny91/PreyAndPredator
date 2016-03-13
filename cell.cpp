#include "cell.h"


/*-----Process Order:
1st-> Check&Count infections around a regular cell
2nd-> Roll given the infections around & Set New Infections.
3rd-> INFECTIONS get worse (originated this turn wont increase) ->death?
4th-> Recount regular
-> Next Round
----------------------------*/



/*-----Possible States:
0->Regular Cell
1->Under Infection
2->Consumed / Unifectable
----------------------------*/


cell::cell()
{
    state = 0;
    TurnsInfected = 0;
    LifeSpanTurns = 6;
    RollLimit = 8;
    InfectedCellsInNeighboorhood = 0;
    PropagationProbability = 8;
    color = new int[2]; //RGB
    color[0] = 130;
    color[1] = 130;
    color[2] = 130;

}


cell::~cell()
{
    //delete color;
    //qDebug()<< "Cell Destructor Call";
    delete this;
}

/*---------------------------
GetsInfectedRoll:
    Rolls a dice. If we get over the set probability TH, the cell gets infected.
----------------------------*/

void cell::GetsInfectedRoll(){
    if(state == 0 && InfectedCellsInNeighboorhood>0){
        QTime now = QTime::currentTime();
        qsrand(now.msec());

        int roll = qrand()% RollLimit + 1;
        Sleep((1)); //WAIT FOR 1 ms to generate a new seed

//        qDebug()<< "RollLimit: " << RollLimit ;
//        qDebug()<< "Roll: " << roll*InfectedCellsInNeighboorhood;


        if (roll*InfectedCellsInNeighboorhood >= RollLimit)
                    SetInfected();


//        if (InfectedCellsInNeighboorhood > 0)
//            SetInfected();
    }
}


/*IncreaseInfection: ---------------------------

----------------------------------*/
void cell::IncreaseInfection(){

    if(state == 1){
        TurnsInfected++;

        if (TurnsInfected>LifeSpanTurns){  //dies
            SetDeath();
            TurnsInfected = 0;
        }
    }

}





/*---------------------------
CountInfectedNeighbourhood:
    Rolls a dice. If we get over the set probability TH, the cell gets infected.
----------------------------*/

void cell::CountInfectedNeighbourhood(int count){
    if(state == 0){
        InfectedCellsInNeighboorhood = count;
    }
}



/*---------------------------

----------------------------*/
void cell::SetInfected(){
    state = 1;
    color[0] = 230;
    color[1] = 20;
    color[2] = 20;
}


/*---------------------------

----------------------------*/
void cell::SetRegular(){
    state = 0;
    TurnsInfected = 0;
    color[0] = 130;
    color[1] = 130;
    color[2] = 130;
}


/*---------------------------

----------------------------*/
void cell::SetDeath(){
    state = 2;
    TurnsInfected = 0;
    color[0] = 10;
    color[1] = 10;
    color[2] = 10;
}



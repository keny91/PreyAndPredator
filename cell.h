#ifndef CELL_H
#define CELL_H


#include <vector>
#include <QDebug>
#include <QTime>
#include <windows.h>
//#include "preycell.h"

//#include <grid.h>

using namespace std;

class cell
{
public:
    cell();
    ~cell();


    int age;
    int BreedingAge;
    int OldAge;
    int BreedingNeighboursRequired;
    int BreedingNeighboursRequiredOnAge;
    int status;
    double RandomDeathProbability;
    int RollLimit;
    int* color;

    //Neighbourhood operations
    int predatorsInNeighbourhood;
    int preyInNeighbourhood;
    int maturePreyInNeighbourhood;
    int maturePredatorInNeighbourhood;
    int EmptyInNeighbourhood;




    void SetPredator();
    void SetPrey();
    void SetEmpty();
    void SetNull();

    //CheckType
    bool isPredator();
    bool isPrey();
    bool isEmpty();

    bool isOld(int age);

    // self operations
    void Dies(int r);
    void IncreaseAge(int generation);
    void Breed();
    void getOlder(); // = increaseInfection
    bool GetsRandomDeathRoll(int r);
    void CopyCell(cell* theNewCell);



};

#endif // CELL_H

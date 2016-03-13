#ifndef GRID_H
#define GRID_H


#include "cell.h"
#include <iostream>
#include <QDebug>

//using namespace std;

//class cell;

class grid
{
public:

    int rowCount, colCount;
    int turnsCount;
    int CountLife, CountDeath, CountInfected;
    int neighbourhoodSize;
    int cellsDeleted; //DEBUG
    cell **theGrid;
    void InitGrid();
    void NextTurn();
    void CountCells();
    void CountStatusInNeighbourdhoods(int thisCellStatus, int theStatusUnderCount);
    grid(int row, int col);
    grid();

    ~grid();

};

#endif // GRID_H

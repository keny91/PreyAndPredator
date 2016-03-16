#ifndef GRID_H
#define GRID_H


#include "preycell.h"
//#include "cell.h"

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
    PreyCell * trycell;

    void InitGrid();
    void PopulateGrid(int type, int number);
    void NextTurn();
    void CountCells();
    void CountStatusInNeighbourdhoods(int thisCellStatus, int theStatusUnderCount);
    grid(int row, int col);
    grid();

    ~grid();

};

#endif // GRID_H

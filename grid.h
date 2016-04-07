#ifndef GRID_H
#define GRID_H



#include "cell.h"
#include <QTime>
#include <windows.h>
#include <iostream>
#include <QDebug>



using namespace std;

//class cell;

class grid
{
public:

    int rowCount, colCount;
    int turnsCount;
    int CountEmpty, CountPrey, CountPredator;
    int neighbourhoodSize;
    int cellsDeleted; //DEBUG
    int randSeed;

    cell **theGrid;
//    PreyCell * trycell;

    void InitGridWithStandardCells(boolean includeGhostCols = false);
    void PopulateGrid(int type, int number);
    void NextTurn();
    void CountCells();
    void CountStatusInNeighbourdhoods(boolean includeGhostCols = false);
    grid(int row, int col);
    grid();

    ~grid();

};

#endif // GRID_H



//#ifndef MINIGRID_H
//#define MINIGRID_H


//class MiniGrid : public grid
//{
//public:
//    MiniGrid();
//    MiniGrid(int col,int row );

//    void setTopNull();
//    void setBotNull();
//    void setLeftNull();
//    void setRightNull();

//};

//#endif // MINIGRID_H

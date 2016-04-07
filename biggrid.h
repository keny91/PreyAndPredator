#ifndef BIGGRID_H
#define BIGGRID_H

#include "minigrid.h"

class BigGrid
{
public:
    BigGrid();
    BigGrid(int X, int NCols, int NRows);
    void InitBigGrid();
    void SetNullGhostCells();
    void FillGhostCells();
    void NextTurnBigGrid();
    void CountCellsBigGrid();
    int numCols, numRows, elementsTotal;
    int CountPredator, CountPrey, CountEmpty, turnsCount;
    MiniGrid * multiGrid;
};

#endif // BIGGRID_H

#ifndef BIGGRID_H
#define BIGGRID_H

#include "minigrid.h"
#include <omp.h>
#include <time.h>

class BigGrid
{
public:
    BigGrid();
    BigGrid(int X, int NCols, int NRows);
    ~BigGrid();
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

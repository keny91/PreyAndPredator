#ifndef BIGGRID_H
#define BIGGRID_H

#include "minigrid.h"

class BigGrid
{
public:
    BigGrid();
    BigGrid(int X, int NCols, int NRows);
    int numCols, numRows, elementsTotal;
    MiniGrid * multiGrid;
};

#endif // BIGGRID_H

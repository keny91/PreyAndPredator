#ifndef MINIGRID_H
#define MINIGRID_H

#include "grid.h"

class MiniGrid : public grid
{
public:
    MiniGrid();
    MiniGrid(int col,int row );

    void setTopNull();
    void setBotNull();
    void setLeftNull();
    void setRightNull();

};

#endif // MINIGRID_H
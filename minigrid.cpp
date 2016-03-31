#include "minigrid.h"
//#include "grid.h"

MiniGrid::MiniGrid()
{

}


/*---------------------------
CONSTRUCTORS; default grid 100x100
----------------------------*/

MiniGrid:: MiniGrid(int col = 100,int row = 100){
    randSeed=0;
    CountEmpty=0;
    CountPredator =0;
    CountPrey = 0;
    rowCount=row+2;
    colCount=col+2;
    turnsCount = 0;
    cellsDeleted = 0;
    neighbourhoodSize =1;
    theGrid = new cell*[colCount];
    for(int i = 0;i<colCount; i++){
        theGrid[i]= new cell[rowCount];

    }

}




/*SetNullX: ---------------------------
    Depending on the selected border,
    we initilized all cells to be NULL
    Null Cells have no functionality
----------------------------------*/

void MiniGrid::setTopNull(){

    for(int i = 0; i< colCount; i++)
        theGrid[0][i].SetNull();

}

void MiniGrid::setBotNull(){

    for(int i = 0; i< colCount; i++)
        theGrid[rowCount-1][i].SetNull();

}


void MiniGrid::setLeftNull(){

    for(int i = 0; i< rowCount; i++)
        theGrid[i][0].SetNull();

}

void MiniGrid::setRightNull(){

    for(int i = 0; i< rowCount; i++)
        theGrid[i][colCount-1].SetNull();

}

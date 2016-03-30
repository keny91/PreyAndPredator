#include "minigrid.h"
//#include "grid.h"

MiniGrid::MiniGrid()
{

}


MiniGrid:: MiniGrid(int col,int row ){
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



void MiniGrid::setTopNull(){

    for(int i = 0; i< colCount; i++)
        theGrid[0][i].SetNull();

}

void MiniGrid::setBotNull(){



}


void MiniGrid::setLeftNull(){



}

void MiniGrid::setRightNull(){



}

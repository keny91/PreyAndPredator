#include "minigrid.h"
//#include "grid.h"

MiniGrid::MiniGrid()
{

}


/*---------------------------
CONSTRUCTORS; default grid 100x100
----------------------------*/

MiniGrid:: MiniGrid(int col,int row,int Xcoor, int General){
    indexX = Xcoor;
//    indexY = Ycoor;
    indexGeneral = General;
    randSeed=0;
    CountEmpty=0;
    CountPredator =0;
    CountPrey = 0;
    rowCount=row;
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

    qDebug() << "TOP";
    for(int i = 0; i< rowCount; i++)
        theGrid[0][i].SetNull();

}

void MiniGrid::setBotNull(){

    qDebug() << "BOT";
    for(int i = 0; i< rowCount; i++)
        theGrid[colCount-1][i].SetNull();

}


void MiniGrid::setLeftNull(){

    qDebug() << "LEFT";
    for(int i = 0; i< colCount; i++){
//        qDebug() << i;
        theGrid[i][0].SetNull();
    }
}

void MiniGrid::setRightNull(){

    qDebug() << "RIGHT";
    for(int i = 0; i< colCount; i++)
        theGrid[i][rowCount-1].SetNull();

}

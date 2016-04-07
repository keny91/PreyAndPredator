#include "biggrid.h"

BigGrid::BigGrid()
{

}

/*CONSTRUCTOR: ---------------------------

----------------------------------*/
BigGrid::BigGrid(int X, int NCols, int NRows){

    int count = 0;

//    qDebug()<< "WITH Y";
    multiGrid = new MiniGrid[X];
    numCols = X;
    for(int n = 0; n < X; n++){
        //                qDebug() <<
//        qDebug()<< "Reached  " << count;
        //                qDebug()<< m << "Reached  " << n;
        MiniGrid * aGrid = new MiniGrid(NCols,NRows , n, count);
//        qDebug() <<"n=" << n;

        // This is specialized in an only COL distribution
        if(n==0  && X > 1){
//            qDebug() << "Firstate";
            aGrid->setLeftNull();
//            qDebug() << "SecondState";
//            qDebug()<< "Reached EndFirstate ";
        }
        else if( n == X-1 && X > 1){
//             qDebug() << "SecondState";
            aGrid->setRightNull();
//            qDebug()<< "Reached END ";

        }

//        if(m==0 && Y > 1){
//            qDebug()<< "Reached  " << "a";
//            aGrid->setTopNull();
//            qDebug()<< "Reached  " << "b";
//        }
//        else if(m==Y-1&& Y > 1){
//            qDebug()<< "Reached END ";
//            aGrid->setBotNull();
//        }

//        qDebug()<< "Reached 102 ";
        multiGrid[n] = *aGrid;
//        qDebug()<< "Reached 3 ";
        count ++;

    }





}


/*SetNullGhostCells: ---------------------------
Using the function "InitGridWithStandardCells" from
the
----------------------------------*/
void BigGrid::SetNullGhostCells(){

    for(int n = 0; n < numCols; n++){
        if(n==0  && numCols > 1){
//            qDebug() << "Firstate";
            multiGrid[n].setLeftNull();

        }
        else if( n == numCols-1 && numCols > 1){

            multiGrid[n].setRightNull();

        }
    }

}


/*InitBigGrid: ---------------------------
Using the function "InitGridWithStandardCells" from
the
----------------------------------*/
void BigGrid::InitBigGrid(){

    for(int i = 0; i < numCols; i++){
        multiGrid[i].InitGridWithStandardCells(true);
    }

}


/*FillGhostCells: ---------------------------
ONLY DURING INITIALIZATION.
next time the ghost cells should be filled with MPI
----------------------------------*/
void BigGrid::FillGhostCells(){

    for(int block = 0; block< numCols; block++){

        for(int i = 0; i<miniBlockWidth; i++){
            for(int j =0;j < height; j++){



                    for(int j = 0;j<multiGrid[block].rowCount; j++){
                        // Get data from the left
                        if(block>0){ //block!=0
                            multiGrid[block].theGrid[0][j] = multiGrid[block-1].theGrid[100][j];
                        }
                        // Get data from the right
                        if(block<numCols-1){  // block!=numCols-1
                            multiGrid[block].theGrid[101][j] = multiGrid[block+1].theGrid[1][j];
                        }

                    }

                // GetRight


            }
        }


    }

}




/*NextTurnBigGrid: ---------------------------
Does all the respective calculations for every minigrid contained
THREADS ACT HERE, ALSO MPI

----------------------------------*/
void BigGrid::NextTurnBigGrid(){

    int countTheCols, countTheRows;

    for(int block = 0; block< numCols; block++){

        multiGrid[block].CountStatusInNeighbourdhoods(); //count all cell´s neighbours
        countTheCols = multiGrid[block].colCount;
        countTheRows = multiGrid[block].rowCount;
        //CountStatusInNeighbourdhoods(0, 0); //count healthy around
        //    Do for all cells in the grid
        for(int i = 0; i < colCount;i++){
            for(int j = 0; j< rowCount;j++){
                theGrid[i][j].Breed();
                theGrid[i][j].Dies(randSeed);
                randSeed++;
            }
        }
    }

    CountCells();
    turnsCount ++;

}


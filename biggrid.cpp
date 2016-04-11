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
    CountEmpty,CountPredator,CountPrey = 0;
    turnsCount = 0;


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


//        qDebug()<< "Reached 102 ";
        multiGrid[n] = *aGrid;
//        qDebug()<< "Reached 3 ";
        count ++;

    }





}


/*DESTRUCTOR: ---------------------------
CRASHES THE APP AT THE MOMENT -> minigrid may be conflicting
----------------------------------*/
BigGrid::~BigGrid(){
//    for(int i=0; i<numCols; i++){
//            delete &multiGrid[i];
//    }

//    delete this;

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
POSSIBLE MEMORY LEAK
----------------------------------*/
void BigGrid::FillGhostCells(){

    for(int block = 0; block< numCols; block++){
        int miniBlockWidth = multiGrid[block].colCount;
        for(int i = 0; i<miniBlockWidth; i++){
            for(int j =0;j < multiGrid[block].rowCount; j++){


                        // Get data from the left
                        if(block>0){ //block!=0
//                            delete &multiGrid[block].theGrid[0][j];
//                            cell * cellptr;
//                            cellptr = &multiGrid[block+1].theGrid[1][j];
                            multiGrid[block].theGrid[0][j] = multiGrid[block-1].theGrid[100][j];

//                            multiGrid[block].theGrid[0][j].CopyCell(cellptr);
                        }
                        // Get data from the right
                        if(block<numCols-1){  // block!=numCols-1
//                            cell * cellptr;
//                            cellptr = &multiGrid[block+1].theGrid[1][j];
//                            delete &multiGrid[block].theGrid[101][j];
                            multiGrid[block].theGrid[101][j] = multiGrid[block+1].theGrid[1][j];
//                            multiGrid[block].theGrid[101][j].CopyCell(cellptr);

                        }


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
    countTheCols = multiGrid[0].colCount;
    countTheRows = multiGrid[0].rowCount;
//    clock_t time1, time2, time3, time4;

#pragma omp parallel num_threads(8)
    {
        //        int tid=omp_get_thread_num();
        //        qDebug()<< "thread:" << tid;
#pragma omp for
        for(int block = 0; block< numCols; block++){
            //        time1 = clock();

            multiGrid[block].CountStatusInNeighbourdhoods(true); //count all cell´s neighbours
            //        time2 = clock();
            //        qDebug() << "Status count:" <<time2- time1;
//            int tid=omp_get_thread_num();
//            qDebug()<< "thread:" << tid << "is in block:" << block;
            //CountStatusInNeighbourdhoods(0, 0); //count healthy around
            //    Do for all cells in the grid
            for(int i = 1; i < multiGrid[block].colCount-1;i++){  // Takes into account the ghostcells
                for(int j = 0; j< multiGrid[block].rowCount;j++){
                    multiGrid[block].theGrid[i][j].Breed();
                    multiGrid[block].theGrid[i][j].Dies(multiGrid[block].randSeed);
                    multiGrid[block].randSeed++;

                }
            }
            //        time3 = clock();
            multiGrid[block].CountCells();
            //        qDebug() << "Status change:" <<time3- time2;

        }
    }

//    int tid=omp_get_thread_num();
//    qDebug()<< "thread:" << tid << "is in END";

//    time3 = clock();
    CountCellsBigGrid();
//    time4 = clock();
//    qDebug() << "Count Cells:" <<time4- time3;

//    time2 = clock();
    FillGhostCells();
//    time3 = clock();
//    qDebug() << "Refill Ghost Cells:" <<time3- time2;
//    qDebug() << multiGrid[0].theGrid[1][0].status;
    turnsCount ++;

}




/*CountCellsBigGrid: ---------------------------
Uses the count of miniGrid to get a general count
----------------------------------*/
void BigGrid::CountCellsBigGrid(){
        CountPredator=0;
        CountEmpty = 0;
        CountPrey = 0;
        for(int block = 0; block< numCols; block++){
//            qDebug() <<"Block " <<block <<" is: " <<multiGrid[block].CountPredator;
            CountPredator += multiGrid[block].CountPredator;
            CountEmpty += multiGrid[block].CountEmpty;
            CountPrey += multiGrid[block].CountPrey;
        }
}

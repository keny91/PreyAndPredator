#include "grid.h"



/*---------------------------
CONSTRUCTORS; default grid 15x15
----------------------------*/



grid::grid()
{
    cellsDeleted = 0;
    turnsCount = 0;
    int cols = 15;
    int rows = 15;
    CountLife=0;
    CountDeath =0;
    CountInfected = 0;
    neighbourhoodSize =1;
    rowCount=rows;
    colCount=cols;
    //theGrid = NULL;
    theGrid = new cell*[rowCount];
    for(int i = 0;i<rowCount; i++){
        theGrid[i]= new cell[colCount];
        for(int j = 0;j<colCount; j++){
            theGrid[i][j].SetRegular();
        }
    }

}

grid::grid(int col,int row )
{
    CountLife=0;
    CountDeath =0;
    CountInfected = 0;
    rowCount=row;
    colCount=col;
    turnsCount = 0;
    cellsDeleted = 0;
    neighbourhoodSize =1;
    theGrid = new cell*[colCount];
    for(int i = 0;i<colCount; i++)
        theGrid[i]= new cell[rowCount];

}


/*---------------------------

----------------------------*/
void grid::InitGrid(){

    for(int i=0; i<rowCount; i++){
        for(int j=0; j<colCount;j++){
            theGrid[i][j] = cell();
            theGrid[i][j].SetRegular();
        }
    }

}




/*CountCells--------------------

----------------------------*/
void grid::CountCells(){
    CountLife=0;
    CountDeath =0;
    CountInfected = 0;

    for(int i=0; i<colCount; i++){
        for(int j=0; j<rowCount;j++){
            if(theGrid[i][j].state ==0)
                CountLife++;
            else if(theGrid[i][j].state ==1)
                CountInfected++;
            else if(theGrid[i][j].state ==2)
                CountDeath++;
        }
    }

}

/*---------------------------
ONLY WORKS FOR NEIGHBOURDHOOD = 1
counts the number
----------------------------*/
void grid::CountStatusInNeighbourdhoods(int thisCellStatus, int theStatusUnderCount){
    int count = 0;
    //Go 1-by-1
    for(int i=0; i<colCount; i++){
        for(int j=0; j<rowCount;j++){
             count = 0;
             if(theGrid[i][j].state == thisCellStatus){

             //Set parameters
             // EXCEPTIONS OUT OF GRID -> need 4 exceptions
                 int initI,finalI;
                 int initJ,finalJ;

                 if(i==0)
                     initI=i;
                 else
                     initI=i-neighbourhoodSize;

                 if(j==0)
                     initJ=j;
                 else
                     initJ=j-neighbourhoodSize;


                 if(i==colCount-1)
                     finalI=i;
                 else
                     finalI=i+neighbourhoodSize;

                 if(j==rowCount-1)
                     finalJ=j;
                 else
                     finalJ=j+neighbourhoodSize;

                // loop in the neighboorhood
                 for(int a=initI; a<=finalI; a++){
                     for(int b=initJ; b<=finalJ;b++){
                         if(theGrid[a][b].state == theStatusUnderCount)
                             count++;
                      }
                     }
                 if(theStatusUnderCount == 1)
                    theGrid[i][j].InfectedCellsInNeighboorhood = count;
                 else if(theStatusUnderCount == 0)
                    theGrid[i][j].HealthyCellsInNeighboorhood = count;
                count = 0;
             }



        }
    }

}


/*NextTurn: ---------------------------

----------------------------------*/
void grid::NextTurn(){

    CountStatusInNeighbourdhoods(0, 1); //count infected around
    CountStatusInNeighbourdhoods(0, 0); //count healthy around
    // roll infections
    for(int i = 0; i < colCount;i++){
        for(int j = 0; j< rowCount;j++){
            if(theGrid[i][j].state == 0)
                theGrid[i][j].GetsInfectedRoll();
            else if (theGrid[i][j].state == 1)
                theGrid[i][j].IncreaseInfection();
        }
    }

    CountCells();
    turnsCount ++;



}



/*---------------------------

----------------------------*/
grid::~grid(){
//    for(int i=0; i<rowCount; i++){
//        for(int j=0; j<colCount;j++){
//            theGrid[i][j].~cell();
//            delete theGrid[i][j];
//            cellsDeleted++;
//            qDebug()<< cellsDeleted;
//        }
//        delete &theGrid[i];
//    }
//    delete theGrid;
//    //qDebug()<< theGrid[1][1].state;
//    //qDebug()<< "Destructor call to grid";
//    delete this;
    qDebug()<< "DEBUG 3";
}

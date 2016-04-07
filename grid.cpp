#include "grid.h"


/*-----Process Order:
1st-> Check&Count STATUSW around a regular cell
2nd-> Breed.
3rd-> Die
4th-> Recount
-> Next Round (next generation)
----------------------------*/


/*-----OPTION 2:
1st-> Check&Count STATUSW around a regular cell
2nd-> Breed,... Die...  (only empty cells can breed)
3RD-> Recount
-> Next Round (next generation)
----------------------------*/


/*---------------------------
CONSTRUCTORS; default grid 15x15
----------------------------*/

grid::grid()
{
    randSeed = 0;
    cellsDeleted = 0;
    turnsCount = 0;
    int cols = 15;
    int rows = 15;
    CountEmpty=0;
    CountPredator =0;
    CountPrey = 0;
    neighbourhoodSize =1;
    rowCount=rows;
    colCount=cols;
    //trycell = new PreyCell();
    //theGrid = NULL;
    theGrid = new cell*[rowCount];
    for(int i = 0;i<rowCount; i++){
        theGrid[i]= new cell[colCount];
//        for(int j = 0;j<colCount; j++){
//            trycell = new PreyCell();
//            theGrid[i][j] = *trycell;
//            qDebug() << theGrid[i][j].color[0] << " " << theGrid[i][j].color[1];
//            theGrid[i][j].SetRegular();
//        }
    }

}

grid::grid(int col,int row )
{
    randSeed=0;
    CountEmpty=0;
    CountPredator =0;
    CountPrey = 0;
    rowCount=row;
    colCount=col;
    turnsCount = 0;
    cellsDeleted = 0;
    neighbourhoodSize =1;
    theGrid = new cell*[colCount];
    for(int i = 0;i<colCount; i++){
        theGrid[i]= new cell[rowCount];
//        for(int j = 0; j<rowCount; j++){
//            cell * cellptr = new PreyCell();

////            cellptr->SetInfected();
////            cell * Vec3b color = theGrid.at<cell[][]>(Point(i,j));
////            cell * cellptr = new cell();
//            PreyCell * cellptr2 = &theGrid[i][j];
////            theGrid[i][j]= *cellptr;
////             = cellptr;
//            //cellptr2 = cellptr;
////            theGrid[i][j]=()
////            theGrid.at<>(cell(i,j))= cellptr;
////            ((PreyCell*)&theGrid[i][j])->SetInfected();
//            theGrid[i][j].SetInfected();


//            qDebug() << theGrid[i][j].color[0] << " " << theGrid[i][j].color[1];
//            cellptr->color[0] = 255;
//            cellptr->color[1] = 255;
//            cellptr->color[2] = 255;
//        }
//    theGrid[i]= new PreyCell[rowCount];

    }

}






/*PopulateGrid--------------------------
During the start of the program we will create a Grid and initialize it with different and
randomly distributed kinds of samples.
----------------------------*/
void grid::PopulateGrid(int type, int number){
    int vertical;
    QTime now = QTime::currentTime();
    int horizontal;
    for(int i = 0; i < number;  i++ ){
        QTime now = QTime::currentTime();
        qsrand(now.msec()+randSeed + qrand());
        randSeed++;
        horizontal = qrand()% colCount;  //maybe is not + 1
        qsrand(now.msec()+randSeed + qrand());
        randSeed++;
        vertical = qrand()% rowCount;

        // Case 1: the cell is empty
//        qDebug()<<"Selected Cell is: " << horizontal << " " << vertical;
//        qDebug() << i;
        if(theGrid[horizontal][vertical].isEmpty()){
                switch (type) {
                    case 1:  //case prey
                        theGrid[horizontal][vertical].SetPrey();
//                        qDebug()<<"It´s a prey";
//                        qDebug()<<"-----------";
                        break;

                    case 2:  //case predator
                        theGrid[horizontal][vertical].SetPredator();
//                        qDebug()<<"It´s a predat";
                        break;

                    default: // remain empty
                        theGrid[horizontal][vertical].SetEmpty();
                        break;
                }
            }
                        // Case 2: the cell is populated so we look for a new one. So we repeat again.
         else{
//            qDebug() << "Cell not empty";
//            qDebug()<<"-----------";
            i--;
         }

    // reset seed in case it goes too large for int format
            if (randSeed > 30000)
                randSeed = 0;
    }
}







/*---------------------------
InitGridWithStandardCells: this is the default call to initialize de grid
with 50% preys and 25% predators
----------------------------*/
void grid::InitGridWithStandardCells(boolean includeGhostCols){
    double TotalNumber;
    int NumberOfPredators,NumberOfPreys;

    if(includeGhostCols){
        TotalNumber = rowCount * (colCount-2);  // Exclude ghost cells
    }
    else{
        TotalNumber = rowCount * colCount;
    }

    NumberOfPredators = round(TotalNumber*0.25);
    NumberOfPreys = round(TotalNumber*0.5);


//    qDebug()<< "Generating Grid";
//    qDebug()<<" Total Number of Samples: " <<round(TotalNumber);
//    qDebug()<<" estimated number of preys: " <<NumberOfPreys;
//    qDebug()<<" estimated number of Predators: " <<NumberOfPredators;
    PopulateGrid(1,NumberOfPreys);  //Adds prey
    PopulateGrid(2,NumberOfPredators);  //Adds predator

    CountEmpty=0;
    CountPredator =0;
    CountPrey = 0;
}




/*CountCells--------------------
A recount of the every possible cell status
----------------------------*/
void grid::CountCells(){

    CountEmpty=0;
    CountPredator =0;
    CountPrey = 0;

    for(int i=0; i<colCount; i++){
        for(int j=0; j<rowCount;j++){
            if(theGrid[i][j].status ==0)
                CountEmpty++;
            else if(theGrid[i][j].status ==1)
                CountPrey++;
            else if(theGrid[i][j].status ==2)
                CountPredator++;
        }
    }

}

/*---------------------------
ONLY WORKS FOR NEIGHBOURDHOOD = 1
counts the number
----------------------------*/
void grid::CountStatusInNeighbourdhoods(boolean includeGhostCols){
    int countPreds, countPreys, countEmptys= 0;
    int countPredsOld, countPreysOld;

    int initialColStart, finalColEnd;
    initialColStart = 0;
    finalColEnd = colCount;


    if(includeGhostCols){
        initialColStart = 1;
        finalColEnd = colCount -1;
    }


    //Go 1-by-1
    for(int i=initialColStart; i<finalColEnd; i++){
        for(int j=0; j<rowCount;j++){
             countPreds = 0;
             countPreys = 0;
             countPreysOld =0;
             countPredsOld =0;
             countEmptys = 0;

//             if(theGrid[i][j].status == thisCellStatus){

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
                         if(theGrid[a][b].status == 1){
                            countPreys++;
                            if(theGrid[a][b].age >= theGrid[a][b].BreedingAge)
                                countPreysOld++;
                         }

                         else if(theGrid[a][b].status == 2){
                             countPreds++;
                             if(theGrid[a][b].age >= theGrid[a][b].BreedingAge)
                                 countPredsOld++;
                         }
                         else
                             countEmptys++;
                      }
                     }

                 // Since we are including the Cell status as part of the neighbourhood
                 if(theGrid[i][j].status == 1){
                     countPreys--;
                     if(theGrid[i][j].age >= theGrid[i][j].BreedingAge)
                         countPreysOld--;
                 }
                 else if(theGrid[i][j].status == 2){
                     countPreds --;
                     if(theGrid[i][j].age >= theGrid[i][j].BreedingAge)
                         countPredsOld--;
                 }
                 else
                     countEmptys--;

                    theGrid[i][j].predatorsInNeighbourhood = countPreds;
                    theGrid[i][j].maturePredatorInNeighbourhood = countPredsOld;
                    theGrid[i][j].preyInNeighbourhood = countPreys;
                    theGrid[i][j].maturePreyInNeighbourhood = countPreysOld;

//             }



        }
    }

}




/*NextTurn: ---------------------------
    Does a set of process that conform a cycle
----------------------------------*/
void grid::NextTurn(){

    CountStatusInNeighbourdhoods(); //count all cell´s neighbours
    //CountStatusInNeighbourdhoods(0, 0); //count healthy around
//    Do for all cells in the grid
    for(int i = 0; i < colCount;i++){
        for(int j = 0; j< rowCount;j++){
            theGrid[i][j].Breed();
            theGrid[i][j].Dies(randSeed);
            randSeed++;
        }
    }

    CountCells();
    turnsCount ++;

}



/*---------------------------
DESTRUCTOR
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

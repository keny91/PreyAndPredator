#include "biggrid.h"

BigGrid::BigGrid()
{

}


BigGrid::BigGrid(int X, int NCols, int NRows){

    int count = 0;

//    for(int i = 0;i<Y; i++){

////        theGrid = new cell*[colCount];
////        for(int i = 0;i<colCount; i++){
////            theGrid[i]= new cell[rowCount];

//        if(Y > 1){
//            qDebug()<< "WITH Y";
//            multiGrid[i]= new MiniGrid[Y];

//        }
//        else{
//            qDebug()<< "WITHout Y";
//            multiGrid[i] = new MiniGrid[X];
//        }
//    }


//    for(int m = 0;m < X; m++){
////        multiGrid[i]= new MiniGrid[Y];
//            for(int n = 0; n < Y; n++){
////                qDebug() <<
//                qDebug()<< "Reached  " << count;
////                qDebug()<< m << "Reached  " << n;
//                MiniGrid * aGrid = new MiniGrid(NCols,NRows , n, m, count);
//                qDebug() << "m =" << m << "  n=" << n;

//                // This is specialized in an only COL distribution
//                if(n==0  && X > 1){
//                    qDebug() << "Firstate";
//                    aGrid->setLeftNull();
//                    qDebug()<< "Reached EndFirstate ";
//                }
//                else if( n == X-1 && X > 1){
//                    qDebug() << "SecondState";
//                    aGrid->setRightNull();
//                    qDebug()<< "Reached END ";
//                }

//                if(m==0 && Y > 1){
//                    qDebug()<< "Reached  " << "a";
//                    aGrid->setTopNull();
//                    qDebug()<< "Reached  " << "b";
//                }
//                else if(m==Y-1&& Y > 1){
//                    qDebug()<< "Reached END ";
//                    aGrid->setBotNull();
//                }



//                qDebug()<< "Reached 102 ";
//                multiGrid[n][m] = *aGrid;
//                qDebug()<< "Reached 3 ";
//                count ++;

//            }

//    }

    qDebug()<< "WITH Y";
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
//            qDebug()<< "Reached EndFirstate ";
        }
        else if( n == X-1 && X > 1){
//            qDebug() << "SecondState";
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




#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myGrid = new grid(30,30);
//    NCols,NRows , i, j, count



    //Initialization of grid

    // Set dimensions
    height = 1000;
    width = 2000;
    Nblocks = 20;

    frame = new int *[width];
    for(int i =0; i<width ; i++){
        frame[i] = new int[height];
    }
    for(int i =0; i<width ; i++){
        for(int j = 0 ; j <height; j++)
            frame[i][j] = 0;
    }


//    qDebug() << "A->" << frame[1][1];

    myBigGrid = BigGrid(Nblocks,width/Nblocks,height);
    myBigGrid.InitBigGrid();
//    qDebug() << "A->" << myBigGrid.multiGrid[0].theGrid[1][1].status;
    myBigGrid.SetNullGhostCells();
//    qDebug() << "B->" <<myBigGrid.multiGrid[0].theGrid[1][1].status;
    GridToMatrix();

//    qDebug() << myBigGrid.multiGrid[1].indexGeneral ;
//    qDebug() << myBigGrid.multiGrid[0].theGrid[0][0].status;
//    MiniGrid * myMini = new MiniGrid(100,100,1,1,1);
//    qDebug()<< "Reached 2 ";

//    qDebug()<< myBigGrid.multiGrid[0].theGrid[0][0].status;
//               myMini->rowCount;

//  See that left and rightmost columns are null
//    qDebug()<< "TRY1: " << myBigGrid.multiGrid[0].theGrid[1][0].status;
//    qDebug()<< "TRY2: " << myBigGrid.multiGrid[myBigGrid.numCols-1].theGrid[0][myBigGrid.multiGrid->rowCount-1].status;
//    qDebug()<< "In mini: cols: " << myBigGrid.multiGrid[0].colCount << "  rows:" << myBigGrid.multiGrid[0].rowCount;


//    image= Mat(myGrid->rowCount,myGrid->colCount,CV_8UC3, Scalar(0, 0, 0));
    image= Mat(height,width,CV_8UC3, Scalar(0, 0, 0));

    QTimer *mytimer = new QTimer(this);

    connect(mytimer, SIGNAL(timeout()), this,SLOT(Refreshing()));
    mytimer->start(10);  // Change to speed up
//    qDebug()<< "Start Color Assingment" ;



    /*Infectation spread:----------
            Paint the image according to the grid cells.
    ---------------------------*/
    //myGrid->theGrid[1][1].SetInfected();

  myGrid->InitGridWithStandardCells();
//  myGrid->theGrid[22][22].SetEmpty();
//    qDebug()<< "myGrid" << myGrid->theGrid[0][0].status;
//    qDebug()<< "myGrid2" << myGrid->theGrid[1][0].status;
//    qDebug()<< "myGrid3" << myGrid->theGrid[2][0].status;
//    qDebug()<< "myGrid4" << myGrid->theGrid[3][0].status;
//    qDebug()<< "myGrid5" << myGrid->theGrid[4][0].status;
//    qDebug()<< "myGrid6" << myGrid->theGrid[5][0].status;
}




/*Repaint:-----------------
        Paint the image according to the grid cells.
------------------------------*/
void MainWindow::RePaintIm(){


    int r = 0;
    int c = 0;

//    qDebug()<< "Start Color Assingment" ;
    for(int i = 0; i < myGrid->colCount;i++){
        for(int j = 0; j< myGrid->rowCount;j++){
                cv::Vec3b color = image.at<Vec3b>(Point(i,j)); // heeeere
                //Initial color: black = (B, G, R) = (0, 0, 0)
                color[0] = myGrid->theGrid[i][j].color[0];
                color[1] = myGrid->theGrid[i][j].color[1];
                color[2] = myGrid->theGrid[i][j].color[2];
                image.at<cv::Vec3b>(Point(i,j)) = color;
//                qDebug()<< "r: " << r << " ---c: " << c ;
                c = c+1;

        }
    c=0;
    r++;
    }
//    qDebug()<< "End Color Assingment";


}

/*Resize:-----------------

------------------------*/
void MainWindow::ReSizeIm(){

    double imageSizeY, imageSizeX;
    double fx, fy;
    double MaxLenght = 500;

    double Cols = (double)width;
    double Rows =  (double)height;
    double Proportion;

//    qDebug()<< "Start of Resize";
    //CASE 1: y > x
    if (height >= width){

        Proportion = (Cols/Rows);
        imageSizeY = MaxLenght;
        fy = imageSizeY/height;
//        qDebug()<< "Y:" << imageSizeY;
//        qDebug()<< "fy:" << fy;
        imageSizeX = imageSizeY*Proportion;
//        qDebug()<< "Proportion: "<< Proportion;
        fx = imageSizeX/width;
//        qDebug()<< "X:" << imageSizeX;
        cv::resize(image,image,Size(),fy,fy,INTER_AREA );


    }
    else if(height < width){

        Proportion = (Rows/Cols);
        imageSizeX = MaxLenght;
        fx = imageSizeX/width;
//        qDebug()<< "X:" << imageSizeX;
//        qDebug()<< "fx:" << fx;
        imageSizeY = imageSizeX*Proportion;

//        qDebug()<< "Proportion: "<< Proportion;
        fy = imageSizeY/width;
//        qDebug()<< "Y:" << imageSizeY;
        cv::resize(image,image,Size(),fx,fx,INTER_AREA );


    }
//    qDebug()<< "End of Resize";


}



/*GridToMatrix:-----------------
        Read the Multigrid into a int matrix.
        Using Multithread.
------------------------------*/
void MainWindow::GridToMatrix(){


    //ADD THREADS HERE
    int miniBlockWidth = width/Nblocks;
    qDebug()<< "W Block Search: " << miniBlockWidth << "  Actual W Block: " << myBigGrid.multiGrid[0].colCount;
    qDebug()<< "H Block Search: " << height << "  Actual H Block: " << myBigGrid.multiGrid[0].rowCount;


    for(int block = 0; block< Nblocks; block++){

        for(int i = 0; i<miniBlockWidth; i++){
            for(int j =0;j < height; j++){
                frame[i+block*miniBlockWidth][j]= myBigGrid.multiGrid[block].theGrid[i+1][j].status; // +1 to skip ghost cells
            }
        }



    }
        qDebug()<< "SHOULD BE:" << myBigGrid.multiGrid[0].theGrid[100][2].status;
        qDebug()<< "End of Resize" << frame[99][2];

}


/*RepaintBigGrid:-----------------
        Paint the image according to the grid cells.
------------------------------*/

void MainWindow::RepaintBigGrid(){


    qDebug()<< "Start Color Assingment" ;
    for(int i = 0; i < width;i++){
        for(int j = 0; j< height;j++){

//                qDebug()<< frame[i][j];
//            qDebug()<< "i:" << i << "j:"<< j ;
            cv::Vec3b color = image.at<Vec3b>(Point(i,j));
//            qDebug()<< "i:" << i << "j:"<< j ;
                if(frame[i][j]==0){
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0;
                }
                else if(frame[i][j]==1){
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 0;
                }
                // Predators
                else if(frame[i][j]==2){
                    color[0] = 200;
                    color[1] = 30;
                    color[2] = 30;
                }
                // NULL CELLS?
                else{
                    color[0] = 50;
                    color[1] = 50;
                    color[2] = 50;

                }

                image.at<cv::Vec3b>(Point(i,j)) = color;
                 // heeeere

        }
    }

    qDebug()<< "END Color Assingment" ;

}





void MainWindow::Refreshing(){
    clock_t time1, time2,time3;
    time1 = clock();
    myGrid->NextTurn();
    time2 = clock();


    if((myGrid->turnsCount % 100) == 0 || myGrid->turnsCount == 1){
//        RePaintIm();
        RepaintBigGrid();
        ReSizeIm();
        QImage imgIn= QImage((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(imgIn));
        //delete &image;
        image= Mat(height,width,CV_8UC3, Scalar(0, 0, 0));
        time3 = clock();
        stringstream labText;
        labText << myGrid->turnsCount;
        QString QStr = QString::fromStdString(labText.str());
        ui->label_3->setText(QStr);
//        QLineEdit * lineedit = new QLineEdit;
//        lay2->addWidget(lineedit);

//        QLabel * label = edit->findChild<QLabel*>("label_3");
//        label->setText(lineedit->text());
    }

//      qDebug()<< myGrid->turnsCount;
//      qDebug()<< myGrid->turnsCount % 100;
//    qDebug()<< "ProcessTime:" << time2-time1;
//    qDebug()<< "ProcessTime with :" << time3-time1;
//    qDebug()<< "Turns: " << myGrid->turnsCount;
//    qDebug()<< "myGrid->COunt prey: " << myGrid->CountPrey;
//    qDebug()<< "myGrid->COunt pred" << myGrid->CountPredator;
//    qDebug()<< "myGrid->Status: " << myGrid->theGrid[22][22].status;
//    qDebug()<< "myGrid->COunt neigh prey: " << myGrid->theGrid[22][22].preyInNeighbourhood;
//    qDebug()<< "myGrid->COunt neigh prey: " << myGrid->theGrid[22][22].preyInNeighbourhood;
    //Sleep(500);
}


MainWindow::~MainWindow()
{
    delete ui;
}

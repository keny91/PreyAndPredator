#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    myGrid = new grid(30,30);
//    NCols,NRows , i, j, count



    //Initialization of grid

    // Set dimensions
    height = 300;
    width = 500;
    Nblocks = 5;

    frame = new int *[width];
    for(int i =0; i<width ; i++){
        frame[i] = new int[height];
    }
    for(int i =0; i<width ; i++){
        for(int j = 0 ; j <height; j++)
            frame[i][j] = 0;
    }


//    qDebug() << "A->" << frame[1][1];

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pauseButtonClick()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(resetButtonClick()));

    isRunning=true;
    OnCooldown = false;

    myBigGrid = BigGrid(Nblocks,width/Nblocks,height);
    myBigGrid.InitBigGrid();
    myBigGrid.SetNullGhostCells();
    GridToMatrix();
    TotalTime = 0;

    image= Mat(height,width,CV_8UC3, Scalar(0, 0, 0));

    QTimer *mytimer = new QTimer(this);

    connect(mytimer, SIGNAL(timeout()), this,SLOT(Refreshing()));
    mytimer->start(1);  // Change to speed up


//  myGrid->InitGridWithStandardCells();

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
        imageSizeX = imageSizeY*Proportion;
        fx = imageSizeX/width;
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


    for(int block = 0; block< Nblocks; block++){

        for(int i = 0; i<miniBlockWidth; i++){
            for(int j =0;j < height; j++){
                frame[i+block*miniBlockWidth][j]= myBigGrid.multiGrid[block].theGrid[i+1][j].status; // +1 to skip ghost cells
            }
        }



    }
}


/*RepaintBigGrid:-----------------
        Paint the image according to the grid cells.
------------------------------*/

void MainWindow::RepaintBigGrid(){

#pragma omp parallel num_threads(8)
    {
        //        int tid=omp_get_thread_num();
        //        qDebug()<< "thread:" << tid;
#pragma omp for

    for(int i = 0; i < width;i++){
        for(int j = 0; j< height;j++){


            cv::Vec3b color = image.at<Vec3b>(Point(i,j));
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
                    qDebug() << "paint error: should not appear";
                }

                image.at<cv::Vec3b>(Point(i,j)) = color;
                 // heeeere

        }
    }

    }
}



/*Refresh:-----------------
        All the changes from the previous generation are updated
------------------------------*/

void MainWindow::Refreshing(){
//    MeanTime = 0;

    if(isRunning){
      clock_t time1, time2,time3;



    time1 = clock();

//    myGrid->NextTurn();
    myBigGrid.NextTurnBigGrid();

    time2 = clock();
    MeanTime = time2- time1;
    TotalTime += time2-time1;
//    qDebug() << myBigGrid.turnsCount;
//    qDebug() << time2- time1;

    if((myBigGrid.turnsCount % 100) == 0 || myBigGrid.turnsCount == 1){
//        RePaintIm();
        GridToMatrix();
        RepaintBigGrid();
        ReSizeIm();
        QImage imgIn= QImage((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(imgIn));


        image= Mat(height,width,CV_8UC3, Scalar(0, 0, 0));



//        time3 = clock();
//        qDebug() << time3- time2;
//        stringstream labText;
//        labText << myBigGrid.turnsCount;
//        QString QStr = QString::fromStdString(labText.str());
//        ui->label_3->setText(QStr);
//        QLineEdit * lineedit = new QLineEdit;
//        lay2->addWidget(lineedit);

//        QLabel * label = edit->findChild<QLabel*>("label_3");
//        label->setText(lineedit->text());
    }
    else{


    }
            RefreshUI();

             }
}


/*RefreshUI:-----------------
        All the changes from the previous generation are updated
------------------------------*/

void MainWindow::RefreshUI(){

    // Change LCD Displays
    ui->lcdNumber->display(myBigGrid.CountPrey);
    ui->lcdNumber_2->display(myBigGrid.CountPredator);
    ui->lcdNumber_3->display(myBigGrid.CountEmpty);



    ui->lcdNumber_4->display(MeanTime);
    ui->lcdNumber_5->display(myBigGrid.turnsCount);
    ui->lcdNumber_6->display(TotalTime);

        image= Mat(height,width,CV_8UC3, Scalar(0, 0, 0));

        stringstream labText;
        labText << myBigGrid.turnsCount;
        QString QStr = QString::fromStdString(labText.str());
        ui->label_3->setText(QStr);

//        QLineEdit * lineedit = new QLineEdit;
//        lay2->addWidget(lineedit);

//        QLabel * label = edit->findChild<QLabel*>("label_3");
//        label->setText(lineedit->text());
//    }

}



void MainWindow::StartProcess(){

    isRunning = true;
    OnCooldown = false;


}


/*PUSHBUTTONS:-----------------
        All the changes from the previous generation are updated
------------------------------*/
void MainWindow::pauseButtonClick(){

    OnCooldown = true;
    if (isRunning == true){
        isRunning = false;
        ui->pushButton->setText("Play");

    }
    else{
        isRunning = true;
        ui->pushButton->setText("Pause");
    }
    Sleep(300);
    OnCooldown = false;
}
void MainWindow::resetButtonClick(){
//    delete &myBigGrid;
//    myBigGrid = BigGrid(Nblocks,width/Nblocks,height);
//    myBigGrid.InitBigGrid();
//    myBigGrid.SetNullGhostCells();
//    GridToMatrix();


    qDebug() << "Button deactivated";
//    include initialize
}




MainWindow::~MainWindow()
{
    delete ui;
}

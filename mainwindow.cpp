#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myGrid = new grid(300,300);
    MiniGrid * myMini = new MiniGrid(10,10);
//    qDebug()<< myMini->rowCount;
//    qDebug()<< "TRY1: " << myMini->theGrid[1][0].status;
//    myMini->setLeftNull();
//    qDebug()<< "TRY2: " << myMini->theGrid[1][0].status;



    image= Mat(myGrid->rowCount,myGrid->colCount,CV_8UC3, Scalar(0, 0, 0));
    //Mat  image =  Mat( Mat::zeros(myGrid->rowCount, myGrid->colCount, CV_32F) );
//    qDebug()<< "Mat created";
    QTimer *mytimer = new QTimer(this);
//    MainWindow::timer->setInterval(300);

//        _release_timer.start();
    connect(mytimer, SIGNAL(timeout()), this,SLOT(Refreshing()));
    mytimer->start(300);
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

//    qDebug()<< image.at<Vec3b>(Point(16,1))[1];
//    qDebug()<< myGrid->colCount ;
//    qDebug()<< image.cols ;
//    qDebug()<< myGrid->rowCount ;
//    qDebug()<< image.rows ;
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
//            Scalar color= Scalar(myGrid->theGrid[i][j].color[0],myGrid->theGrid[i][j].color[1],myGrid->theGrid[i][j].color[2]);
//            image.at<cv::Vec3b>(Point(i,j)) = color;


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
    double MaxLenght = 350;

    double Cols = (double)myGrid->colCount;
    double Rows =  (double)myGrid->rowCount;
    double Proportion;

//    qDebug()<< "Start of Resize";
    //CASE 1: y > x
    if (myGrid->rowCount >= myGrid->colCount){

        Proportion = (Cols/Rows);
        imageSizeY = MaxLenght;
        fy = imageSizeY/myGrid->rowCount;
//        qDebug()<< "Y:" << imageSizeY;
//        qDebug()<< "fy:" << fy;
        imageSizeX = imageSizeY*Proportion;
//        qDebug()<< "Proportion: "<< Proportion;
        fx = imageSizeX/myGrid->colCount;
//        qDebug()<< "X:" << imageSizeX;
        cv::resize(image,image,Size(),fy,fy,INTER_AREA );


    }
    else if(myGrid->rowCount < myGrid->colCount){

        Proportion = (Rows/Cols);
        imageSizeX = MaxLenght;
        fx = imageSizeX/myGrid->colCount;
//        qDebug()<< "X:" << imageSizeX;
//        qDebug()<< "fx:" << fx;
        imageSizeY = imageSizeX*Proportion;

//        qDebug()<< "Proportion: "<< Proportion;
        fy = imageSizeY/myGrid->colCount;
//        qDebug()<< "Y:" << imageSizeY;
        cv::resize(image,image,Size(),fx,fx,INTER_AREA );


    }
//    qDebug()<< "End of Resize";


}



void MainWindow::Refreshing(){
    clock_t time1, time2,time3;
    time1 = clock();
    myGrid->NextTurn();
    time2 = clock();


    if((myGrid->turnsCount % 100) == 0 || myGrid->turnsCount == 1){
        RePaintIm();
        ReSizeIm();
        QImage imgIn= QImage((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(imgIn));
        //delete &image;
        image= Mat(myGrid->rowCount,myGrid->colCount,CV_8UC3, Scalar(0, 0, 0));
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

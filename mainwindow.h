#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
//#include <QTableWidget>
#include "ui_mainwindow.h"
#include <QtCore>
#include <iostream>
#include "grid.h"
#include <time.h>
#include <QTimer>
#include "minigrid.h"
#include "biggrid.h"
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
using namespace cv;



namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void ReSizeIm();
    void RePaintIm();

    void RepaintBigGrid();
    void GridToMatrix();

    ~MainWindow();
    grid *myGrid;
    BigGrid myBigGrid;
    Mat image;


//    cell **grid;

public slots:
    void Refreshing();


private:
    Ui::MainWindow *ui;
    QTimer *mytimer;

};

#endif // MAINWINDOW_H

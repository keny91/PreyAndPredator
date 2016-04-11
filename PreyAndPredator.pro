#-------------------------------------------------
#
# Project created by QtCreator 2016-03-13T09:31:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PreyAndPredator
TEMPLATE = app


QMAKE_CXXFLAGS+= -openmp
QMAKE_LFLAGS +=  -openmp


# MPI Settings
QMAKE_CXX = mpicxx
QMAKE_CXX_RELEASE = $$QMAKE_CXX
QMAKE_CXX_DEBUG = $$QMAKE_CXX
QMAKE_LINK = $$QMAKE_CXX
QMAKE_CC = mpicc

QMAKE_CFLAGS += $$system(mpicc --showme:compile)
QMAKE_LFLAGS += $$system(mpicxx --showme:link)
QMAKE_CXXFLAGS += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK
QMAKE_CXXFLAGS_RELEASE += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK


INCLUDEPATH += C:\\openCV3\\opencv\\MyBuild\\install\\include

LIBS += -LC:\\openCV3\\opencv\\MyBuild\\install\\x64\\vc14\\lib\
    -lopencv_core310d\
    -lopencv_highgui310d\
    -lopencv_imgcodecs310d\
    -lopencv_videoio310d\
    -lopencv_imgproc310d\
    -lopencv_video310d\
    -lopencv_calib3d310d\
    -lopencv_features2d310d\
    -lopencv_flann310d\
    -lopencv_ml310d\
    -lopencv_objdetect310d\
    -lopencv_photo310d\
    -lopencv_shape310d\
    -lopencv_stitching310d\
    -lopencv_superres310d\
    -lopencv_ts310d\
    -lopencv_videostab310d\


SOURCES += main.cpp\
        mainwindow.cpp \
    grid.cpp \
    cell.cpp \
    minigrid.cpp \
    biggrid.cpp

HEADERS  += mainwindow.h \
    grid.h \
    cell.h \
    minigrid.h \
    biggrid.h

FORMS    += mainwindow.ui

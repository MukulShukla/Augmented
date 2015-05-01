#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash=new QSplashScreen;
    splash->setPixmap(QPixmap("/home/mukul/FinalYearProj/Augmented/Augmented/SmartCam_UI/2.jpeg"));
    splash->show();
    MainWindow w;
    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));
    //w.show();
    
    return a.exec();
}

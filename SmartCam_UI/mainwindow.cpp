#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QProcess>
#include "gesture.h"
#include "dialog.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("/home/mukul/FinalYearProj/Augmented/Augmented/SmartCam_UI/3.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    QString link= "https://www.facebook.com/AdvancedImageProcessing?fref=ts";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_5_clicked()
{
    QString link= "http://augrealmsrit.blogspot.in/";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_6_clicked()
{
    QMessageBox::information(this,tr("HELP"),tr("SmartCam has three features.\n1. Live Face Detection is carried out on the click of a button using Laptop's Webcam and puts up different masks on it accordingly.\n2. Live gesture Recognition has 3 sub modules - adding, checking and detecting.\nFor adding a gesture, write the name of the gesture and choose the application to be operated by it. Checking gestures would need the name of the gestures already added.\n 3. Motion is detected live here for different purposes and various activities can be carried out thereafter, mainly for Patient Support system."));

}

void MainWindow::on_pushButton_clicked()
{
    Dialog *C=new Dialog();
    C->setModal(true);
    C->show();
    int res=system("cd /home/mukul/FinalYearProj/Augmented/Augmented/;g++ myprog.cpp -o facedetect -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect");
    if (!res)
    {
        C->hide();
        system("cd /home/mukul/FinalYearProj/Augmented/Augmented/;./facedetect");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    Gesture sec;
    sec.setModal(true);
    sec.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    Dialog *C=new Dialog();
    C->setModal(true);
    C->show();
    int res=system("cd /home/mukul/FinalYearProj/Augmented/Augmented/MotionDetection;g++ main.cpp -o motion -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect;");
    if (!res)
    {
        C->hide();
        system("cd /home/mukul/FinalYearProj/Augmented/Augmented/MotionDetection;./motion");
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    QMessageBox::information(this,tr("About Us"),tr("This file is part of SmartCam (made as a part of Senior Project by students at MSRIT). SmartCam is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\nSmartCam is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with Foobar. If not, see <http://www.gnu.org/licenses/>."));

}

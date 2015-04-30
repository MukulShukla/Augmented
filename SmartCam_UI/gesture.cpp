#include "gesture.h"
#include "ui_gesture.h"
#include <QDebug>
#include "dialog.h"


Gesture::Gesture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gesture)
{
    ui->setupUi(this);
    QPixmap bkgnd("/home/mukul/FinalYearProj/Augmented/Augmented/SmartCam_UI/3.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

Gesture::~Gesture()
{
    delete ui;
}

void Gesture::on_pushButton_clicked()
{
    QString str = ui->var1->text();
    QString str2= ui->var2->currentText();
    QByteArray ba = str.toLatin1();
    const char *c = ba.data();
    QByteArray ba1 = str2.toLatin1();
    const char *c1 = ba1.data();
    const char* space = " ";
    std::string buf(c);
    buf.append(space);
    buf.append(c1);
    const char * c4 = buf.c_str();
    //Dialog *Com=new Dialog();
    //Com->setModal(true);
    //Com->show();
    int res=system("cd /home/mukul/FinalYearProj/Augmented/Augmented/live-gesture-recognition;./install");
    if (!res)
        {
        //Com->hide();
        QString myString = QString("cd /home/mukul/FinalYearProj/Augmented/Augmented/live-gesture-recognition;./addgesture %1").arg(c4);
        qDebug()<< myString;
        system(qPrintable(myString));
        }
}

void Gesture::on_pushButton_2_clicked()
{
    QString str = ui->lineEdit_2->text();
    QByteArray ba = str.toLatin1();
    const char *c = ba.data();
    QString myString = QString("cd /home/mukul/FinalYearProj/Augmented/Augmented/live-gesture-recognition;./checkgesture %1").arg(c);
    system(qPrintable(myString));
}

void Gesture::on_pushButton_3_clicked()
{
    system("cd /home/mukul/FinalYearProj/Augmented/Augmented/live-gesture-recognition;./gesture");
}

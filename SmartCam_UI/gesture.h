#ifndef GESTURE_H
#define GESTURE_H

#include <QDialog>

namespace Ui {
class Gesture;
}

class Gesture : public QDialog
{
    Q_OBJECT
    
public:
    explicit Gesture(QWidget *parent = 0);
    ~Gesture();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Gesture *ui;
};

#endif // GESTURE_H

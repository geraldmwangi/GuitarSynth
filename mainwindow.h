#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "gsengine.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QWidget* getSynthArea();
    void InitSignalSlots();
    ~MainWindow();
public  slots:
        void updateFreqLabel(float val);

private:
    Ui::MainWindow *ui;
    GSEngine* mEngine;


};

#endif // MAINWINDOW_H

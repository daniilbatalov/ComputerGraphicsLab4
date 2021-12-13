#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>

#include "prism.h"
#include "customqtopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSlider* getNSlider();
    QSlider* getRSlider();
    QSlider* getHSlider();
    QSlider* getXSlider();
    QSlider* getYSlider();
    QSlider* getZSlider();
    QSlider* getN2Slider();
    QSlider* getR2Slider();
    QSlider* getH2Slider();
    QSlider* getX2Slider();
    QSlider* getY2Slider();
    QSlider* getZ2Slider();
    QSlider* getD2Slider();
    Prism* getPrism1();
    Prism* getPrism2();
    customqtopenglwidget* getWidget1();
    customqtopenglwidget* getWidget2();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(getNSlider(), &QSlider::valueChanged, getPrism1(), &Prism::on_n_changed);
    QObject::connect(getRSlider(), &QSlider::valueChanged, getPrism1(), &Prism::on_r_changed);
    QObject::connect(getHSlider(), &QSlider::valueChanged, getPrism1(), &Prism::on_h_changed);
    QObject::connect(getXSlider(), &QSlider::valueChanged, getPrism1(), &Prism::on_ex_changed);
    QObject::connect(getYSlider(), &QSlider::valueChanged, getPrism1(), &Prism::on_ey_changed);
    QObject::connect(getZSlider(), &QSlider::valueChanged, getPrism1(), &Prism::on_ez_changed);
    QObject::connect(getPrism1(), SIGNAL(prism_updated()), getWidget1(), SLOT(repaint_par()));
    QObject::connect(getN2Slider(), &QSlider::valueChanged, getPrism2(), &Prism::on_n_changed);
    QObject::connect(getR2Slider(), &QSlider::valueChanged, getPrism2(), &Prism::on_r_changed);
    QObject::connect(getH2Slider(), &QSlider::valueChanged, getPrism2(), &Prism::on_h_changed);
    QObject::connect(getX2Slider(), &QSlider::valueChanged, getPrism2(), &Prism::on_ex_changed);
    QObject::connect(getY2Slider(), &QSlider::valueChanged, getPrism2(), &Prism::on_ey_changed);
    QObject::connect(getZ2Slider(), &QSlider::valueChanged, getPrism2(), &Prism::on_ez_changed);
    QObject::connect(getD2Slider(), &QSlider::valueChanged, getPrism2(), &Prism::on_d_changed);
    QObject::connect(getPrism2(), SIGNAL(prism_updated()), getWidget2(), SLOT(repaint_per()));
}
QSlider* MainWindow::getNSlider()
{
    return ui->slider_n;
}
QSlider* MainWindow::getRSlider()
{
    return ui->slider_r;
}
QSlider* MainWindow::getHSlider()
{
    return ui->slider_h;
}
QSlider* MainWindow::getXSlider()
{
    return ui->slider_x;
}
QSlider* MainWindow::getYSlider()
{
    return ui->slider_y;
}
QSlider* MainWindow::getZSlider()
{
    return ui->slider_z;
}
QSlider* MainWindow::getN2Slider()
{
    return ui->slider_n_2;
}
QSlider* MainWindow::getR2Slider()
{
    return ui->slider_r_2;
}
QSlider* MainWindow::getH2Slider()
{
    return ui->slider_h_2;
}
QSlider* MainWindow::getX2Slider()
{
    return ui->slider_x_2;
}
QSlider* MainWindow::getY2Slider()
{
    return ui->slider_y_2;
}
QSlider* MainWindow::getZ2Slider()
{
    return ui->slider_z_2;
}
QSlider* MainWindow::getD2Slider()
{
    return ui->slider_d_2;
}
Prism* MainWindow::getPrism1()
{
    return &(ui->mainOpenGLWidget->prism1);
}
Prism* MainWindow::getPrism2()
{
    return &(ui->addOpenGLWidget->prism2);
}
customqtopenglwidget* MainWindow::getWidget1()
{
    return ui->mainOpenGLWidget;
}
customqtopenglwidget* MainWindow::getWidget2()
{
    return ui->addOpenGLWidget;
}
MainWindow::~MainWindow()
{
    delete ui;
}






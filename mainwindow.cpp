#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "dialog.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

double m, k, alpha, V0, h=0, xi=0, yi=0, Vx=0, Vy=0, Vxk1=0, Vxk2=0, Vxk3=0, Vxk4=0, Vyk1=0, Vyk2=0, Vyk3=0, Vyk4=0, alphal=0;
QVector<double> xx, yy;

double fvx(double vx, double vy){
    return (-1*k*(sqrt(pow(vx, 2)+pow(vy,2)))*vx/m);
}

double fvy(double vx, double vy){
    return (-9.8-1*k*(sqrt(pow(vx, 2)+pow(vy,2)))*vy/m);
}

double summ(double k1, double k2, double k3, double k4){
    return (k1+2*k2+2*k3+k4);
}
void MainWindow::on_zapusk_clicked()
{
    alphal=(3.14159265*alpha) / 180.0;
    h=0.05;
    Vx=V0*cos(alphal);
    Vy=V0*sin(alphal);
    xx.push_back(0.0);
    yy.push_back(0.0);
    xi=0.0; yi=0.0;
    bool vzlet = true;
    int i=1;
    while ((yi>-0.00001 || vzlet)&& i<10000)
    {
        Vxk1=h*fvx(Vx, Vy);
        Vyk1=h*fvy(Vx, Vy);

        Vxk2=h*fvx(Vx+Vxk1/2, Vy+Vyk1/2);
        Vyk2=h*fvy(Vx+Vxk1/2, Vy+Vyk1/2);

        Vxk3=h*fvx(Vx+Vxk2/2, Vy+Vyk2/2);
        Vyk3=h*fvy(Vx+Vxk2/2, Vy+Vyk2/2);

        Vxk4=h*fvx(Vx+Vxk3,Vy+Vyk3);
        Vyk4=h*fvy(Vx+Vxk3,Vy+Vyk3);

        Vx=Vx+summ(Vxk1,Vxk2,Vxk3,Vxk4)/6;
        Vy=Vy+summ(Vyk1,Vyk2,Vyk3,Vyk4)/6;

        xi=xi+Vx*h;
        yi=yi+Vy*h;
        xx.push_back(xi);
        yy.push_back(yi);

        i++;
       }
    //int n=i-1;
    ui->widget->clearGraphs(); // Очищение всех графиков
    ui->widget->addGraph();  // Добавление одного графика в widget
    ui->widget->graph(0)->setData(xx, yy); // Указание, что отрисовать нужно график по двум массивам xx и yy
    ui->widget->xAxis->setLabel("Ось x");   // Подпись оси Ox и Oy
    ui->widget->yAxis->setLabel("Ось y");
    double maxX = xx.back();
    for (auto it=xx.end(); it!=xx.begin(); it--)
    {
        if (*it >maxX) maxX = *it;
    }
    // Установка области, которая будет показываться на графике
    ui->widget->xAxis->setRange(0, maxX); // Для оси Ox
    double maxY = yy.back();
    for (auto it=yy.end(); it!=yy.begin(); it--)
    {
        if (*it >maxY) maxY = *it;
    }
    ui->widget->yAxis->setRange(0, maxY); // Для оси Oy
    ui->widget->replot();    // Перерисовка графика на widget
    xx.clear(); yy.clear();
}


void MainWindow::on_angle_valueChanged(double arg1)
{ // угол
    alpha = ui->angle->value();
}

void MainWindow::on_resistance_valueChanged(double arg1)
{ // сопротивление
    k = ui->resistance->value();
}

void MainWindow::on_mass_valueChanged(double arg1)
{ // масса
    m = ui->mass->value();
}

void MainWindow::on_speed_valueChanged(double arg1)
{ // скорость
    V0 = ui->speed->value();
}

void MainWindow::on_informationn_clicked()
{
    Dialog d;
    d.setModal(true);
    d.exec();
}

void MainWindow::on_close_clicked()
{
    QWidget::close();
}

void MainWindow::on_clearr_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->xAxis->setLabel("Ось x");
    ui->widget->yAxis->setLabel("Ось y");
    ui->widget->replot();
    xx.clear();
    yy.clear();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QLocale>
#include <QString>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_zapusk_clicked();

    void on_informationn_clicked();

    void on_angle_valueChanged(double arg1);

    void on_resistance_valueChanged(double arg1);

    void on_mass_valueChanged(double arg1);

    void on_speed_valueChanged(double arg1);

    void on_close_clicked();

    void on_clearr_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

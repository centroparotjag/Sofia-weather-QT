#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSettings>
#include <QDateTime>
#include <plot_window.h>
#include <QVector>
#include <QFileDialog>



/* Defining */
#define ORGANIZATION_NAME "SofiaWeather"
#define ORGANIZATION_DOMAIN "centroparotjag"
#define APPLICATION_NAME "QSettings Program"

#define SETTINGS_SummerVinter "settings/SummerVinter"
#define SETTINGS_CITY "settings/city"

#define cnt_point_plot 24  // видима область осі - X в годинах.

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    struct weather{
        int id = 0;
        double temp = 0;
        int pressure = 0;
        int humidity = 0;
        double wind_speed = 0;
        double wind_gust=0;
        int wind_deg = 0;
        double directional_angle = 0;
        int sunrise = 0;
        int sunset = 0;
        QString city = "";
        int visibility = 0;
        int clouds = 0;
        QString description = "";

    };

    int visibility = 0;
    int clouds = 0;
    QString description = "";

    int h_u = 0;
    int m_u = 0;

    int tic5 = 0;

public:
    void parser_request (QString data);
    QString find_data(QString data, QString search);
    QString unixTimeToHumanReadable(long int seconds);
    QString what_is_in_the_sky_ParseData(QString data);
    QString find_city(QString data);

private slots:
    void onGo();
    void onFinished( QNetworkReply* reply );

    void on_pushButton_2_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_clicked();
    void general_weather_conditions();


private:
    Ui::MainWindow *ui;
    plot_window plot_window;
    QNetworkAccessManager m_manager;
    QTimer *timer;
    QTimer *timer5;

public:
    //plot_window plot_window;

};
#endif // MAINWINDOW_H

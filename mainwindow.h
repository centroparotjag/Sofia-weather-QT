#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSettings>
#include <QDateTime>
#include <plot_window.h>
#include <QVector>


/* Defining */
#define ORGANIZATION_NAME "SofiaWeather"
#define ORGANIZATION_DOMAIN "centroparotjag"
#define APPLICATION_NAME "QSettings Program"

#define SETTINGS_SummerVinter "settings/SummerVinter"
#define SETTINGS_CITY "settings/city"


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
        double temp = 0;
        int pressure = 0;
        int humidity = 0;
        double wind_speed = 0;
        int wind_deg = 0;
        double directional_angle = 0;
        int sunrise = 0;
        int sunset = 0;
        QString city = "";
    };

    int count_data = 5;

    double weather_data[100][5] = { { 11.5, 1000, 50, 1.1, 0  },
                                    { 12.5, 1001, 55, 2.1, 10 },
                                    { 13.5, 1002, 60, 3.1, 20 },
                                    { 14.5, 1003, 75, 5.1, 30 },
                                    { 15.5, 1004, 90, 7.1, 40 },
                                    { 16.5, 1005, 84, 10.1, 50 },
                                    { 17.5, 1006, 77, 15.1, 60 },
                                    { 18.5, 1003, 68, 14.1, 70 },
                                    { 19.5, 1001, 54, 10.1, 80 },
                                    { 20.5, 998,  45, 9.1, 90 },
                                    { 19.5, 996,  33, 5.1, 100 },
                                    { 17.5, 994,  28, 3.1, 110 },
                                    { 13.5, 996,  30, 1.1, 120 },
                                    { 12.5, 997,  32, 0.5, 130 },
                                    { 12.3, 998,  34, 0.1, 140 },
                                    { 12.2, 998,  38, 0.0, 150 },
                                    { 12.1, 1002, 40, 0.2, 160 },
                                    { 12.0, 1004, 42, 0.4, 170 },
                                    { 11.8, 1003, 45, 0.6, 180 },
                                    { 11.7, 1001, 49, 0.8, 180 },
                                    { 11.5, 1000, 50, 1.1, 190 },
                                    { 12.5, 1001, 55, 2.1, 200 },
                                    { 13.5, 1002, 60, 3.1, 210 },
                                    { 14.5, 1003, 75, 5.1, 220 },
                                    { 15.5, 1004, 90, 7.1, 230 },
                                    { 16.5, 1005, 84, 10.1, 240 },
                                    { 17.5, 1006, 77, 15.1, 250 },
                                    { 18.5, 1003, 68, 14.1, 260 },
                                    { 19.5, 1001, 54, 10.1, 270 },
                                    { 20.5, 998,  45, 9.1, 280 },
                                    { 19.5, 996,  33, 5.1, 290 },
                                    { 17.5, 994,  28, 3.1, 300 },
                                    { 13.5, 996,  30, 1.1, 310 },
                                    { 12.5, 997,  32, 0.5, 320 },
                                    { 12.3, 998,  34, 0.1, 330 },
                                    { 12.2, 998,  38, 0.0, 340 },
                                    { 12.1, 1002, 40, 0.2, 350 },
                                    { 12.0, 1004, 42, 0.4, 360 },
                                    { 11.8, 1003, 45, 0.6, 370 },
                                    { 11.7, 1001, 49, 0.8, 380 },
                                    { 11.5, 1000, 50, 1.1, 0 },
                                    { 12.5, 1001, 55, 2.1, 10 },
                                    { 13.5, 1002, 60, 3.1, 20 },
                                    { 14.5, 1003, 75, 5.1, 30 },
                                    { 15.5, 1004, 90, 7.1, 40 },
                                    { 16.5, 1005, 84, 10.1, 50 },
                                    { 17.5, 1006, 77, 15.1, 60 },
                                    { 18.5, 1003, 68, 14.1, 70 },
                                    { 19.5, 1001, 54, 10.1, 80 },
                                    { 20.5, 998,  45, 9.1, 90 },
                                    { 19.5, 996,  33, 5.1, 100 },
                                    { 17.5, 994,  28, 3.1, 110 },
                                    { 13.5, 996,  30, 1.1, 120 },
                                    { 12.5, 997,  32, 0.5, 130 },
                                    { 12.3, 998,  34, 0.1, 140 },
                                    { 12.2, 998,  38, 0.0, 150 },
                                    { 12.1, 1002, 40, 0.2, 160 },
                                    { 12.0, 1004, 42, 0.4, 170 },
                                    { 11.8, 1003, 45, 0.6, 180 },
                                    { 11.7, 1001, 49, 0.8, 180 },
                                    { 11.5, 1000, 50, 1.1, 190 },
                                    { 12.5, 1001, 55, 2.1, 200 },
                                    { 13.5, 1002, 60, 3.1, 210 },
                                    { 14.5, 1003, 75, 5.1, 220 },
                                    { 15.5, 1004, 90, 7.1, 230 },
                                    { 16.5, 1005, 84, 10.1, 240 },
                                    { 17.5, 1006, 77, 15.1, 250 },
                                    { 18.5, 1003, 68, 14.1, 260 },
                                    { 19.5, 1001, 54, 10.1, 270 },
                                    { 20.5, 998,  45, 9.1, 280 },
                                    { 19.5, 996,  33, 5.1, 290 },
                                    { 17.5, 994,  28, 3.1, 300 },
                                    { 13.5, 996,  30, 1.1, 310 },
                                    { 12.5, 997,  32, 0.5, 320 },
                                    { 12.3, 998,  34, 0.1, 330 },
                                    { 12.2, 998,  38, 0.0, 340 },
                                    { 12.1, 1002, 40, 0.2, 350 },
                                    { 12.0, 1004, 42, 0.4, 360 },
                                    { 11.8, 1003, 45, 0.6, 370 },
                                    { 11.7, 1001, 49, 0.8, 380 },
                                    { 11.5, 1000, 50, 1.1, 190 },
                                    { 12.5, 1001, 55, 2.1, 200 },
                                    { 13.5, 1002, 60, 3.1, 210 },
                                    { 14.5, 1003, 75, 5.1, 220 },
                                    { 15.5, 1004, 90, 7.1, 230 },
                                    { 16.5, 1005, 84, 10.1, 240 },
                                    { 17.5, 1006, 77, 15.1, 250 },
                                    { 18.5, 1003, 68, 14.1, 260 },
                                    { 19.5, 1001, 54, 10.1, 270 },
                                    { 20.5, 998,  45, 9.1, 280 },
                                    { 19.5, 996,  33, 5.1, 290 },
                                    { 17.5, 994,  28, 3.1, 300 },
                                    { 13.5, 996,  30, 1.1, 310 },
                                    { 12.5, 997,  32, 0.5, 320 },
                                    { 12.3, 998,  34, 0.1, 330 },
                                    { 12.2, 998,  38, 0.0, 340 },
                                    { 12.1, 1002, 40, 0.2, 350 },
                                    { 12.0, 1004, 42, 0.4, 360 },
                                    { 11.8, 1003, 45, 0.6, 370 },
                                    { 11.7, 1001, 49, 0.8, 380 }        };


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

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager m_manager;
    QTimer *timer;

public:
    plot_window plot_window;


//    double xBegin, xEnd, h, X;
//    int N;
//    QVector<double> x, y;
};
#endif // MAINWINDOW_H

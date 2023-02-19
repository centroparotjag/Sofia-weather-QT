#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>



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
    };

public:
    void parser_request (QString data);
    QString find_data(QString data, QString search);
    QString unixTimeToHumanReadable(long int seconds);
    QString what_is_in_the_sky_ParseData(QString data);

private slots:
    void onGo();
    void onFinished( QNetworkReply* reply );




    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager m_manager;

};
#endif // MAINWINDOW_H

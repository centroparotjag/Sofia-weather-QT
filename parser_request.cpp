#include "mainwindow.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include <cstring>

QString MainWindow::find_data(QString data, QString search){
    int skip = 0;
    int length = 0;
    //---------------------------------------------------
    char text [600] = {};
    memcpy(text, data.toStdString().c_str(), data.size());
    //---------------------------------------------------

    QRegExp rx(search);
    int n = data.indexOf (rx); //индекс

    //------ we find the beginning of the data ----------
    for (int i=n; i < n+50; i++) {
        if (text [i-1] == ':' && text [i] >= 0x30 && text [i] <= 0x39){
            skip = i;
            break;
        }
    }

    //----- we find the length of the data -------------
    for (int i=skip; i < skip+50; i++) {
        if (text [i] == '}' || text [i] == ','){
            length = i-skip;
            break;
        }
    }
    QString result=data.mid(skip, length);
    qDebug() << result;
    //return "303";
    return result;
}


// description":"light rain",

QString MainWindow::what_is_in_the_sky_ParseData(QString data){
    int skip;
    int length;
    //---------------------------------------------------
    char text [600] = {};
    memcpy(text, data.toStdString().c_str(), data.size());
    //---------------------------------------------------

    QRegExp rx("description");
    int n = data.indexOf (rx); //индекс

    //------ we find the beginning of the data ----------
    for (int i=n; i < n+50; i++) {
        if (text [i-2] == '"' && text [i-1] == ':' && text [i] == '"'){
            skip = i+1;
            break;
        }
    }

    //----- we find the length of the data -------------
    for (int i=skip; i < skip+50; i++) {
        if (text [i] == '"' && text [i+1] == ',' && text [i+2] == '"'){
            length = i-skip;
            break;
        }
    }
    QString result=data.mid(skip, length);
    qDebug() << result;
    return result;
}


void MainWindow::parser_request (QString data){
    weather weather1;

    weather1.temp       = find_data(data, "temp").toDouble();
    weather1.pressure   = find_data(data, "pressure").toInt();
    weather1.humidity   = find_data(data, "humidity").toInt();
    weather1.wind_speed = find_data(data, "wind").toDouble();
    weather1.wind_deg   = find_data(data, "deg").toInt();
    weather1.sunrise    = find_data(data, "sunrise").toInt();
    weather1.sunset     = find_data(data, "sunset").toInt();

    weather1.directional_angle = (double)weather1.wind_deg/6;

    //---------------- debug Log -----------------------------
    ui->textEdit->setTextColor("green");
    ui->textEdit->append("\nDebug meteo data for Chernivtsi");
    ui->textEdit->append("temp K = "       + QString::number(weather1.temp));
    ui->textEdit->append("temp C = "       + QString::number(weather1.temp-273.16));
    ui->textEdit->append("pressure hPa = "  + QString::number(weather1.pressure));
    ui->textEdit->append("pressure mmHg = " + QString::number((double)weather1.pressure*0.75));
    ui->textEdit->append("humidity % = "   + QString::number(weather1.humidity));
    ui->textEdit->append("wind_speed m/s= " + QString::number(weather1.wind_speed));
    ui->textEdit->append("wind_deg = "   + QString::number(weather1.wind_deg));
    ui->textEdit->append("dir_angle = "  + QString::number(weather1.directional_angle));
    ui->textEdit->append("sunrise Unix time (UTC) = "    + QString::number(weather1.sunrise));
    ui->textEdit->append("sunset Unix time (UTC) = "     + QString::number(weather1.sunset));

    int const size = data.size();

    ui->textEdit->append("sunrise - "+ unixTimeToHumanReadable(weather1.sunrise));
    ui->textEdit->append("sunset - "+ unixTimeToHumanReadable(weather1.sunset));

    ui->textEdit->append(what_is_in_the_sky_ParseData(data));

    ui->textEdit->append("size XML request = " + QString::number(data.size()));


    //-------------- Form data print ------------------------------


    ui->textEdit_temperatura->clear();
    ui->textEdit_temperatura->setTextColor("green");
    if ((weather1.temp-273.16) < 18){
        ui->textEdit_temperatura->setTextColor("blue");
    }
    if ((weather1.temp-273.16) > 27){
        ui->textEdit_temperatura->setTextColor("DeepPink");
    }
    ui->textEdit_temperatura->setFontPointSize(10);
    ui->textEdit_temperatura->append(QString::number(weather1.temp-273.16) + "°C");



    ui->textEdit_humidity->clear();
    ui->textEdit_humidity->setTextColor("green");
    if ((weather1.humidity) < 30 || (weather1.humidity) > 60){
        ui->textEdit_humidity->setTextColor("DeepPink");
    }
    ui->textEdit_humidity->setFontPointSize(10);
    ui->textEdit_humidity->append(QString::number(weather1.humidity) + "%");

    ui->textEdit_wind->clear();
    ui->textEdit_wind->setTextColor("green");
    if (weather1.wind_speed > 10){
        ui->textEdit_wind->setTextColor("DeepPink");
    }
    ui->textEdit_wind->setFontPointSize(10);
    ui->textEdit_wind->append(QString::number(weather1.wind_speed) + "м/с");


    ui->textEdit_wind_deg->clear();
    ui->textEdit_wind_deg->setTextColor("green");
    ui->textEdit_wind_deg->setFontPointSize(10);
    ui->textEdit_wind_deg->append(QString::number(weather1.wind_deg) + "°");

    ui->textEdit_state->clear();
    ui->textEdit_state->setTextColor("green");
    ui->textEdit_state->setFontPointSize(10);
    ui->textEdit_state->append(what_is_in_the_sky_ParseData(data));

    ui->textEdit_Sun_up->clear();
    ui->textEdit_Sun_up->setTextColor("green");
    ui->textEdit_Sun_up->setFontPointSize(10);
    ui->textEdit_Sun_up->append(unixTimeToHumanReadable(weather1.sunrise));

    ui->textEdit_Sun_down->clear();
    ui->textEdit_Sun_down->setTextColor("green");
    ui->textEdit_Sun_down->setFontPointSize(10);
    ui->textEdit_Sun_down->append(unixTimeToHumanReadable(weather1.sunset));



}

#include "mainwindow.h"
#include <QDebug>
#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>

QString extern version;


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
    return result;
}


QString MainWindow::what_is_in_the_sky_ParseData(QString data){
    int skip=0;
    int length=0;
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

QString MainWindow::find_city(QString data){
    int skip =0;
    int length=0;
    //---------------------------------------------------
    char text [600] = {};
    memcpy(text, data.toStdString().c_str(), data.size());
    //---------------------------------------------------

    QRegExp rx("name");
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

uint count_data = 0;
int last_update_hour = 55;
//int test = 0;

void MainWindow::parser_request (QString data ){
    weather weather1;

    weather1.temp       = find_data(data, "temp").toDouble();
    weather1.pressure   = find_data(data, "pressure").toInt();
    uint grnd_level     = find_data(data, "grnd_level").toInt();
    weather1.humidity   = find_data(data, "humidity").toInt();
    weather1.wind_speed = find_data(data, "wind").toDouble();
    weather1.wind_gust  = find_data(data, "gust").toDouble();
    weather1.wind_deg   = find_data(data, "deg").toInt();
    weather1.sunrise    = find_data(data, "sunrise").toInt();
    weather1.sunset     = find_data(data, "sunset").toInt();
    weather1.city       = find_city(data);

    weather1.directional_angle = (double)weather1.wind_deg/6;

    QTime ct = QTime::currentTime();
    qDebug() << ct.toString("hh:mm:ss");
    int hour = ct.toString("h").toInt();
    int min = ct.toString("m").toInt();
    qDebug() << "hour " << hour<< ", min " << min;

    //------ Plot updates every hour --------------------------
    if (last_update_hour != hour && weather1.pressure != 0 && weather1.humidity != 0){

//        test++;
//        weather1.temp      =weather1.temp      +test;
//        weather1.pressure  =weather1.pressure  +test;
//        weather1.humidity  =weather1.humidity  +test;
//        weather1.wind_speed=weather1.wind_speed+test;
//        weather1.wind_deg  =weather1.wind_deg  +test;

        plot_window.plot_g1(weather1.temp-273.16, weather1.wind_speed, weather1.wind_deg,
                            weather1.pressure*0.75, weather1.humidity, count_data);

        count_data++;
        last_update_hour = hour;
    }

    qDebug() << "Count data " << count_data;

    //--------------------------------------------------------

    //---------------- debug Log -----------------------------
    ui->textEdit->setTextColor(QColor::fromRgb(0,150,0));
    ui->textEdit->append("\n");
    ui->textEdit->append("temp K = "       + QString::number(weather1.temp));
    ui->textEdit->append("temp C = "       + QString::number(weather1.temp-273.16));
    ui->textEdit->append("pressure hPa (Sea level) = "  + QString::number(weather1.pressure));
    ui->textEdit->append("pressure mmHg (Sea level) = " + QString::number((double)weather1.pressure*0.75));
    ui->textEdit->append("pressure hPa (Grnd level) = "  + QString::number(grnd_level));
    ui->textEdit->append("pressure mmHg (Grnd level) = " + QString::number((double)grnd_level*0.75));
    ui->textEdit->append("humidity % = "   + QString::number(weather1.humidity));
    ui->textEdit->append("wind_speed m/s= " + QString::number(weather1.wind_speed));
    ui->textEdit->append("wind_gust m/s= " + QString::number(weather1.wind_gust));          //
    ui->textEdit->append("wind_deg = "   + QString::number(weather1.wind_deg));
    ui->textEdit->append("dir_angle = "  + QString::number(weather1.directional_angle));
    ui->textEdit->append("sunrise Unix time (UTC) = "    + QString::number(weather1.sunrise));
    ui->textEdit->append("sunset Unix time (UTC) = "     + QString::number(weather1.sunset));


    ui->textEdit->append("sunrise - "+ unixTimeToHumanReadable(weather1.sunrise));
    ui->textEdit->append("sunset - "+ unixTimeToHumanReadable(weather1.sunset));

    ui->textEdit->append(what_is_in_the_sky_ParseData(data));

    ui->textEdit->append(weather1.city + "\n");

    QString ver = version;
    ver.append(" City - ");
    ver.append(weather1.city);
    setWindowTitle(ver);

    //-------------- Form data print ------------------------------
    ui->textEdit_temperatura->clear();
    ui->textEdit_temperatura->setFontWeight(QFont::Bold);
    ui->textEdit_temperatura->setTextColor("green");
    if ((weather1.temp-273.16) < 18){
        ui->textEdit_temperatura->setTextColor("blue");
    }
    if ((weather1.temp-273.16) > 27){
        ui->textEdit_temperatura->setTextColor("DeepPink");
    }
    ui->textEdit_temperatura->setFontPointSize(10);
    ui->textEdit_temperatura->append(QString::number(weather1.temp-273.16) + " °C");


    ui->textEdit_humidity->clear();
    ui->textEdit_humidity->setFontWeight(QFont::Bold);
    ui->textEdit_humidity->setTextColor("green");
    if ((weather1.humidity) < 30 || (weather1.humidity) > 60){
        ui->textEdit_humidity->setTextColor("DeepPink");
    }
    ui->textEdit_humidity->setFontPointSize(10);
    ui->textEdit_humidity->append(QString::number(weather1.humidity) + " %");

    ui->textEdit_pressure->clear();
    ui->textEdit_pressure->setFontWeight(QFont::Bold);
    ui->textEdit_pressure->setTextColor("green");
    ui->textEdit_pressure->setFontPointSize(9);
    ui->textEdit_pressure->append(QString::number(weather1.pressure*0.750) + " мм рт.ст. " +
                                  "(" +QString::number(grnd_level*0.75) + " РЗ)");   //grnd_level*0.75

    ui->textEdit_wind->clear();
    ui->textEdit_wind->setFontWeight(QFont::Bold);
    ui->textEdit_wind->setTextColor("green");
    if (weather1.wind_gust > 15){
        ui->textEdit_wind->setTextColor("DeepPink");
    }
    ui->textEdit_wind->setFontPointSize(10);
    ui->textEdit_wind->append(QString::number(weather1.wind_speed) + " м/с, (пор. "  + QString::number(weather1.wind_gust) + ")");
    ui->textEdit_wind_deg->clear();
    ui->textEdit_wind_deg->setFontWeight(QFont::Bold);
    ui->textEdit_wind_deg->setTextColor("green");
    ui->textEdit_wind_deg->setFontPointSize(10);
    ui->textEdit_wind_deg->append(QString::number(weather1.wind_deg) + " °");

    ui->textEdit_state->clear();
    ui->textEdit_state->setFontWeight(QFont::Bold);
    ui->textEdit_state->setTextColor("green");
    ui->textEdit_state->setFontPointSize(10);
    ui->textEdit_state->append(what_is_in_the_sky_ParseData(data));

    ui->textEdit_Sun_up->clear();
    ui->textEdit_Sun_up->setFontWeight(QFont::Bold);
    ui->textEdit_Sun_up->setTextColor("green");
    ui->textEdit_Sun_up->setFontPointSize(10);
    ui->textEdit_Sun_up->append(unixTimeToHumanReadable(weather1.sunrise));

    ui->textEdit_Sun_down->clear();
    ui->textEdit_Sun_down->setFontWeight(QFont::Bold);
    ui->textEdit_Sun_down->setTextColor("green");
    ui->textEdit_Sun_down->setFontPointSize(10);
    ui->textEdit_Sun_down->append(unixTimeToHumanReadable(weather1.sunset));

    ui->textEdit_duration->clear();
    ui->textEdit_duration->setFontWeight(QFont::Bold);
    ui->textEdit_duration->setTextColor("green");
    ui->textEdit_duration->setFontPointSize(10);

    int duration = weather1.sunset - weather1.sunrise;
    if(ui->radioButton->isChecked()) {
        duration -= 7200;           // -2Hr
    }
    else{
        duration -= 10800;          // -3Hr
    }

    ui->textEdit_duration->append(unixTimeToHumanReadable(duration));


    //--------------- wind direction indicator ---------------

    QString path_image;
//    #ifdef QT_DEBUG     // debug
//       path_image = "D:/Projekt/QT_prj/Sofia_weather/Sofia-weather-QT/sources/wind_arrow/";
//    #endif

//    #ifndef QT_DEBUG    // release
//      //path_image = ":/wind_arrow/";   // do not work???
//      path_image = QDir::currentPath() + "/wind_arrow/";
//    #endif

      path_image = QDir::currentPath() + "/wind_arrow/";


    QString image_name;
    if (weather1.wind_deg>=352 || weather1.wind_deg<7){ image_name = "WA_0.png"; }

    if (weather1.wind_deg>=7 && weather1.wind_deg<22){ image_name = "WA_15.png"; }
    if (weather1.wind_deg>=22 && weather1.wind_deg<37){ image_name = "WA_30.png"; }
    if (weather1.wind_deg>=37 && weather1.wind_deg<52){ image_name = "WA_45.png"; }
    if (weather1.wind_deg>=52 && weather1.wind_deg<67){ image_name = "WA_60.png"; }
    if (weather1.wind_deg>=67 && weather1.wind_deg<82){ image_name = "WA_75.png"; }
    if (weather1.wind_deg>=82 && weather1.wind_deg<97){ image_name = "WA_90.png"; }

    if (weather1.wind_deg>=97 && weather1.wind_deg<112){ image_name = "WA_105.png"; }
    if (weather1.wind_deg>=112 && weather1.wind_deg<127){ image_name = "WA_120.png"; }
    if (weather1.wind_deg>=127 && weather1.wind_deg<142){ image_name = "WA_135.png"; }
    if (weather1.wind_deg>=142 && weather1.wind_deg<157){ image_name = "WA_150.png"; }
    if (weather1.wind_deg>=157 && weather1.wind_deg<172){ image_name = "WA_165.png"; }
    if (weather1.wind_deg>=172 && weather1.wind_deg<187){ image_name = "WA_180.png"; }

    if (weather1.wind_deg>=187 && weather1.wind_deg<202){ image_name = "WA_195.png"; }
    if (weather1.wind_deg>=202 && weather1.wind_deg<217){ image_name = "WA_210.png"; }
    if (weather1.wind_deg>=217 && weather1.wind_deg<232){ image_name = "WA_225.png"; }
    if (weather1.wind_deg>=232 && weather1.wind_deg<247){ image_name = "WA_240.png"; }
    if (weather1.wind_deg>=247 && weather1.wind_deg<262){ image_name = "WA_255.png"; }
    if (weather1.wind_deg>=262 && weather1.wind_deg<277){ image_name = "WA_270.png"; }

    if (weather1.wind_deg>=277 && weather1.wind_deg<292){ image_name = "WA_285.png"; }
    if (weather1.wind_deg>=292 && weather1.wind_deg<307){ image_name = "WA_300.png"; }
    if (weather1.wind_deg>=307 && weather1.wind_deg<322){ image_name = "WA_315.png"; }
    if (weather1.wind_deg>=322 && weather1.wind_deg<337){ image_name = "WA_330.png"; }
    if (weather1.wind_deg>=337 && weather1.wind_deg<352){ image_name = "WA_345.png"; }

    QPixmap imagine (path_image + image_name);

    QSize PicSize(40, 40);  // resize picture
    imagine = imagine.scaled(PicSize,Qt::KeepAspectRatio);
    ui->label_10->setPixmap(imagine);
    ui->label_10->repaint();
    ui->label_10->setPixmap(imagine);

    qDebug() << "path_image = " << path_image + image_name;

}


#include "plot_window.h"
#include <ui_plot_window.h>
#include "mainwindow.h"

plot_window::plot_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plot_window)
{
    ui->setupUi(this);

    // temperature
    ui->temp->addGraph();
    ui->temp->graph(0);
    ui->temp->graph(1);
    ui->temp->setInteraction(QCP::iRangeZoom,true);     // Включаем взаимодействие удаления/приближения
    ui->temp->setInteraction(QCP::iRangeDrag, true);    // Включаем взаимодействие перетаскивания графика
    //ui->temp->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->temp->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->temp->xAxis->setLabel("Години");
    ui->temp->xAxis->setRange(0, cnt_point_plot);
    ui->temp->yAxis->setLabel("Темп. (℃)");
    ui->temp->yAxis->setRange(-25, +35);

    // speed wind
    ui->speedwind->addGraph();
    ui->speedwind->graph(0);
    ui->speedwind->graph(1);
    ui->speedwind->setInteraction(QCP::iRangeZoom,true);     // Включаем взаимодействие удаления/приближения
    ui->speedwind->setInteraction(QCP::iRangeDrag, true);    // Включаем взаимодействие перетаскивания графика
    //ui->speedwind->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->speedwind->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->speedwind->xAxis->setLabel("Години");
    ui->speedwind->xAxis->setRange(0, cnt_point_plot);
    ui->speedwind->yAxis->setLabel("Шв. вітру (м/с)");
    ui->speedwind->yAxis->setRange(0, 15);


    // deflection wind
    ui->deflWind->addGraph();
    ui->deflWind->setInteraction(QCP::iRangeZoom,true);     // Включаем взаимодействие удаления/приближения
    ui->deflWind->setInteraction(QCP::iRangeDrag, true);    // Включаем взаимодействие перетаскивания графика
    //ui->deflWind->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->deflWind->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->deflWind->xAxis->setLabel("Години");
    ui->deflWind->xAxis->setRange(0, cnt_point_plot);
    ui->deflWind->yAxis->setLabel("Напр. вітру (°)");
    ui->deflWind->yAxis->setRange(0, 360);


    // pressure
    ui->pressure->addGraph();
    ui->pressure->graph(0);
    ui->pressure->graph(1);
    ui->pressure->setInteraction(QCP::iRangeZoom,true);     // Включаем взаимодействие удаления/приближения
    ui->pressure->setInteraction(QCP::iRangeDrag, true);    // Включаем взаимодействие перетаскивания графика
    //ui->pressure->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->pressure->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->pressure->xAxis->setLabel("Години");
    ui->pressure->xAxis->setRange(0, cnt_point_plot);
    ui->pressure->yAxis->setLabel("Тиск (мм.рт.ст.)");
    ui->pressure->yAxis->setRange(705, 805);

    // humidity
    ui->humidity->addGraph();
    ui->humidity->graph(0);
    ui->humidity->graph(1);
    ui->humidity->setInteraction(QCP::iRangeZoom,true);     // Включаем взаимодействие удаления/приближения
    ui->humidity->setInteraction(QCP::iRangeDrag, true);    // Включаем взаимодействие перетаскивания графика
    //ui->humidity->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->humidity->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->humidity->xAxis->setLabel("Години");
    ui->humidity->xAxis->setRange(0, cnt_point_plot);
    ui->humidity->yAxis->setLabel("Відн. вол. (%)");
    ui->humidity->yAxis->setRange(20, 100);

    ui->label_Tmin->setText("");
    ui->label_Smin->setText("");
    ui->label_Dmin->setText("");
    ui->label_Pmin->setText("");
    ui->label_Hmin->setText("");


}

plot_window::~plot_window()
{

    delete ui;
}


double Tmin, Tmax, Smin, Smax, Dmin, Dmax, Pmin, Pmax, Hmin, Hmax= 0;

void plot_window::plot_g1(double temp, double speedwind, double deflWind, double pressure, double humidity, int count){

    setWindowTitle("Графік змін метеоданних. Оновлено " +QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy"));


    if (count > cnt_point_plot){
        ui->temp->xAxis->     setRange(count-cnt_point_plot, count);
        ui->speedwind->xAxis->setRange(count-cnt_point_plot, count);
        ui->deflWind->xAxis-> setRange(count-cnt_point_plot, count);
        ui->pressure->xAxis-> setRange(count-cnt_point_plot, count);
        ui->humidity->xAxis-> setRange(count-cnt_point_plot, count);
    }

    ui->temp     ->graph(0)->addData(count, temp);
    ui->speedwind->graph(0)->addData(count, speedwind);
    ui->deflWind ->graph(0)->addData(count, deflWind);
    ui->pressure ->graph(0)->addData(count, pressure);
    ui->humidity ->graph(0)->addData(count, humidity);

    ui->temp     ->replot();
    ui->speedwind->replot();
    ui->deflWind ->replot();
    ui->pressure ->replot();
    ui->humidity ->replot();

    MinMaxPlot(temp,  speedwind,  deflWind,  pressure,  humidity);
    set_the_graph_range(0.5);

}



void plot_window::MinMaxPlot(double temp, double speedwind, double deflWind, double pressure, double humidity){

    if (Tmin==0 && Tmax==0 && Smin==0 && Smax==0 && Dmin==0 && Dmax==0 && Pmin==0 && Pmax==0 && Hmin==0 && Hmax==0){
        Tmax = temp;
        Tmin = temp;
        Smax = speedwind;
        Smin = speedwind;
        Dmax = deflWind;
        Dmin = deflWind;
        Pmax = pressure;
        Pmin = pressure;
        Hmax = humidity;
        Hmin = humidity;

        ui->label_Tmax->setNum(Tmax);
        ui->label_Tmax->setText(ui->label_Tmax->text()+" °C");
        ui->label_Tmin->setNum(Tmin);
        ui->label_Tmin->setText(ui->label_Tmin->text()+" °C");
        ui->label_Smax->setNum(Smax);
        ui->label_Smax->setText(ui->label_Smax->text()+" м/с");
        ui->label_Smin->setNum(Smin);
        ui->label_Smin->setText(ui->label_Smin->text()+" м/с");
        ui->label_Dmax->setNum(Dmax);
        ui->label_Dmax->setText(ui->label_Dmax->text()+" °");
        ui->label_Dmin->setNum(Dmin);
        ui->label_Dmin->setText(ui->label_Dmin->text()+" °");
        ui->label_Pmax->setNum(Pmax);
        ui->label_Pmax->setText(ui->label_Pmax->text()+" ммРст");
        ui->label_Pmin->setNum(Pmin);
        ui->label_Pmin->setText(ui->label_Pmin->text()+" ммРст");
        ui->label_Hmax->setNum(Hmax);
        ui->label_Hmax->setText(ui->label_Hmax->text()+" %");
        ui->label_Hmin->setNum(Hmin);
        ui->label_Hmin->setText(ui->label_Hmin->text()+" %");
    }

    if (temp > Tmax){
        Tmax = temp;
        ui->label_Tmax->setNum(Tmax);
        ui->label_Tmax->setText(ui->label_Tmax->text()+" °C");
    }
    if (temp < Tmin){
        Tmin = temp;
        ui->label_Tmin->setNum(Tmin);
        ui->label_Tmin->setText(ui->label_Tmin->text()+" °C");
    }

    if (speedwind > Smax){
        Smax = speedwind;
        ui->label_Smax->setNum(Smax);
        ui->label_Smax->setText(ui->label_Smax->text()+" м/с");
    }
    if (speedwind < Smin){
        Smin = speedwind;
        ui->label_Smin->setNum(Smin);
        ui->label_Smin->setText(ui->label_Smin->text()+" м/с");
    }

    if (deflWind > Dmax){
        Dmax = deflWind;
        ui->label_Dmax->setNum(Dmax);
        ui->label_Dmax->setText(ui->label_Dmax->text()+" °");
    }
    if (deflWind < Dmin){
        Dmin = deflWind;
        ui->label_Dmin->setNum(Dmin);
        ui->label_Dmin->setText(ui->label_Dmin->text()+" °");
    }

    if (pressure > Pmax){
        Pmax = pressure;
        ui->label_Pmax->setNum(Pmax);
        ui->label_Pmax->setText(ui->label_Pmax->text()+" ммРст");
    }
    if (pressure < Pmin){
        Pmin = pressure;
        ui->label_Pmin->setNum(Pmin);
        ui->label_Pmin->setText(ui->label_Pmin->text()+" ммРст");
    }

    if (humidity > Hmax){
        Hmax = humidity;
        ui->label_Hmax->setNum(Hmax);
        ui->label_Hmax->setText(ui->label_Hmax->text()+" %");
    }
    if (humidity < Hmin){
        Hmin = pressure;
        ui->label_Hmin->setNum(Hmin);
        ui->label_Hmin->setText(ui->label_Hmin->text()+" %");
    }
}


void plot_window::set_the_graph_range(double border){
    // Tmin, Tmax, Smin, Smax, Dmin, Dmax, Pmin, Pmax, Hmin, Hmax
    ui->temp->yAxis->setRange     (Tmin - border, Tmax + border);
    ui->speedwind->yAxis->setRange(Smin - border, Smax + border);
    ui->deflWind->yAxis->setRange (Dmin - border, Dmax + border);
    ui->pressure->yAxis->setRange (Pmin - border, Pmax + border);
    ui->humidity->yAxis->setRange (Hmin - border, Hmax + border);
}











#include "plot_window.h"
#include "ui_plot_window.h"
#include "mainwindow.h"


//extern int count_data;
//extern double weather_data[100][5];



plot_window::plot_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plot_window)
{
    ui->setupUi(this);



    ui->temp->addGraph();
    ui->temp->graph(0);
    ui->temp->graph(1);
    ui->temp->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    ui->temp->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
    ui->temp->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->temp->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    ui->temp->graph()->setPen(QPen(QColor("red")));
    ui->temp->xAxis->setLabel("Time");
    ui->temp->xAxis->setRange(0, cnt_point_plot);
    ui->temp->yAxis->setLabel("Temperature");
    ui->temp->yAxis->setRange(-30, +40);

    ui->temp->setAutoAddPlottableToLegend(0);




    ui->elevWind->addGraph();
    ui->elevWind->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    ui->elevWind->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
    ui->elevWind->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->elevWind->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    ui->temp->graph()->setPen(QPen(QColor("blue")));
    ui->elevWind->xAxis->setLabel("Time");
    ui->elevWind->xAxis->setRange(0, cnt_point_plot);
    ui->elevWind->yAxis->setLabel("Elevation");
    ui->elevWind->yAxis->setRange(0, 360);


}

plot_window::~plot_window()
{
    ui->temp->clearGraphs();
    ui->temp->clearPlottables();
    ui->elevWind->clearGraphs();
    ui->elevWind->clearPlottables();
    ui->temp->replot();
    ui->elevWind->replot();
    delete ui;
}

void plot_window::plot_g1(double (* array)[5] , int count){

    for (int i=0; i < count; i++) {
        ui->temp->    graph(0)->addData( i, array [i][0]);
        ui->elevWind->graph(0)->addData( i, array [i][4]);
    }

    ui->temp->replot();
    ui->elevWind->replot();

}

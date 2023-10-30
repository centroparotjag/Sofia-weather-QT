#include "plot_window.h"
#include <ui_plot_window.h>
#include "mainwindow.h"

int skale_min = 0;

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
    ui->temp->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->temp->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->temp->xAxis->setLabel("Години");
    ui->temp->xAxis->setRange(skale_min, cnt_point_plot);
    ui->temp->yAxis->setLabel("Темп. (℃)");
    ui->temp->yAxis->setRange(-25, +35);

    // speed wind
    ui->speedwind->addGraph();
    ui->speedwind->graph(0);
    ui->speedwind->graph(1);
    ui->speedwind->setInteraction(QCP::iRangeZoom,true);     // Включаем взаимодействие удаления/приближения
    ui->speedwind->setInteraction(QCP::iRangeDrag, true);    // Включаем взаимодействие перетаскивания графика
    ui->speedwind->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->speedwind->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->speedwind->xAxis->setLabel("Години");
    ui->speedwind->xAxis->setRange(skale_min, cnt_point_plot);
    ui->speedwind->yAxis->setLabel("Шв. вітру (м/с)");
    ui->speedwind->yAxis->setRange(0, 15);


    // deflection wind
    ui->deflWind->addGraph();
    ui->deflWind->setInteraction(QCP::iRangeZoom,true);     // Включаем взаимодействие удаления/приближения
    ui->deflWind->setInteraction(QCP::iRangeDrag, true);    // Включаем взаимодействие перетаскивания графика
    ui->deflWind->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->deflWind->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->deflWind->xAxis->setLabel("Години");
    ui->deflWind->xAxis->setRange(skale_min, cnt_point_plot);
    ui->deflWind->yAxis->setLabel("Напр. вітру (°)");
    ui->deflWind->yAxis->setRange(0, 360);

    // pressure
    ui->pressure->addGraph();
    ui->pressure->graph(0);
    ui->pressure->graph(1);
    ui->pressure->setInteraction(QCP::iRangeZoom,true);     // Включаем взаимодействие удаления/приближения
    ui->pressure->setInteraction(QCP::iRangeDrag, true);    // Включаем взаимодействие перетаскивания графика
    ui->pressure->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->pressure->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->pressure->xAxis->setLabel("Години");
    ui->pressure->xAxis->setRange(skale_min, cnt_point_plot);
    ui->pressure->yAxis->setLabel("Тиск (мм.рт.ст.)");
    ui->pressure->yAxis->setRange(705, 805);

    // humidity
    ui->humidity->addGraph();
    ui->humidity->graph(0);
    ui->humidity->graph(1);
    ui->humidity->setInteraction(QCP::iRangeZoom,true);     // Включаем взаимодействие удаления/приближения
    ui->humidity->setInteraction(QCP::iRangeDrag, true);    // Включаем взаимодействие перетаскивания графика
    ui->humidity->axisRect()->setRangeDrag(Qt::Vertical);   // Включаем перетаскивание только по Vertical оси
    ui->humidity->axisRect()->setRangeZoom(Qt::Vertical);   // Включаем удаление/приближение только по Vertical оси
    //ui->humidity->xAxis->setLabel("Години");
    ui->humidity->xAxis->setRange(skale_min, cnt_point_plot);
    ui->humidity->yAxis->setLabel("Відн. вол. (%)");
    ui->humidity->yAxis->setRange(20, 100);

}

plot_window::~plot_window()
{

    delete ui;
}

void plot_window::plot_g1(double (* array)[5] , int count){

    for (int i=0; i < count+1; i++) {
        ui->temp->     graph(0)->addData(i, array [i][0]);
        ui->speedwind->graph(0)->addData(i, array [i][3]);
        ui->deflWind-> graph(0)->addData(i, array [i][4]);
        ui->pressure-> graph(0)->addData(i, array [i][1]);
        ui->humidity-> graph(0)->addData(i, array [i][2]);
    }
    ui->temp->replot();
    ui->speedwind->replot();
    ui->deflWind->replot();
    ui->pressure->replot();
    ui->humidity->replot();
}

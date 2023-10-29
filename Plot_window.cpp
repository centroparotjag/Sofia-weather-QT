#include "plot_window.h"
#include "ui_Plot_window.h"

Plot_window::Plot_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Plot_window)
{
    ui->setupUi(this);
}

Plot_window::~Plot_window()
{
    delete ui;
}






#include "extwindow.h"
#include "ui_extwindow.h"

extWindow::extWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::extWindow)
{
    ui->setupUi(this);
}

extWindow::~extWindow()
{
    delete ui;
}

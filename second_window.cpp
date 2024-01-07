#include "second_window.h"
#include "ui_second_window.h"

Second_window::Second_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Second_window)
{
    ui->setupUi(this);

    movie = new QMovie(":/res/image/Falling_flowers.gif");
    movie->setScaledSize(this->size());
    ui->label_GIF->setMovie(movie);
    ui->label_GIF->show();
    movie->start();

    //ui->label_2->setStyle(QColor::fromRgb(0,120,0));

    ui->label_2->setStyleSheet("QLabel {color: 	#FF69B4 }");   //magenta;
    ui->label_2->setText("Я тебе люблю.");

}





Second_window::~Second_window()
{
    delete ui;
}


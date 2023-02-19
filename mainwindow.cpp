#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "second_window.h"

#include <QtXml/QtXml>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->pushButton, SIGNAL( clicked( bool ) ), SLOT( onGo() ) );
    connect( &m_manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( onFinished( QNetworkReply* ) ) );

    // default set text
   }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onGo() {
    QString urlText = "https://api.openweathermap.org/data/2.5/weather?id=710719&appid=184fb9b7d1a763b9eb3214f10ea05a72";
    //QString urlText = "https://openweathermap.org/current";
    qDebug() << "Working...";

    //------ Print data update time ----------
    ui->textEdit_time_request->clear();
    ui->textEdit_time_request->setFontWeight(QFont::Bold);
    ui->textEdit_time_request->setTextColor("blue");
    ui->textEdit_time_request->setFontPointSize(8);
    ui->textEdit_time_request->append(QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy"));


    //ui->textEdit->clear();  //format.setFontWeight(QFont::Bold);
    ui->textEdit->setFontWeight(QFont::Bold);
    ui->textEdit->setTextColor(QColor::fromRgb(99,184,255));         // QColor::fromRgb(0,20,50)
    ui->textEdit->append( "********************************************************************" );
    ui->textEdit->append( "********************************************************************");
    ui->textEdit->append(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss") + "\n");
    ui->textEdit->append( "urlText - " + urlText + "\n" );

    m_manager.get( QNetworkRequest( QUrl( urlText ) ) );
}

void MainWindow::onFinished( QNetworkReply* reply ) {
    if( reply->error() == QNetworkReply::NoError ) {
        QString data = QString::fromUtf8( reply->readAll() );
        ui->textEdit->setTextColor(QColor::fromRgb(255,69,0));
        ui->textEdit->append("XML request:");
        ui->textEdit->setTextColor(QColor::fromRgb(255,99,71));
        ui->textEdit->append( data );

//---------------------------------------------------

        parser_request (data);

    } else {
        qDebug() << reply->errorString();
        ui->textEdit->append( reply->errorString() );
    }

    reply->deleteLater();
}




void MainWindow::on_pushButton_2_clicked()
{
    Second_window window;
    window.setModal(true);
    window.exec();
}

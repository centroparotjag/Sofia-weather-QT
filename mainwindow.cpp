#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "second_window.h"

#include <QtXml/QtXml>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QDebug>

QString version ="V2.1.1 Plot. ";
int id=710719;              // Чернівці default

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(version);

    connect( ui->pushButton, SIGNAL( clicked( bool ) ), SLOT( on_pushButton_clicked() ) );
    connect( ui->radioButton, SIGNAL( clicked( bool ) ), SLOT( onGo() ) );
    connect( ui->comboBox, SIGNAL( clicked( bool ) ), SLOT( onGo() ) );
    connect( &m_manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( onFinished( QNetworkReply* ) ) );


    timer = new QTimer(this);
    timer->setInterval(300000);         // 300000 = 5min  3600000=1h
    connect(timer, SIGNAL(timeout()), this, SLOT(onGo()));
    timer->start();


#ifdef QT_DEBUG     // debug

#endif

#ifndef QT_DEBUG    // release
   // ui -> pushButton -> hide();
#endif

        ui->comboBox->addItem( "Чернівці"        ,"0");
        ui->comboBox->addItem( "Київ"            ,"1");
        ui->comboBox->addItem( "Львів"           ,"2");
        ui->comboBox->addItem( "Дніпро"          ,"3");
        ui->comboBox->addItem( "Харків"          ,"4");
        ui->comboBox->addItem( "Івано-Франківськ","5");
        ui->comboBox->addItem( "Тернопіль"       ,"6");
        ui->comboBox->addItem( "Вінниця"         ,"7");
        ui->comboBox->addItem( "Запоріжжя"       ,"8");
        ui->comboBox->addItem( "Хмельницький"    ,"9");
        ui->comboBox->addItem( "Луцьк"           ,"10");
        ui->comboBox->addItem( "Одеса"           ,"11");
        ui->comboBox->addItem( "Рівне"           ,"12");
        ui->comboBox->addItem( "Полтава"         ,"13");
        ui->comboBox->addItem( "Миколаїв"        ,"14");
        ui->comboBox->addItem( "Черкаси"         ,"15");
        ui->comboBox->addItem( "Житомир"         ,"16");
        ui->comboBox->addItem( "Кропивницький"   ,"17");
        ui->comboBox->addItem( "Чернігів"        ,"18");
        ui->comboBox->addItem( "Суми"            ,"19");
        ui->comboBox->addItem( "Ужгород"         ,"20");
        ui->comboBox->addItem( "Херсон"          ,"21");
        ui->comboBox->addItem( "Донецьк"         ,"22");
        ui->comboBox->addItem( "Луганськ"        ,"23");
        ui->comboBox->addItem( "Сімферополь"     ,"24");
        ui->comboBox->addItem( "Мала Токмачка"   ,"25");

        // read settings from register
        /* При создании главного окна производим установку начальных параметров
          * из настроек, сохранённых в операционной системе
          * */
        QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
         /* Устанавливаем состояние чекбокса из настроек приложения по заданному ключу.
            * Если ключ не существует, то будет установлен параметр по умолчанию,
           * то есть false
         * */
        ui->radioButton->setChecked(settings.value(SETTINGS_SummerVinter, false).toBool());
        ui->comboBox->setCurrentIndex(settings.value(SETTINGS_CITY, 0).toInt());
        on_comboBox_activated(ui->comboBox->currentIndex());


        ui->pushButton->setToolTip("Виведення графіків змін метеоданних.\n"
                                    "Накопичення данних відбувається від моменту запуску програми до її закриття.\n"
                                    "Оновлення метеоданних на графіку відбувається з періодичністю в 1 год.\n"
                                    "Оновлення метеоданних в основному вікні відбувається з періодичністю в 5хв.");
        ui->pushButton_2->setToolTip("Сюрприз для Софійки і не тільки...))");
        ui->radioButton->setToolTip("Встановлює часовий пояс літо/зима. \n"
                                    "Використовується для коректного відображення часу - сходу/заходу сонця.");
        ui->comboBox->setToolTip   ("Вибір населенного пункту для відображення погоди.\n"
                                    "В списку всі обласні центри України.");

        ui->textEdit_time_request->setToolTip("Відображення часу крайнього оновлення метеоданних головного вікна.\n"
                                              "Період оновлення метеоданних становить 5хв.");


        ui->textEdit_temperatura->setToolTip("Відображення температури в градусах цельсія.");
        ui->textEdit_humidity->setToolTip   ("Відображення відносної вологості у відсотках.");
        ui->textEdit_pressure->setToolTip   ("Відображення атмосферного тиску на рівні моря в міліметрах ртутного стовпа.\n"
                                             "Відображення атмосферного тиску на рівні землі -РЗ.");
        ui->textEdit_wind->setToolTip   ("Відображення сили вітру в метрах за секунду.");
        ui->textEdit_wind_deg->setToolTip   ("Відображення напрямку вітру в градусах (360°).");
        ui->textEdit_state->setToolTip      ("Відображення станну неба: ясно, хмарно, дощь ...");
   }

MainWindow::~MainWindow()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    if (ui->radioButton->isChecked() != settings.value(SETTINGS_SummerVinter).toBool()){
        qDebug() << "SETTINGS_SummerVinter є зміни " << ui->radioButton->isChecked()
                 << "!= " << settings.value(SETTINGS_SummerVinter).toBool();
        qDebug() << "Write SummerVinters in register ";
        //--------- write settings in register -----------------------
        if(ui->radioButton->isChecked()){
            settings.setValue(SETTINGS_SummerVinter, true);
        } else {
            settings.setValue(SETTINGS_SummerVinter, false);
        }
        settings.sync();
    }

    if (ui->comboBox->currentIndex() != settings.value(SETTINGS_CITY).toInt()){
        qDebug() << "SETTINGS_CITY є зміни " << ui->comboBox->currentIndex()
                 << "!= " <<   settings.value(SETTINGS_CITY).toInt();
        qDebug() << "Write sity in register ";

        //--------- write settings in register -----------------------
        settings.setValue(SETTINGS_CITY, ui->comboBox->currentIndex());
        settings.sync();
    }

    qDebug() << "Closed.";

    delete ui;
}


void MainWindow::onGo() {
    // chernivtci
    //QString urlText = "https://api.openweathermap.org/data/2.5/weather?id=710719&appid=184fb9b7d1a763b9eb3214f10ea05a72";

    QString urlText;
    urlText.append(QString("https://api.openweathermap.org/data/2.5/weather?id=%1&appid=184fb9b7d1a763b9eb3214f10ea05a72").arg(id));

    qDebug() << "Working...";

    //ui->textEdit->clear();  //format.setFontWeight(QFont::Bold);
    ui->textEdit->setFontWeight(QFont::Bold);
    ui->textEdit->setTextColor(QColor::fromRgb(29,4,255));         // QColor::fromRgb(0,20,50)
    ui->textEdit->append( "********************************************************************" );
    ui->textEdit->append( "********************************************************************");
    ui->textEdit->append(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss") + "\n");
    ui->textEdit->append( "urlText - " + urlText + "\n" );

//    ui->textEdit_time_request->clear();
//    ui->textEdit_time_request->setFontPointSize(10);
//    ui->textEdit_time_request->setFontWeight(QFont::Bold);
//    ui->textEdit_time_request->setTextColor(QColor::fromRgb(200, 0, 0));
//    ui->textEdit_time_request->append("Оновлення данних");

    m_manager.get( QNetworkRequest( QUrl( urlText ) ) );
}

void MainWindow::onFinished( QNetworkReply* reply ) {
    if( reply->error() == QNetworkReply::NoError ) {

        //------ Print data update time ----------
        ui->textEdit_time_request->clear();
        ui->textEdit_time_request->setFontPointSize(10);
        ui->textEdit_time_request->setFontWeight(QFont::Bold);
        ui->textEdit_time_request->setTextColor(QColor::fromRgb(0, 0, 0));
        ui->textEdit_time_request->append("Оновлено " +QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy"));

        QString data = QString::fromUtf8( reply->readAll() );
        ui->textEdit->setTextColor(QColor::fromRgb(200,0,0));
        ui->textEdit->append("XML request:");
        ui->textEdit->setTextColor(QColor::fromRgb(200,0,0));
        ui->textEdit->append( data );
        parser_request (data);

        timer->setInterval(300000);         // 300000 = 5min  3600000=1h
    } else {
        qDebug() << "Not answer " << reply->errorString();
        ui->textEdit->append( reply->errorString() );
        timer->setInterval(1000);         // 300000 = 5min  3600000=1h
    }
    reply->deleteLater();
}


void MainWindow::on_pushButton_2_clicked()
{
    Second_window window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_comboBox_activated(int index)
{

    switch (index) {
        case 0:  id=710719; break;      //"Чернівці"
        case 1:  id=703448; break;      //"Київ"
        case 2:  id=702550; break;      //"Львів"
        case 3:  id=709930; break;      //"Дніпро"
        case 4:  id=706483; break;      //"Харків"
        case 5:  id=707471; break;      //"Івано-Франківськ"
        case 6:  id=691650; break;      //"Тернопіль"
        case 7:  id=689558; break;      //"Вінниця"
        case 8:  id=687700; break;      //"Запоріжжя"
        case 9:  id=706369; break;      //"Хмельницький"
        case 10: id=702569; break;      //"Луцьк"
        case 11: id=4166787; break;      //"Одеса"
        case 12: id=7046809; break;      //"Рівне"
        case 13: id=696643; break;      //"Полтава"
        case 14: id=700568; break;      //"Миколаїв"
        case 15: id=710791; break;      //"Черкаси"
        case 16: id=686967; break;      //"Житомир"
        case 17: id=705812; break;      //"Кропивницький"
        case 18: id=710735; break;      //"Чернігів"
        case 19: id=692194; break;      //"Суми"
        case 20: id=690548; break;      //"Ужгород"
        case 21: id=706448; break;      //"Херсон"
        case 22: id=709717; break;      //"Донецьк"
        case 23: id=702658; break;      //"Луганськ"
        case 24: id=693805; break;      //"Сімферополь"
        case 25: id=702153; break;      //"Мала Токмачка"

        default: id=710719; break;      //"Чернівці"
    }
    onGo();
}

void MainWindow::on_pushButton_clicked()
{
    plot_window.show();
}



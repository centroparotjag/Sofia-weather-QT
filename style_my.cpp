#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::style_my(void){
    //-------------------------------------------------------------------------------------------------
    ui->pushButton->setStyleSheet("QPushButton{"
                                   "height: 26px;"
                                   "width: 120px;"
                                   "color:rgba(0,0,0,255);"     // font colour
                                   "border-radius: 5px;"
                                   "background-color:rgba(240, 240, 240, 255);"
                                   "border-top: 2px solid rgba(255, 255, 255, 255);"
                                   "border-left: 2px solid rgba(255, 255, 255, 255);"
                                   "border-right: 2px solid rgba(160, 160, 160, 255);"
                                   "border-bottom: 2px solid rgba(160, 160, 160, 255);"
                                   "}"
                                   "QPushButton::pressed {background-color:rgba(230, 230, 230, 255);"
                                   "border-top: 2px solid rgba(160, 160, 160, 255);"
                                   "border-left: 2px solid rgba(160, 160, 160, 255);"
                                   "border-right: 2px solid rgba(255, 255, 255, 255);"
                                   "border-bottom: 2px solid rgba(255, 255, 255, 255); }" );

    ui->pushButton_2->setStyleSheet("QPushButton{"
                                   "height: 26px;"
                                   "width: 120px;"
                                   "color:rgba(0,0,0,255);"     // font colour
                                    "border-radius: 5px;"
                                   "background-color:rgba(240, 240, 240, 255);"
                                   "border-top: 2px solid rgba(255, 255, 255, 255);"
                                   "border-left: 2px solid rgba(255, 255, 255, 255);"
                                   "border-right: 2px solid rgba(160, 160, 160, 255);"
                                   "border-bottom: 2px solid rgba(160, 160, 160, 255);"
                                   "}"
                                   "QPushButton::pressed {background-color:rgba(230, 230, 230, 255);"
                                   "border-top: 2px solid rgba(160, 160, 160, 255);"
                                   "border-left: 2px solid rgba(160, 160, 160, 255);"
                                   "border-right: 2px solid rgba(255, 255, 255, 255);"
                                   "border-bottom: 2px solid rgba(255, 255, 255, 255);}" );

    //-------------------------------------------------------------------------------------------------
    ui->comboBox->setStyleSheet("QComboBox{"
                                   "border-top: 2px solid rgba(160, 160, 160, 255);"
                                   "border-left: 2px solid rgba(160, 160, 160, 255);"
                                   "border-right: 2px solid rgba(255, 255, 255, 255);"
                                   "border-bottom: 2px solid rgba(255, 255, 255, 255);"
                                   "background:rgba(240, 240, 240, 255);"
                                    "border-radius: 5px;"
                                    "padding: 1px 18px 1px 3px;"
                                    "min-width: 6em;" "}"
                                    "QComboBox:!editable:on, QComboBox::drop-down:editable:on {"
                                    "background-color:rgba(230, 230, 230, 255);}"
                                    "QComboBox QAbstractItemView {"
                                    "border: 2px solid darkgray;"
                                    "selection-background-color:rgba(111, 111, 111, 255); }" );

    //-------------------------------------------------------------------------------------------------
    ui->tabWidget->setStyleSheet("QTabWidget::pane {" /* The tab widget frame */
                                    "border-top: 2px solid rgba(160, 160, 160, 255);"
                                    "border-left: 2px solid rgba(160, 160, 160, 255);"
                                    "border-right: 2px solid rgba(255, 255, 255, 255);"
                                    "border-bottom: 2px solid rgba(255, 255, 255, 255);"
                                    "}"
//                                  "QTabWidget::tab-bar {"
//                                     "left: 0px;" /* move to the right by 5px */
//                                    "}"


                                "QTabBar::tab {"
                                    "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 0,"
                                                "stop: 0 #E1E1E1, stop: 0.1 #DDDDDD,"
                                                "stop: 0.5 #E6E6E6, stop: 1.0 #D3D3D3);"
                                    "border: 2px solid #A0A0A0;"
                                    "border-bottom-color: #E6E6E6;" /* same as the pane color */
                                    "border-top-left-radius: 4px;"
                                    "border-top-right-radius: 4px;"
                                    "min-width: 0ex;"
                                    "padding: 1px;"
                                    "}"

                                "QTabBar::tab:selected, QTabBar::tab:hover {"
                                     "background:rgba(240, 240, 240, 255)"
                                     "}"

                                "QTabBar::tab:selected {"
                                     "border-color: #9B9B9B;"
                                     "border-bottom-color: #E6E6E6;" /* такой же цвет как у панели */
                                "}"

//                                "QTabBar::tab:!selected {"
//                                    "margin-top: 2px;" /* делаем невыбранные вкладки меньше */
//                                 "}"

                                /* воспользуемся отрицательными полями для перекрывания вкладок */
                                "QTabBar::tab:selected {"
                                    /* расширение/перекрытие слева и справа по 4px */
                                    "margin-left: 2px;"
                                    "margin-right: 2px;"
                                "}"

                                "QTabBar::tab:first:selected {"
                                     "margin-left: 0;" /* первая выбранная вкладка ничего не перекрывает слева от себя */
                                "}"

                                "QTabBar::tab:last:selected {"
                                     "margin-right: 0;" /* последняя выбранная вкладка ничего не перекрывает справа от себя */
                                "}"

                                "QTabBar::tab:only-one {"
                                     "margin: 0;" /* если имеется только одна вкладка, перекрывающиеся поля не нужны */
                                "}"
         );

    //-----------------------------------------------------------------------------------------
         ui->groupBox->setStyleSheet("QGroupBox {"
                                         "border: 1px solid #a0a0a0;"
                                         "border-radius: 0px;"
                                         "margin-top: 0ex;" /* leave space at the top for the title */
                                     "}"
         );
    //--------------------------------------------------------------------
        ui->textEdit->setStyleSheet("QTextEdit, QListView {"
                                        "background-color: #f0f0f0;"
                                           "border-top: 2px solid rgba(160, 160, 160, 255);"
                                           "border-left: 2px solid rgba(160, 160, 160, 255);"
                                           "border-right: 2px solid rgba(255, 255, 255, 255);"
                                           "border-bottom: 2px solid rgba(255, 255, 255, 255);"
                                      "}"
        );
    //---------------------------------------------------------------------

        ui->radioButton->setStyleSheet("QRadioButton::indicator::unchecked{"
                                            "border: 1px solid;"
                                            "border-color: rgb(0,0,0);"
                                            "background-color: rgb(230, 230, 230);"
                                            "}"
                                        "QRadioButton::indicator::checked{"
                                            "border: 1px solid;"
                                            "border-color: rgb(0,0,0);"
                                            "background-color: rgb(0,128,0);"
                                            "}"
                                        );

}

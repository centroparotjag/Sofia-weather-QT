QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = WeatherInformerForSofia

QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Parser_request.cpp \
    UNIX_TIME.cpp \
    extwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    second_window.cpp



HEADERS += \
    extwindow.h \
    mainwindow.h \
    second_window.h

FORMS += \
    extwindow.ui \
    mainwindow.ui \
    second_window.ui

RC_FILE = appIcon.rc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

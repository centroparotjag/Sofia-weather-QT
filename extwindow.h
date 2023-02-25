#ifndef EXTWINDOW_H
#define EXTWINDOW_H

#include <QMainWindow>

namespace Ui {
class extWindow;
}

class extWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit extWindow(QWidget *parent = nullptr);
    ~extWindow();

private:
    Ui::extWindow *ui;
};

#endif // EXTWINDOW_H

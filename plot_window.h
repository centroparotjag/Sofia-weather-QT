#ifndef PLOT_WINDOW_H
#define PLOT_WINDOW_H

#include <QWidget>
#include <QFileDialog>


namespace Ui {
class plot_window;
}

class plot_window : public QWidget
{
    Q_OBJECT

public:
    explicit plot_window(QWidget *parent = nullptr);
    ~plot_window();

private:
    Ui::plot_window *ui;

public:    
    void plot_g1(double temp, double speedwind, double deflWind, double pressure, double humidity, int count);
};

#endif // PLOT_WINDOW_H

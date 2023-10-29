#ifndef PLOT_WINDOW_H
#define PLOT_WINDOW_H

#include <QWidget>

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
};

#endif // PLOT_WINDOW_H

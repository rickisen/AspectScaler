#ifndef ASPECTSCALER_H
#define ASPECTSCALER_H

#include <QMainWindow>

namespace Ui {
class AspectScaler;
}

class AspectScaler : public QMainWindow
{
    Q_OBJECT

public:
    explicit AspectScaler(QWidget *parent = 0);
    ~AspectScaler();

private slots:
    void NewW(QString) ;
    void NewH(QString) ;
    void updateAspectScale(int);

    void on_ButtonNext_clicked();

    void on_ButtonPrev_clicked();

private:
    Ui::AspectScaler *ui;
};



#endif // ASPECTSCALER_H

#include "aspectscaler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AspectScaler w;
    w.show();

    return a.exec();
}

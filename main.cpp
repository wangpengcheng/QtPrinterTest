#include "mainwindow.h"
#include <QApplication>
#include "picwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    PicWidget win;
    win.show();
    return a.exec();
}

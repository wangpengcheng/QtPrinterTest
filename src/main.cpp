#include "mainwindow.h"
#include <QApplication>
#include "picwidget.h"
#include <QtGui/private/qzipreader_p.h>
#include <QString>
#include <QtDebug>
#include <QFileDialog>
#include <src/filesloader.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
  //  PicWidget win;
  //  win.show();
    QString file_path="F:/GitHub/QtPrinterTest/barcode (1).zip";
    qDebug()<<file_path;
    FilesLoader files_loader_test(file_path);
    files_loader_test.show();
    files_loader_test.InitFileDialog();
    files_loader_test.UnZipDir();
    return a.exec();
}

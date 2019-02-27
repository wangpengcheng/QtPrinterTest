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
    //PicWidget win;
   // win.show();
    QString file_path="F:/GitHub/QtPrinterTest/barcode (1).zip";
    qDebug()<<file_path;
    FilesLoader files_loader_test;
    files_loader_test.show();
    //files_loader_test.InitFileDialog();
    //files_loader_test.UnZipDir();
    //files_loader_test.PrintFiles();
    //auto result=files_loader_test.SavePathList("F:/GitHub/QtPrinterTest/");
    return a.exec();
}

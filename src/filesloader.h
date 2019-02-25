#ifndef FILESLOADER_H
#define FILESLOADER_H

/****************************************************************************
** @projectName   QtPrinterTest
** QT Version    5.11.1
** This file is part of the QtPrinterTest project.
** @file          filesloader.h
** @brief         this file is header file of FilesLoader class
** @details       FileLoader class is to find and unzip all image files ,and return those file path
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/QtPrinterTest
** @date          2019-02-24 周日  21:40:07
** @example
**
** 示例代码
**
*****************************************************************************/
#include <QList>
#include <QFile>
#include <QString>
//using qzip
#include <QtGui/private/qzipreader_p.h>
#include <QtWidgets>
#include <QFileDialog>
#include <QDir>
class FilesLoader: public QWidget
{
public:
    FilesLoader();
    FilesLoader(const QString dir_path);
    ~FilesLoader();
    inline QString root_dir_path() { return root_dir_path_;}
    inline void set_root_dir_path(const QString dir_path){ root_dir_path_=dir_path;}
    void InitFileDialog();
    void UnZipDir();//this function is to unzip file
    void SavePathList();//searech all file in unzip dirceatroy
    void PrintFiles();//this function is to use printer tp print image;
    QList<QString> file_path_list(){ return file_path_list_;}//return file_path_list;
private:
    QList<QString> file_path_list_;//this member is to loader image file abosult path list
    QString root_dir_path_=nullptr; //the root directory path;
    QFileDialog choose_dialog_;
};

#endif // FILESLOADER_H

#include "filesloader.h"

FilesLoader::FilesLoader()
{
    choose_dialog_.setParent(this);
}
FilesLoader::FilesLoader(const QString dir_path)
{
    this->root_dir_path_=dir_path;
}
FilesLoader::~FilesLoader()
{

}
void FilesLoader::UnZipDir()
{

    //if this file path is empty
    if(this->root_dir_path_!=nullptr)
    {
        QZipReader unziper_(this->root_dir_path_);

        //unzip dirceatroy path
        QString unziped_dir_path=this->root_dir_path_.replace(".zip","");
        //QString unziped_dir_path="F:/GitHub/QtPrinterTest/barcode (1)";
        qDebug()<<unziped_dir_path;
        //check this dirceatroy is exsit;
        QDir temp_dir;
        if (!temp_dir.exists(unziped_dir_path))
        {
            bool res=temp_dir.mkpath(unziped_dir_path);
            qDebug() << "create folder is success ?" << res;
        }
        unziper_.extractAll(unziped_dir_path);//unzip file
        QVector< QZipReader::FileInfo > file_list=unziper_.fileInfoList();
        for(int i=0;i<file_list.length();++i)
        {
            qDebug()<<file_list.at(i).filePath;
        }
        unziper_.close();
        qDebug()<<"unzip endl";
   }else {
        qDebug()<<"Please check the file path !";
    }
}
void FilesLoader::InitFileDialog()
{
    QString cur_path=QDir::homePath();//get application file path
    QString dialog_title=QString::fromLocal8Bit("选择一个文件");
    QString filter=QString::fromLocal8Bit("压缩文件(.zip);;图片文件(*.jpg*.gif*.png*.bmp);;所有文件(*.*)");
    QUrl file_path=QFileDialog::getOpenFileUrl(this,dialog_title,cur_path,filter);
    if(!file_path.isEmpty()){
        this->root_dir_path_=file_path.toString().replace("file:///","");//change file path;
        qDebug()<<root_dir_path_;
    }

}
void FilesLoader::PrintFiles()
{

}

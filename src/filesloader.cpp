#include "filesloader.h"

FilesLoader::FilesLoader()
{
    //set window size
    int p_width=350,p_height=90;
    resize(p_width,p_height);
    setWindowTitle(QString::fromLocal8Bit("快捷打印工具"));
    //button1,button2
    get_file_button=new QPushButton(QString::fromLocal8Bit("选择文件"),this);
    print_button=new QPushButton(QString::fromLocal8Bit("打印文件"),this);
    //txtbox;
    show_path_line_edit=new QLineEdit(this);
    show_path_line_edit->setPlaceholderText(QString::fromLocal8Bit("文件路径"));
    show_path_line_edit->setReadOnly(true);//not allow input
    show_path_line_edit->setStyleSheet("background-color: #cccccc;");
    //set position
    show_path_line_edit->setGeometry(p_width/10,p_height/10,p_width*0.8,this->height()*0.4);
    get_file_button->setGeometry(p_width/10,p_height/10+show_path_line_edit->height()+3,(show_path_line_edit->width()-10)/2,this->height()*0.4);
    print_button->setGeometry(p_width/10+get_file_button->width()+8,p_height/10+show_path_line_edit->height()+3,(show_path_line_edit->width()-10)/2,this->height()*0.4);
    //print_button->setGeometry(70, 40, 50, 30);
    //set connect function;
    connect(get_file_button,SIGNAL(clicked()),this,SLOT(InitFileDialog()));
    connect(print_button,SIGNAL(clicked()),this,SLOT(PrintFiles()));
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
            QString temp_path=unziped_dir_path+"/"+file_list.at(i).filePath;
            qDebug()<<temp_path;
            file_path_list_.append(temp_path);//add path to list;
        }
        qDebug()<<this->file_path_list_;

        unziper_.close();
        qDebug()<<"unzip endl";
   }else {
        qDebug()<<"Please check the file path !";
    }
}
void FilesLoader::InitFileDialog()
{
    if(!file_path_list_.isEmpty())
    {
        file_path_list_.clear();
        qDebug()<<"this file list cleaned";
    }
    QString cur_path=QDir::homePath();//get application file path
    QString dialog_title=QString::fromLocal8Bit("选择一个文件");
    QString filter=QString::fromLocal8Bit("压缩文件(*.zip);;图片文件(*.jpg*.gif*.png*.bmp);;所有文件(*.*)");
    QUrl file_path=QFileDialog::getOpenFileUrl(this,dialog_title,cur_path,filter);
    if(!file_path.isEmpty()){
        this->root_dir_path_=file_path.toString().replace("file:///","");//change file path;
        qDebug()<<root_dir_path_;
    }
    //show file path
    this->show_path_line_edit->setPlaceholderText(root_dir_path_);
    this->UnZipDir();
}
void FilesLoader::PrintFiles()
{
    //---打印新对象
	QPrinter printer;
    //set page size;
    //printer.setPageSize(QPageSize(QSize(355,224)));
    //printer.setPageSize(QPageSize(QPageSize::A4));
	//QPrintDialog printDlg(&printer, this);
    // 用于判断用户是否点击“打印”按钮
    QPrintPreviewDialog preview(&printer, this);
    preview.setMinimumSize(1000,600);
    connect(&preview,SIGNAL(paintRequested(QPrinter*)),this,SLOT(PrintPreviewSlot(QPrinter*)));
    preview.exec();
//	//if (printDlg.exec())
//    if (preview.exec())
//	{
//		QPainter painter;
//        painter.begin(&printer);
//        for(int i=0;i<temp_img_list.size();++i)
//        {
//            QImage img=temp_img_list.at(i);
//            QRect rect = painter.viewport();	//---获取Qpainter对象的矩形区域
//            QSize size = img.size();		//--获取图片的大小
//            size.scale(rect.size(), Qt :: KeepAspectRatio);		//----按照图形比例大小重新设置视口矩形区域
//            //---打印图片
//            painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
//            painter.setWindow(img.rect());
//            painter.drawImage(0, 0, img);
//            painter.isActive();
//            if(i!=temp_img_list.size()-1)
//            {
//                printer.newPage();
//            }
//        }
//        painter.end();

//	}



}
void FilesLoader::PrintPreviewSlot(QPrinter *printer1)
{
    //set painter
    QPainter painter;
    painter.begin(printer1);
    if(this->file_path_list_.isEmpty())
    {
         qDebug()<<"this file_path is wrrong";
    }else {
        for(int i=0;i<file_path_list_.length();++i)
        {
            QImage img(file_path_list_.at(i));
            if(img.isNull())
            {
                qDebug()<<"can not load image file ";

            }else {
                //set image size;
                QRect rect = painter.viewport();	//get Qpainter view rect
                QSize size = img.size();		//--get image size
                size.scale(rect.size(), Qt :: KeepAspectRatio);		//----按照图形比例大小重新设置视口矩形区域
                //---print image
                painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
                painter.setWindow(img.rect());
                painter.drawImage(0, 0, img);
                painter.isActive();
            }
            if(i!=file_path_list_.length()-1)
            {
                printer1->newPage();
            }
        }
        painter.end();
        qDebug()<<"painter end";
    }
}
QList<QString> FilesLoader::SavePathList(QString dir_path)
{
    QList<QString> result;
    QDir root_dir(dir_path);
    if (!root_dir.exists())
    {
        qDebug()<<"this dirceattroy is not exists";
    }
    root_dir.setFilter(QDir::Dirs|QDir::Files);//除了目录或文件，其他的过滤掉
    root_dir.setSorting(QDir::DirsFirst);//优先显示目录
    QFileInfoList file_list = root_dir.entryInfoList();//获取文件信息列表
    int i=0;
    do{
        QFileInfo fileInfo = file_list.at(i);
        if(fileInfo.fileName()=="."|fileInfo.fileName()=="..")
        {
            ++i;
            continue;
        }
        if (fileInfo.isDir())
        {
            //fileInfo.size(),fileInfo.fileName(),fileInfo.path()
            result.append(this->SavePathList(fileInfo.filePath()));
        }else{
            result.append(fileInfo.filePath());
        }
        ++i;
    } while(i<file_list.size());
    for(int i=0;i<result.length();++i)
    {
        qDebug()<<result.at(i);
    }
    return result;
}

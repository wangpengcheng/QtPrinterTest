#include "picwidget.h"
#include <QtDebug>
#include <QPrintPreviewDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QLineEdit>
PicWidget::PicWidget(QWidget *parent /*= 0*/) : QWidget(parent)
{
	//---按钮
	pintPicBtn = new QPushButton("print", this);
    //设置按钮位置
	pintPicBtn->setGeometry(70, 40, 50, 30);
    //连接信号和槽
	//connect(pintPicBtn, SIGNAL(clicked()), this, SLOT(slotPrintPic()));
    connect(pintPicBtn,SIGNAL(clicked()),this,SLOT(SavePDFFile()));
	//--导入图片
	img.load("C:/Users/lin/Desktop/123.png");
    qDebug()<<img.isNull();
    if(!img_list_.isEmpty())
    {
        img_list_.clear();
    };
    //初始化图片数据
    for(int i=0;i<3;++i)
    {
        QImage temp_img;
        auto load_result=temp_img.load("C:/Users/lin/Desktop/123.png");
        //if load successful
        if(load_result){
            img_list_.append(temp_img);
        }
    }
    qDebug()<<img_list_.size();
    qDebug()<<img_list_.at(2).isNull();
	//---窗口属性
	resize(200, 100);
}

//---按钮槽函数
void PicWidget::slotPrintPic()
{

    //---打印新对象
	QPrinter printer;
    //设置打印选择框
	//QPrintDialog printDlg(&printer, this);
    //set printer
    qDebug()<<printer.paperRect();
    //set page
    printer.setPageSize(QPageSize(QPageSize::A4));
    //set print view;
    QPrintPreviewDialog preview(&printer, this);
    preview.setMinimumSize(1000,600);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreviewSlot(QPrinter*)));
    preview.exec ();
//    // 用于判断用户是否点击“打印”按钮
//	if (printDlg.exec())
//	{
//		 QPainter painter;
//        painter.begin(&printer);
//        for(int i=0;i<this->img_list_.size();++i)
//        {
//            QRect rect = painter.viewport();	//---获取Qpainter对象的矩形区域
//            QSize size = img.size();		//--获取图片的大小
//            size.scale(rect.size(), Qt :: KeepAspectRatio);		//----按照图形比例大小重新设置视口矩形区域
//            //--打印图片
//            painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
//            painter.setWindow(img.rect());
//            painter.drawImage(0, 0, img);
//            painter.isActive();
//            if(i!=this->img_list_.size()-1)
//            {
//                printer.newPage();
//            }
//        }
//        painter.end();

//	}


}
void PicWidget::printPreviewSlot(QPrinter *printerPixmap)
{
    printerPixmap->setOrientation(QPrinter::Landscape);
        //获取界面的图片
    QPainter painter;
    painter.begin(printerPixmap);
    QRect rect = painter.viewport();	//---获取Qpainter对象的矩形区域
    QSize size = img.size();		//--获取图片的大小
    size.scale(rect.size(), Qt :: KeepAspectRatio);		//----按照图形比例大小重新设置视口矩形区域
    //--打印图片
    painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
    painter.setWindow(img.rect());
    painter.drawImage(0, 0, img);
    painter.isActive();
    painter.end();


}
void PicWidget::SavePDFFile()
{
    //QString fileName = QFileDialog::getSaveFileName(this, tr("保存PDF文件"), QString(), "*.pdf");
    QString fileName="F:/GitHub/QtPrinterTest/test.pdf";
    qDebug()<<fileName;

        if (!fileName.isEmpty())
        {
            // 如果文件后缀为空，则默认使用.pdf
            if (QFileInfo(fileName).suffix().isEmpty())
            {
                fileName.append(".pdf");
            }
            QPrinter printer(QPrinter::HighResolution);
            //自定义纸张大小，这里要打印的内容都在stackedWidget上
            //printerPixmap.setPageSize(QPrinter::Custom);
            //printerPixmap.setPaperSize(QSizeF(ui->stackedWidget->height(), ui->stackedWidget->width()), QPrinter::Point);
            //设置纸张大小为A4，这里注释掉了，建议自定义纸张 ，否则保存的就会有很多空白
            printer.setPageSize(QPrinter::A4);
            //横向打印
            //printer.setOrientation(QPrinter::Landscape);
            //设置输出格式为pdf
            printer.setOutputFormat(QPrinter::PdfFormat);
            //设置输出路径
            printer.setOutputFileName(fileName);
            //获取界面的图片
            //QPixmap pixmap = QPixmap::grabWidget(ui->stackedWidget, ui->stackedWidget->rect());
            QPainter painter;
            painter.begin(&printer);
          for(int i=0;i<this->img_list_.size();++i)
          {
              QRect rect = painter.viewport();	//---获取Qpainter对象的矩形区域
              QSize size = img.size();		//--获取图片的大小
              size.scale(rect.size(), Qt :: KeepAspectRatio);		//----按照图形比例大小重新设置视口矩形区域
              //--打印图片
              painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
              painter.setWindow(img.rect());
              painter.drawImage(0, 0, img);
              painter.isActive();
              if(i!=this->img_list_.size()-1)
                  {
                     printer.newPage();
                  }
           }
           painter.end();
            QMessageBox::information(this, tr("生成PDF"), tr("保存PDF文件成功"), QMessageBox::Ok);
        }

}

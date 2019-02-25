#include "picwidget.h"
#include <QtDebug>
PicWidget::PicWidget(QWidget *parent /*= 0*/) : QWidget(parent)
{
	//---按钮
	pintPicBtn = new QPushButton("print", this);
    //设置按钮位置
	pintPicBtn->setGeometry(70, 40, 50, 30);
    //连接信号和槽
	connect(pintPicBtn, SIGNAL(clicked()), this, SLOT(slotPrintPic()));

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
	QPrintDialog printDlg(&printer, this);
    // 用于判断用户是否点击“打印”按钮
	if (printDlg.exec())
	{
		QPainter painter;
        painter.begin(&printer);
        for(int i=0;i<this->img_list_.size();++i)
        {
            QRect rect = painter.viewport();	//---获取Qpainter对象的矩形区域
            QSize size = img.size();		//--获取图片的大小
            size.scale(rect.size(), Qt :: KeepAspectRatio);		//----按照图形比例大小重新设置视口矩形区域
            //---打印图片
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

	}
}

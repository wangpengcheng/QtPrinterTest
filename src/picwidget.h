#ifndef PICWIDGET_H
#define PICWIDGET_H

#include <QPainter>
#include <QWidget>
#include <QPushButton>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QRect>
#include <QImage>
#include <QList>
class PicWidget : public QWidget
{
	Q_OBJECT
public:
	explicit PicWidget(QWidget *parent = nullptr);

	public slots:
		void slotPrintPic();
private:
	QPushButton *pintPicBtn;
	QImage img;
    QList<QImage> img_list_;
};

#endif	//--PICWIDGET_H

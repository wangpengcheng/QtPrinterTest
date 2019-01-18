#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTextDocument>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QPrinter printer;
    QTextDocument doc;

    QFont font("宋体",2);
    doc.setDefaultFont(font);

//    QFont font = doc.defaultFont();
//    font.setBold(true);
//    font.setPointSize(10);
//    doc.setDefaultFont(font);

    QSizeF s = QSizeF(printer.logicalDpiX() * (58 / 25.4),
                      printer.logicalDpiY() * (297 / 25.4));
    doc.setPageSize(s);
    printer.setPageSizeMM(s);
    printer.setOutputFormat(QPrinter::NativeFormat);
    doc.setPlainText("I am jdh!\n打印测试");
    doc.print(&printer);
}

void MainWindow::doPrint()
{
    // 创建打印机对象
    QPrinter printer;
    // 创建打印对话框
    QString printerName = printer.printerName();
    if( printerName.size() == 0)
        return;
    QPrintDialog dlg(&printer, this);
    //如果编辑器中有选中区域，则打印选中区域
    if (ui->textEdit->textCursor().hasSelection())
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    // 如果在对话框中按下了打印按钮，则执行打印操作
    if (dlg.exec() == QDialog::Accepted)
    {
       //ui->textEdit->print(&printer);
       // print the existing document by absoult path
        //printFile("D:/1.doc");

        QTextDocument doc;
        //doc.setHtml(htmlString);
        QFont font = doc.defaultFont();
        font.setBold(true);
        font.setPointSize(10);
        doc.setDefaultFont(font);
        QSizeF s = QSizeF(printer.logicalDpiX() * (58 / 25.4), printer.logicalDpiY() * (297 / 25.4));
        //doc.setPageSize(s);
        printer.setPageSizeMM(s);
        printer.setOutputFormat(QPrinter::NativeFormat);

        doc.setHtml("店联");
        doc.print(&printer);
    }
}
// 打印预览
void MainWindow::doPrintPreview()
{
    QPrinter printer;

    // 创建打印预览对话框
    QPrintPreviewDialog preview(&printer, this);
    // 当要生成预览页面时，发射paintRequested()信号
    connect(&preview, SIGNAL(paintRequested(QPrinter*)),
                  this,SLOT(printPreview(QPrinter*)));
    preview.exec();
}
void MainWindow::printPreview(QPrinter *printer)
{
    //ui->textEdit->print(printer);
    QTextDocument doc;
    //doc.setHtml(htmlString);
//    QFont font = doc.defaultFont();
//    font.setBold(true);
//    font.setPointSize(font.pointSize() + 1);
//    doc.setDefaultFont(font);
    QSizeF s = QSizeF(printer->logicalDpiX() * (58 / 25.4), printer->logicalDpiY() * (297 / 25.4));
//    doc.setPageSize(s);
    printer->setPageSizeMM(s);
    printer->setOutputFormat(QPrinter::NativeFormat);

    doc.setHtml("店联");
    doc.print(printer);
}
// 生成PDF文件
void MainWindow::createPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"), QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer;
        // 指定输出格式为pdf
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->textEdit->print(&printer);

    }
}
// 页面设置
void MainWindow::setUpPage()
{
    QPrinter printer;
    QPageSetupDialog pageSetUpdlg(&printer, this);
    if (pageSetUpdlg.exec() == QDialog::Accepted)
    {
        printer.setOrientation(QPrinter::Landscape);
    }
    else
    {
        printer.setOrientation(QPrinter::Portrait);
    }
}



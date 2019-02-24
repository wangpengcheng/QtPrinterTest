#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QPageSetupDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void doPrint();
    void doPrintPreview();
    void printPreview(QPrinter *printer);
    void createPdf();
    void setUpPage();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

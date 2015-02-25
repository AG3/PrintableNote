#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QPixmap>
#include <QFileDialog>
#include <QDir>
#include <QUrl>
#include<QRgb>
#include<cv.h>
#include<highgui.h>
#include<imgcodecs.hpp>
#include"imgproc.hpp"
#include"core.hpp"

#include<QDebug>

using namespace cv;
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_iptfile_clicked();
    void on_button_process_clicked();

private:
    QString picurl,dicurl;
    QColor color;
    Mat iptMat,hsvMat;
    void Cut_img(Mat src_img,int m,int n,vector<int> ceil_avr);
    void removeBackground();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

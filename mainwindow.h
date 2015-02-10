#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QPixmap>
#include <QFileDialog>
#include <QDir>
#include <QUrl>

#include<QDebug>

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
    QPixmap currentPic;
    QFile optFile;
    inline QRgb getPureColor(int h, int s, int v);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_button_iptfile_clicked()
{
    picurl=QFileDialog::getOpenFileUrl().toString(QUrl::RemoveScheme);
    picurl=picurl.right(picurl.size()-3);
    currentPic.load(picurl);
    ui->label_rawpic->setPixmap(currentPic.scaled(ui->label_rawpic->size()));
}

void MainWindow::on_button_process_clicked()
{

    QImage tpic;
    QColor tcol;
    int h,s,v;
    //QColor(255,0,0).getHsl(&h,&s,&l);
    //qDebug()<<h<<s<<l;
    tpic=currentPic.toImage();
    for(int i=0;i<tpic.width();i++)
    {
        for(int j=0;j<tpic.height();j++)
        {
            tcol=tpic.pixel(i,j);
            tcol.getHsv(&h,&s,&v);
            if(i==899 && j==383)
                    qDebug()<<h<<s<<v;
            tpic.setPixel(i,j,getPureColor(h,s,v));
        }
    }
    ui->label_respic->setPixmap(QPixmap::fromImage(tpic).scaled(ui->label_respic->size()));
    tpic.save("a.png");
}

inline QRgb MainWindow::getPureColor(int h, int s, int v)
{
    if(v>126 && s<=44)
    {
        return QColor(255,255,255).rgb();//White
    }
    if((v<127 && s<=77) || v<=77)
    {
        return QColor(0,0,0).rgb();//Black
    }

    if((h>=0&&h<=16) || h>=331)
    {
        return QColor(255,0,0).rgb();//Red
    }
    if(h>=17 && h<=35)
    {
        return QColor(255,165,0).rgb();//Orange
    }
    if(h>=36 && h<=65)
    {
        return QColor(255,255,0).rgb();//Yellow
    }
    if(h>=66 && h<=165)
    {
        return QColor(0,255,0).rgb();//Green
    }
    if(h>=166 && h<=205)
    {
        return QColor(0,204,255).rgb();//Lightblue
    }
    if(h>=206 && h<=255)
    {
        return QColor(0,0,255).rgb();//Darkblue
    }
    if(h>=256 && h<=285)
    {
        return QColor(173,33,173).rgb();//Purple
    }
    if(h>=286 && h<=330)
    {
        return QColor(255,110,230).rgb();//Pink
    }
    return QColor(0,0,0).rgb();
}

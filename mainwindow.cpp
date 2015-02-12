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

int minn(int a,int b)
{
    if(a<b)return a;
    return b;
}
int maxx(int a,int b)
{
    if(a>b)return a;
    return b;
}
int sum2i[10000][10000];
int gray[10000][10000];
void MainWindow::on_button_process_clicked()
{
    //首先转换为灰度图分离背景和内容（不知道为什么背景一定比内容浅）
    QImage tpic,*npic;
    QColor tcol;
    QRgb WHITE=QColor(255,255,255).rgb();
    int h,s,v,i,j,r,g,b,picwidth,picheight,k;
    int gr;


    tpic=currentPic.toImage();
    npic=new QImage(tpic.size(),tpic.format());
    picwidth=tpic.width();
    picheight=tpic.height();
    for(i=0;i<picwidth;i++)
    {
        for(j=0;j<picheight;j++)
        {
            npic->setPixel(i,j,WHITE);//Init npic

            tcol=tpic.pixel(i,j);
            tcol.getRgb(&r,&g,&b);
            gr= (r * 11 + g * 16 + b * 5)/32;
            gray[i][j]=gr;
            for(int k=0;k<=j;k++)
            {
                sum2i[i][j]+=gray[i][k];
            }
        }
    }

    //然后遍历每个像素，当这个像素的颜色比周围（各上下左右各扩展dist像素）的平均值浅时认定为白
    int dist=40;
    double avr;
    double magicNum=0.95;
    for(i=0;i<picwidth;i++)
    {
        for(j=0;j<picheight;j++)
        {
            int ri=minn(i+dist,picwidth),bot=minn(j+dist,picheight),up=maxx(j-dist,0),lef=maxx(i-dist,0);
            for(k=lef;k<ri;k++)
            {
                avr+=(sum2i[k][bot]-sum2i[k][up])*1.0/(bot-up+1)*1.0;
            }
            avr/=(ri-lef)*1.0;
            if(gray[i][j]<avr*magicNum)
            {
                tcol=tpic.pixel(i,j);
                tcol.getHsv(&h,&s,&v);
                if(i==178 && j==484) qDebug()<<h<<s<<v;
                npic->setPixel(i,j,getPureColor(h,s,v));
                //tpic.setPixel(i,j,QColor(0,0,0).rgb());
            }
        }
    }

    ui->label_respic->setPixmap(QPixmap::fromImage(*npic).scaled(ui->label_respic->size()));
    npic->save("opt.png");
}

inline bool isBlack(int h,int s,int v)
{
    if(h>=205 && h<=260 && s>30 && v>40) return false;
    if(h==233 &&s==190 &&v==82) qDebug()<<"SSS";
    if(v<=64)return true;
    if(v<153 && s<=38)return true;
    return false;
}

inline QRgb MainWindow::getPureColor(int h, int s, int v)
{
    if(isBlack(h,s,v))
    {
        return QColor(0,0,0).rgb();//Black
    }

    if((h>=0&&h<=16) || h>=340)
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
    if(h>=256 && h<=285)
    {
        return QColor(173,33,173).rgb();//Purple
    }
    if(h>=286 && h<=339)
    {
        return QColor(255,110,230).rgb();//Pink
    }
    if(h>=206 && h<=255)
    {
        return QColor(0,0,255).rgb();//Darkblue
    }

    if(v>152 && s<=50)
    {
        return QColor(255,255,255).rgb();//White
    }
    //return QColor::fromHsv(h,s,v).rgb();
}

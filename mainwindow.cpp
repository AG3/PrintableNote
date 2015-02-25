#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace cv;

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
    iptMat=imread("./zkx.jpg");
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

inline bool isBlack(int h,int s,int v)//Finally。。。还有蓝色
{
if(v<=63.75 && s<=63.75)return true;
if(s>=63.75 && v<=s*(-0.23)+78.41)return true;
if(s<=63.75 && v<=s*(-4.37)+342.34 && v<=160)return true;
return false;
}

inline bool isWhite(int h,int s,int v)
{
    if(s<=63.75 && v>=120)return true;
    return false;
}

void MainWindow::Cut_img(Mat src_img, int m, int n, vector<int> ceil_avr)
{
    int h,s,v;
    int height = src_img.rows;
    int width  = src_img.cols;

    int ceil_height = height/m;
    int ceil_width  = width/n;

    int x,y;

    Mat roi_img;
    int avr,mx=0,mi=300;
    for(int i = 0;i<m;i++)
        for(int j = 0;j<n;j++){
            Rect rect(j*ceil_width,i*ceil_height,ceil_width,ceil_height);
            src_img(rect).copyTo(roi_img);
            avr=0;
            mx=0;
            mi=300;
            for(int k=0;k<ceil_height;k++)
            {
                for(int l=0;l<ceil_width;l++)
                {
                    if(roi_img.at<Vec3b>(i,j)[2]>mx)mx=roi_img.at<Vec3b>(i,j)[2];
                    if(roi_img.at<Vec3b>(i,j)[2]<mi)mi=roi_img.at<Vec3b>(i,j)[2];
                }
            }
            avr=(mx+mi)/2;
            for(int k=0;k<ceil_height;k++)
            {
                for(int l=0;l<ceil_width;l++)
                {
                    x=i*ceil_height+k;
                    y=j*ceil_width+l;
                    h=src_img.at<Vec3b>(x,y)[0];
                    s=src_img.at<Vec3b>(x,y)[1];
                    v=src_img.at<Vec3b>(x,y)[2];
                    if(v>avr*0.5)//Magic num here
                    {
                        iptMat.at<Vec3b>(x,y)[0]=255;
                        iptMat.at<Vec3b>(x,y)[1]=255;
                        iptMat.at<Vec3b>(x,y)[2]=255;
                    }
                    else if(isBlack(h,s,v))
                    {
                        iptMat.at<Vec3b>(x,y)[0]=0;
                        iptMat.at<Vec3b>(x,y)[1]=0;
                        iptMat.at<Vec3b>(x,y)[2]=0;
                    }
                }
            }
            ceil_avr.push_back(avr);

        }
}


void MainWindow::removeBackground()
{
    vector<int> vm(10000);
    MatIterator_<Vec3b> it, end;
    int width=hsvMat.cols,height=hsvMat.rows;
    int roiW=width/100,roiH=height/100;
    int cw,ch;
    float avr,sc;
    Cut_img(hsvMat,100,100,vm);


    //qDebug()<<s;
}

void MainWindow::on_button_process_clicked()
{
    cvtColor(iptMat,hsvMat,CV_BGR2HSV_FULL);
    removeBackground();
    //imshow(iptMat);
    int lowThreshold=40,ratio=3,kernel_size=3;
    Mat gray,edges,res;
    //cvtColor(iptMat,gray,CV_BGR2GRAY);
    //blur(gray,edges,Size(3,3));
    //Canny(edges,edges, lowThreshold, lowThreshold*ratio, kernel_size );
    //imshow("d",edges);
    //blur(edges,res,Size(3,3));

    imwrite("./opt.png",iptMat);
    qDebug()<<"finish";
}



/*inline QRgb MainWindow::getPureColor(int h, int s, int v)
{
if(isBlack(h,s,v))
{
return QColor(0,0,0).rgb();//Black
}
if(s>=255*0.2)
{
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
}
return QColor(255,255,255).rgb();
}
*/

# include <iostream>
# include <conio.h>
#include<time.h>
# include <graphics.h>
# include <math.h>
using namespace std;
char IncFlag;/*
void Bresenham(double,double,double,double);
void drawcircle(int,int,int);
void text_print();
void get_time();*/


class Analog_clock{
public:
    double x1=0,x2=1.25,y1=0,y2=180;
    double xm=1.25,ym=150,xh=1.25,yh=100;
    int sec,min;
    double hr;



void Bresenham(double x1,double x2,double y1,double y2)
{
    double S,O,End;
    double P;
    double dx = abs(x1 - x2);
    double dy = abs(y1 - y2);
    double Slope;
    double PInc,NInc,XInc,YInc;
    if (dx == 0)  //Slope Infinite
    {
    }
    else
    {
        Slope = (double)(y1 - y2) / (x1 - x2);
        if (Slope>-1 && Slope<1)
        {
            IncFlag = 'X';
            PInc = 2 * (dy - dx);
            NInc = 2 * dy;
            P = 2 * dy - dx;
            if (x1>x2)
            {
                S = x2;
                O = y2;
                End = x1;
            }
            else
            {
                S = x1;
                O = y1;
                End = x2;
            }
//            DrawLine(x,y,End,PInc,NInc,P,XInc,YInc);
        }
        else
        {
            IncFlag = 'Y';
            PInc = 2 * (dx - dy);
            NInc = 2 * dx;
            P = 2 * dx - dy;
            if (y1 > y2)
            {
                O = x2;
                S = y2;
                End = y1;
            }
            else
            {
                O = x1;
                S = y1;
                End = y2;
            }
        }
        if (IncFlag == 'X')
            putpixel(320+S,240-O,12);
        else
            putpixel(320+O,240-S,12);
        while (S <= End)
        {
            S++;
            if (P<0)
                P = P + NInc;
            else
            {
                P = P + PInc;
                if (Slope>0.0)
                    O++;
                else
                    O--;
            }
            if (IncFlag == 'X')
                putpixel(320+S,240-O,12);
            else
                putpixel(320+O,240-S,12);
        }
    }
}

void drawcircle(int x0, int y0, int radius)
{
    int x = radius;
    int y = 0;
    int p = 0;

    while (x >= y)
    {
	putpixel(x0 + x, y0 + y, 7);
	putpixel(x0 + y, y0 + x, 7);
	putpixel(x0 - y, y0 + x, 7);
	putpixel(x0 - x, y0 + y, 7);
	putpixel(x0 - x, y0 - y, 7);
	putpixel(x0 - y, y0 - x, 7);
	putpixel(x0 + y, y0 - x, 7);
	putpixel(x0 + x, y0 - y, 7);

	if (p <= 0)
	{
	    y += 1;
	    p += 2*y + 1;
	}

	if (p > 0)
	{
	    x -= 1;
	    p -= 2*x + 1;
	}
    }
}
// for  design of numbering in clock
void text_print(){
      outtextxy(320,50,"12");
      outtextxy(425,75,"1");
      outtextxy(490,150,"2");
      outtextxy(500,240,"3");
      outtextxy(490,330,"4");
      outtextxy(425,395,"5");
      outtextxy(320,420,"6");
      outtextxy(215,395,"7");
      outtextxy(150,330,"8");
      outtextxy(125,240,"9");
      outtextxy(150,150,"10");
      outtextxy(215,75,"11");

}
void get_time(){
     struct tm*data;
     double ros,rom,roh,x,y;

  time_t t1;
  t1=time(NULL);
  data=localtime(&t1);

  sec=data->tm_sec%60;       //fetching second from device
  ros=0.1047197551*sec;
  x=x2*cos(ros)+y2*sin(ros);
  y=-x2*sin(ros)+y2*cos(ros);
  x2=x;
  y2=y;

  min = data->tm_min % 60;              //fetching minute from device
  //cout<<min;
  rom=0.1047197551*(min+sec/60.0);
  x=xm*cos(rom)+ym*sin(rom);  //rotating minute pointer according to real time taken from device.
  y=-xm*sin(rom)+ym*cos(rom);
  xm=x;                         //updating the minute line drawing final coordinate
  ym=y;

  hr = data->tm_hour % 12;       //fetching hour from device
  roh=3.14*(hr+min/60.0)/6;  //rotating hour pointer  between two digit(eg. 8,9) due to minutes.
  x=xh*cos(roh)+yh*sin(roh);  //rotating hour pointer according to real time taken from device.
  y=-xh*sin(roh)+yh*cos(roh);
  xh=x;                         //updating the hour line drawing final coordinate
  yh=y;


}
void reset(){
xm=1.25,ym=150,xh=1.25,yh=100,x2=1.25,y2=180;
}
};
int main()
{   Analog_clock A;
    int gDriver=DETECT, gMode;
    int s=1,m=1;
    double x,y;
    initgraph(&gDriver,&gMode,"thapathali graphics project");       //initialize the graphics window
    A.get_time();

   // line(320,0,320,480);
   // line(0,240,640,240);
    //Bresenham(x1,x2,y1,y2);
while(1){
      A.drawcircle(320,240,210);
      A.drawcircle(320,240,211);
      A.drawcircle(320,240,212);
      A.drawcircle(320,240,230);

      A.text_print();


      x=A.x2*cos(0.1047197551)+A.y2*sin(0.1047197551); //Rotating second pointer by 6 degree
      y=-A.x2*sin(0.1047197551)+A.y2*cos(0.1047197551); //Remember angle should be in radian

      A.Bresenham(A.x1,A.x2,A.y1,A.y2);     //second pointer line draw

      A.x2=x;                               //updating new coordinate
      A.y2=y;
      A.sec+=1;

      if(A.sec==59){
            x=A.xm*cos(0.104719)-A.ym*sin(0.104719);
            y=-A.xm*sin(0.104719)+A.ym*cos(0.104719);
            A.xm=x;
            A.ym=y;
            A.min+=1;
            if(A.min%5==0){
                A.reset();             //before updating time reset is necessary to go in initial state
                A.get_time();       //updating device time in each 5 minute
            }
            if(A.min==60){
            A.min=0;
            }
            A.sec=0;
        }

      A.Bresenham(A.x1,A.xm,A.y1,A.ym);         //function call to draw minute pointer
      //In case of not using device time (just uncomment)
       /*
      if(A.min%12==0){
        x=A.xh*cos(0.104719)-A.yh*sin(0.104719);
        y=-A.xh*sin(0.104719)+A.yh*cos(0.104719);
        A.yh=y;
        if(A.min==60){
            A.min=0;

        }
        }*/

      A.Bresenham(A.x1,A.xh,A.y1,A.yh);


        delay(999);
    cleardevice();
}
    getch();
}

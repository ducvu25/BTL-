
#include<iostream>
#include"graphics.h"
#include "winbgim.h"
#include<mmsystem.h>
#include<cmath>
#include<windows.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
int setColor = 14;
int x = 200, y = 400;
float Pi = 3.141592653589793;

string ChuyenSangXau(int x) {
    string s;
    if (x < 0) {
        s.push_back('-');
        x *= -1;
    }else
        s.push_back(' ');
    while(x != 0){
        s.insert((s.begin() + 1), char(x%10 + 48));
        x/= 10;
    }
    s += "   ";
    return s;
}
char* ChuyenDoi(int x){
    string s = ChuyenSangXau(x);
    char* kq = new char[s.size() + 1];
    strcpy(kq, s.c_str());
    return kq;
}

void VeTruc(int Ox, int Oy, int d){
    setcolor(7);
    // Ox
    line(x, y, x + Ox, y);
    //for(int i=10; i< Ox; i+=10)
      //  line(x + i, y - d, x + i, y + d);
    line(x + Ox - 10, y - 5*d, x + Ox, y);
    line(x + Ox - 10, y + 5*d, x + Ox, y);
    // Oy
    line(x + Ox/2, y - Oy/2, x + Ox/2, y + Oy/2);
    //for(int i=-Oy/2 + 10; i< Oy/2; i+=10)
        //line(x + Ox/2 - d, y + i, x + Ox/2 + d, y + i);
    line(x + Ox/2 - 10, y - Oy/2 + 5*d, x + Ox/2, y - Oy/2);
    line(x + Ox/2 + 10, y - Oy/2 + 5*d, x + Ox/2, y - Oy/2);
}
void VeY(int loai){
    settextstyle(0, 0, 3);
    int Ox = 700, Oy = 700, d = 2;
    VeTruc(Ox, Oy, d);
    int xtrc = -Ox/2;
    setcolor(setColor);
    double ytrc = loai > 0 ? xtrc*cos(xtrc*Pi/90) : 10*(1 + cos(xtrc*Pi/180));
    outtextxy(x + Ox + 100 - 75, y - Oy/2, "x = ");
    outtextxy(x + Ox + 100 - 75, y - Oy/2 + 50, "y = ");
    for(int i= -Ox/2; i < Ox/2; i++){
        double yy = loai > 0 ? xtrc*cos(xtrc*Pi/90) : 10*(1 + cos(xtrc*Pi/180));
        line(x + Ox/2 + xtrc, y - ytrc, x + Ox/2 + i, y - yy);
        xtrc = i;
        ytrc = yy;
        outtextxy(x + Ox + 100, y - Oy/2, ChuyenDoi(xtrc));
        outtextxy(x + Ox + 100, y - Oy/2 + 50, ChuyenDoi(int(yy)));
        //Sleep(50);
    }
}

int main()
{
    initwindow(1200, 700, "Do hoa", 50, 30);
    setcolor(setColor);
    int x1 = 200, y1 = 200, x2 = 1000, y2 = 250, chuotX, chuotY;
    settextstyle(0, 0, 3);
    rectangle(x1, y1, x2, y2);
    outtextxy(x1 + 100, y2 - 40, "Ve do thi y = xcos(2x)");
    rectangle(x1, y1 + 100, x2, y2 + 100);
    outtextxy(x1 + 100, y2 + 100 - 40, "Ve do thi y = 10(1 + cos(x))");
    rectangle(x1, y1 + 200, x2, y2 + 200);
    outtextxy(x1 + 100, y2 + 200 - 40, "Thoat");

    while(1){
        if(ismouseclick(WM_LBUTTONDOWN)){
            cleardevice();
            rectangle(x1, y1, x2, y2);
            outtextxy(x1 + 100, y2 - 40, "Ve do thi y = xcos(2x)");
            rectangle(x1, y1 + 100, x2, y2 + 100);
            outtextxy(x1 + 100, y2 + 100 - 40, "Ve do thi y = 10(1 + cos(x))");
            rectangle(x1, y1 + 200, x2, y2 + 200);
            outtextxy(x1 + 100, y2 + 200 - 40, "Thoat");
                getmouseclick(WM_LBUTTONDOWN, chuotX, chuotY);
                if(chuotX >= x1 && chuotX <= x2){
                    if(chuotY >= y1 && chuotY <= y2){
                        cleardevice();
                        VeY(1);
                        Sleep(1000);
                    }else if(chuotY >= y1 + 100 && chuotY <= y2+ 100){
                        cleardevice();
                        VeY(-1);
                        Sleep(1000);
                    }else if(chuotY >= y1 + 200 && chuotY <= y2+ 200){
                        closegraph();
                        return 0;
                    }
                }
            }
    };
}

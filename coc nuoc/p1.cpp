#include<iostream>
#include"graphics.h"
#include "winbgim.h"
#include<mmsystem.h>
#include<cmath>
#include<windows.h>

using namespace std;
int setColor = 14;
int x = 400, y = 200;
int dayx = 400, dayy = 400;
int ra = 80, rb = 150;

void VeCocNuoc(){
    setcolor(setColor);
    // vẽ miệng cốc
    ellipse(x, y, 0, 360, rb, ra - 10);
    // vẽ mực nước bên trong
    for(int i=0; i<180; i+=10)
        ellipse(x, y + 50, i, i + 5, rb - 13, ra - 20);
    // vẽ mực nước bên ngoài
    ellipse(x, y + 50, 180, 360, rb - 13, ra - 20);
    // vẽ 2 bên thành cốc
    line(x - rb, y, x - rb + 50, y + 200);
    line(x + rb, y, x + rb - 50, y + 200);
    // vẽ đáy cốc
    for(int i=0; i<180; i+=10)
        ellipse(x, y + 200, i, i + 5, rb - 13 - 35, ra - 30);
    ellipse(x, y + 200, 180, 360, rb - 13 - 35, ra - 35);
}

int main()
{
    cout << sin(180);
    initwindow(1200, 800, "Do hoa", 50, 30);
    VeCocNuoc();
    getch();
    closegraph();
    return 0;
}

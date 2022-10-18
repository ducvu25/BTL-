#include<iostream>
#include"graphics.h"
#include "winbgim.h"
#include<mmsystem.h>
#include<cmath>
#include<windows.h>

using namespace std;
const double PI = 4.0*atan(1.0);

//ham chuyen con tro
    void gotoxy(int x,int y)
    {
        COORD coord;
        coord.X=x;
        coord.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    }

    void set_color(int X)       //b la stt cua mau chu
    {
        HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute( color , X);
    }

    struct DuongTron
    {
        int x;
        int y;
        int r;
        DuongTron(int a, int b, int R)
        {
        x = a;
        y = b;
        r = R;
        }
    };

    void VeTamGiac(int x1, int y1, int x2, int y2, int x3, int y3);

    void VeRongRoc(int x, int y, DuongTron a, DuongTron b, int xNguoi, int yNguoi, int d);

    void XuLy(DuongTron &a, int F, int m);

    void huongdan();

    int main()
    {
        // xuất ra chữ tiếng việt
        SetConsoleOutputCP(65001);

        int A = 0,  m, d = 1, x, y;
        char dk;
        char s1[100], s2[100], s3[100], s0[100];
      //  settextstyle(1, 2, 7);
        strcpy(s0, "BANG DIEU KHIEN");
        strcpy(s1, "+ Tang cong keo 200(J)");
        strcpy(s2, "- Giam cong keo 200(J)");
        strcpy(s3, "Thoat");
        set_color(4);

        gotoxy(40,1);
        cout << "MÔ PHỎNG HỆ 2 RÒNG RỌC";

        // đề bài và cách tính
        set_color(10);

        gotoxy(20,4);
        cout <<"(vui lòng nhập m từ 0 đến 25 để thí nghiệm được chính xác nhất)";

        gotoxy (1,6);
        cout << "Cho hệ 2 ròng rọc đỡ vật nặng (kg).Khi xe tăng hoặc giảm 200N thì vật đi lên hoặc đi xuống bao nhiêu mét? l=? ";

        gotoxy(1,7);
        cout <<"vì hệ 2 ròng rọc động nên lợi về lực 2x2=4(lần)";

        gotoxy(1,9);
        cout <<"Lực kéo vật lên là:";

        gotoxy(10,10);
        cout <<"Fv=mg/2";

        gotoxy(1,12);
        cout <<"quãng đường vật di chuyển ứng với 200N là:";

        gotoxy(10,13);
        cout << "l=Fk/Fv";

        gotoxy(1,14);
        cout <<"chú thích:";

        gotoxy(1,15);
        cout <<"g=10";

        gotoxy(1,16);
        cout <<"Fk: mỗi lần 200N";

        gotoxy(63,3);
        cout << "kg";

        do
        {
            gotoxy(38,3);
            cout << "Nhập khối lượng vật:";
            gotoxy(59,3);
            cin >> m;
        }
        while(m <=0 || m >25 );

            initwindow(1200, 800, "Do hoa", 50, 30);

            DuongTron a(200, 500, 25), b(250, 200, 25);

        int xXe = 400, yXe = 500;

            VeRongRoc(0, 100, a, b, xXe, yXe, 2);
            settextstyle(3,0,2);
            int xHop = 600, yHop = 200;
            rectangle(xHop-100, yHop - 175 - 10, xHop + 310, yHop + 50);
            rectangle(xHop-50, yHop - 100 - 10, xHop + 250, yHop - 100 + 25);
            rectangle(xHop-50, yHop - 50 - 10, xHop + 250, yHop - 50 + 25);
            rectangle(xHop-50, yHop - 0 - 10, xHop + 250, yHop + 25);
            outtextxy(xHop + 25, yHop - 150, s0);
            outtextxy(xHop, yHop - 100, s1);
            outtextxy(xHop, yHop - 50, s2);
            outtextxy(xHop, yHop - 0, s3);

        do
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                VeRongRoc(0, 100, a, b, xXe, yXe, 0);
                if(x>= xHop-50 && x <= xHop + 250 && y >= yHop - 100 - 10 && y <=  yHop - 100 + 25)
                {
                    A += 200;
                    xXe+=10;
                }
                else if(x>= xHop-50 && x <= xHop + 250 && y >= yHop - 50 - 10 && y <=  yHop - 50 + 25)
                {
                    A -= 200;
                    xXe-=10;
                }else if(x>= xHop-50 && x <= xHop + 250 && y >= yHop - 0 - 10 && y <=  yHop - 0 + 25){
                    cleardevice();
                    goto End;
                }

                XuLy(a, A, m);
                VeRongRoc(0, 100, a, b, xXe, yXe, 1);
            }

        if(a.y + 4*a.r >= 700)
        break;
        }
        while(a.y > b.y);
        End:
        delay(2000);
        closegraph();
        return 0;
    }

    void VeTamGiac(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        line(x1, y1, x2, y2);
        line(x1, y1, x3, y3);
        line(x3, y3, x2, y2);
    }

    void VeRongRoc(int x, int y, DuongTron a, DuongTron b, int xNguoi, int yNguoi, int d)
    {
        if(d == 2)
        {
            setcolor(14);
            circle(b.x, b.y, b.r);
            circle(b.x, b.y, b.r/2);
            setcolor(11);
            ellipse(b.x, b.y, 0, 180, b.r, b.r);
            setcolor(7);
            rectangle(x, y, b.x + 100, b.y - 50);
            VeTamGiac(b.x-b.r/2,y,b.x+b.r/2, y, b.x, b.y);
            VeTamGiac(a.x-a.r*3/2, y,a.x-a.r/2, y, a.x-a.r, b.y);
            setcolor(9);
            rectangle(xNguoi, yNguoi - 10, xNguoi+400, 650);
            circle(xNguoi + 100, 650, 50);
            circle(xNguoi + 300, 650, 50);
            circle(xNguoi + 100, 650, 25);
            circle(xNguoi + 300, 650, 25);
            line(0, 700, 1200, 700);
        }
        setcolor(0);

        if(d != 0)
        setcolor(14);
        circle(a.x, a.y, a.r);
        circle(a.x, a.y, a.r/2);

        if(d != 0)
        setcolor(11);
        line(a.x+a.r, a.y, b.x-b.r, b.y);
        line(a.x-a.r, a.y, a.x-a.r, b.y);
        line(b.x+b.r, b.y, xNguoi, yNguoi);
        ellipse(a.x, a.y, 180, 360, a.r, a.r);

        if(d != 0)
        setcolor(7);
        VeTamGiac(a.x, a.y, a.x-a.r, a.y + 2*a.r, a.x + a.r, a.y + 2*a.r);
        rectangle(a.x-3*a.r, a.y + 2*a.r, a.x + 3*a.r, a.y + 4*a.r);

        if(d != 0)
        setcolor(9);
        rectangle(xNguoi, yNguoi - 10, xNguoi+400, 650);
        circle(xNguoi + 100, 650, 50);
        circle(xNguoi + 300, 650, 50);
        circle(xNguoi + 100, 650, 25);
        circle(xNguoi + 300, 650, 25);
        line(0, 700, 1200, 700);
}




    void XuLy(DuongTron &a, int A, int m)
    {
        int s = 500 - A/m;
        a.y = s;
    }

#include<iostream>
#include"graphics.h"
#include "winbgim.h"
#include<mmsystem.h>
#include<cmath>
#include<windows.h>

using namespace std;
const double PI = 4.0*atan(1.0);

    //ham di chuyển vị trí con trỏ
    void gotoxy(int x,int y)
    {
        COORD coord;
        coord.X=x;
        coord.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    }

    //hàm đổi màu
    void setColor(int X)

    {
        HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute( color , X);
    }

    struct diem{
        char Mon[50];
        float giua;
        float cuoi;
        char diemChu[3];
        float diemSo;
    };

    diem Nhap(int x, int y){
        diem a;
        gotoxy(x, y); cout << "Nhap điểm giữa kì: "; cin >> a.giua;
        gotoxy(x, y + 1); cout << "Nhap điểm cuối kì: "; cin >> a.cuoi;
        a.diemSo = (0.4*a.giua + 0.6*a.cuoi);
        if(a.diemSo < 4)    {
            strcpy(a.diemChu, "F");
            a.diemSo = 0;
        }
        else    if(a.diemSo < 4.9){
            strcpy(a.diemChu, "D");
            a.diemSo = 1;
        }
        else    if(a.diemSo < 5.4){
            strcpy(a.diemChu, "D+");
            a.diemSo = 1.5;
        }
        else    if(a.diemSo < 6.4) {
            strcpy(a.diemChu, "C");
            a.diemSo = 2;
        }
        else    if(a.diemSo < 6.9){
            strcpy(a.diemChu, "C+");
            a.diemSo = 2.5;
        }
        else    if(a.diemSo < 7.9){
            strcpy(a.diemChu, "B");
            a.diemSo = 3;
        }
        else    if(a.diemSo < 8.4) {
            strcpy(a.diemChu, "B+");
            a.diemSo = 3.5;
        }
        else    if(a.diemSo < 8.9) {
            strcpy(a.diemChu, "A");
            a.diemSo = 3.7;
        }
        else  {
            strcpy(a.diemChu, "A+");
            a.diemSo = 4;
        }

        return a;
    }
    int main()
    {
        char name[100], lop[50];
        // xuất ra chữ tiếng việt
        SetConsoleOutputCP(65001);
        setColor(14);

        gotoxy(30, 0); cout << "NHẬP THÔNG TIN";
        gotoxy(0, 2); cout << "Nhập họ và tên: "; cin.getline(name, 99);
        gotoxy(0, 3); cout << "Nhập lớp: "; cin.getline(lop, 49);
        diem a[5];
        for(int i=0; i<5; i++){
            if(i == 0)  strcpy(a[i].Mon, "Giải tích 1: ");
            if(i == 1)  strcpy(a[i].Mon, "Đại số: ");
            if(i == 2)  strcpy(a[i].Mon, "Triết: ");
            if(i == 3)  strcpy(a[i].Mon, "Vật lý đại cương 1: ");
            if(i == 4)  strcpy(a[i].Mon, "Nhập môn lập trình: ");
            gotoxy(0, 5 + i*4); cout << "Nhập điểm môn " << a[i].Mon;
            a[i] = Nhap(0, i*4 + 6);
        }
        float GPA = (a[0].diemSo*4 + a[1].diemSo*4 + a[2].diemSo*3 + a[3].diemSo*2 + a[4].diemSo*4)/17;
        char *GPAstring = new char[4];
        sprintf(GPAstring, "%0.2f\n", GPA);
        char KQ[1000];
        strcpy(KQ, "Sinh vien ");   strcat(KQ, name); strcat(KQ, ", "); strcat(KQ, lop);    strcat(KQ, " co GPA: "); strcat(KQ, GPAstring);
        initwindow(1200, 800, "Bang danh gia", 50, 30);
        settextstyle(3,0,4);
        outtextxy(250, 0, "BANG DANH GIA KET QUA SINH VIEN");
        int x = 50, y = 50;
        settextstyle(3,0,2);
        char Name[100];
        strcpy(Name, "Ho va ten: ");    strcat(Name, name);
        outtextxy(x, y, Name);
        char Lop[100];
        strcpy(Lop, "Lop: "); strcat(Lop, lop);
        outtextxy(x, y + 30, Lop);
        outtextxy(x, y + 60, "Nam hoc: 2021 - 20222");
        rectangle(x-10, y + 200, x + 900, y + 510);
        outtextxy(x + 10, y + 225, "STT");                     //   Mon         Giua ky    Cuoi ky     Diem chu    Diem so");
        outtextxy(x + 140, y + 225, "Mon");
        outtextxy(x + 340, y + 225, "Giua ky");
        outtextxy(x + 490, y + 225, "Cuoi ky");
        outtextxy(x + 640, y + 225, "Diem chu");
        outtextxy(x + 790, y + 225, "Diem so");
        line(x+65, y + 200, x + 65, y + 510);
        line(x+290, y + 200, x + 290, y + 510);
        line(x+440, y + 200, x + 440, y + 510);
        line(x+590, y + 200, x + 590, y + 510);
        line(x+750, y + 200, x + 750, y + 510);
        line(x-10, y + 250, x + 900, y + 250);
        line(x-10, y + 225 + 80, x + 900, y + 225 + 80);
        line(x-10, y + 225 + 2*65, x + 900, y + 225 + 2*65);
        line(x-10, y + 225 + 3*60, x + 900, y + 225 + 3*60);
        line(x-10, y + 225 + 4*58, x + 900, y + 225 + 4*58);
        char STT[5][3], giuaKy[5][10], cuoiKy[5][10], diemSo[5][10];
        for(int i=0; i<5; i++){
            sprintf(STT[i], "%d\n", i+1);
            outtextxy(x + 10, y + 225 + (i+1)*50, STT[i]);
            if(i==0)    outtextxy(x + 120, y + 225 + (i+1)*50, "Giai tich 1");
            if(i==1)    outtextxy(x + 120, y + 225 + (i+1)*50, "Dai so");
            if(i==2)    outtextxy(x + 120, y + 225 + (i+1)*50, "Triet");
            if(i==3)    outtextxy(x + 120, y + 225 + (i+1)*50, "Vat ly dai cuong 1");
            if(i==4)    outtextxy(x + 120, y + 225 + (i+1)*50, "Nhap mon lap trinh");
            sprintf(giuaKy[i], "%0.2f\n", a[i].giua);
            outtextxy(x + 340, y + 225 + (i+1)*50, giuaKy[i]);
            sprintf(cuoiKy[i], "%0.2f\n", a[i].cuoi);
            outtextxy(x + 490, y + 225 + (i+1)*50, cuoiKy[i]);
            outtextxy(x + 640, y + 225 + (i+1)*50, a[i].diemChu);
            sprintf(diemSo[i], "%0.1f\n", a[i].diemSo);
            outtextxy(x + 790, y + 225 + (i+1)*50, diemSo[i]);
        }
        rectangle(200, 600, 375, 650);
        outtextxy(250, 615, "Thoat");
        rectangle(700, 600, 875, 650);
        outtextxy(750, 615, "Danh gia");

        int ChuotX, ChuotY;
        do{
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, ChuotX, ChuotY);
                if(ChuotX >= 700 && ChuotX <= 875 && ChuotY >= 600 && ChuotY <= 650){
                    outtextxy(200, 700, KQ);
                }
                if(ChuotX >= 200 && ChuotX <= 375 && ChuotY >= 600 && ChuotY <= 650)
                    break;
            }
        }while(1);
        closegraph();
        return 0;
    }

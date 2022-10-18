
#include<iostream>
#include"graphics.h"
#include "winbgim.h"
#include<mmsystem.h>
#include<cmath>
#include<windows.h>

using namespace std;

//ham chuyen con tro
    void gotoxy(int x,int y){
        COORD coord;
        coord.X=x;
        coord.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    }

    void set_color(int X) {
        HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute( color , X);
    }
    void VeTram(int x, int y, int d){
        setcolor(7);
        rectangle(x, y-150, x + 300, y);
        line(x, y - 100, x + 300, y - 100);
        settextstyle(3, 0, 2);
        char s[100];
        strcpy(s, "CHOT KIEM SOAT");
        outtextxy(x+65, y-135, s);
        if(d == 0){
            setcolor(4);
            for(int i = 0; i<=25; i++)
                rectangle(x + 250, y, x + 250 + i, y + 150);
        }
        if(d == 4){
            {
            setcolor(0);
            for(int i = 0; i<=25; i++)
                rectangle(x + 250, y, x + 250 + i, y + 150);
        }
        }
    }
    void VeDuong(int y){
        setcolor(7);
        line(0, y, 1200, y);
        line(0, y + 150, 1200, y+150);
        for(int i=0; i<=15; i++){
            rectangle(150, y+60, 250, y + 60 + i);
            rectangle(500, y+60, 600, y + 60 + i);
            rectangle(900, y+60, 1000, y + 60 + i);
        }
    }
    void VeCot(int x, int y, int time){
        int c1, c2, c3;
        if(time == 3){
            c1 = 10;
            c2 = 14;
            c3 = 4;
        }else if(time == 2){
            c1 = 14;
            c2 = 4;
            c3 = 10;
        }else{
            c1 = 4;
            c2 = 10;
            c3 = 14;
        }
        for(int i=0; i<=10; i++){
            setcolor(c3);
            circle(x+10, y - 100 , i);
            setcolor(c2);
            circle(x+10, y - 100 - 40, i);
            setcolor(c1);
            circle(x+10, y - 100 - 80, i);
        }
        setcolor(7);
        rectangle(x, y-75, x+20, y);
        rectangle(x-10, y-75, x+30, y - 200);
    }
    void Xe(int x, int y, int d){
        setcolor(d);
        line(x, y, x, y - 50);
        line(x, y, x + 50, y);
        line(x, y-50, x + 70, y-50);
        circle(x+75, y, 25);
        circle(x+75, y, 10);
        line(x + 100, y, x + 150, y);
        circle(x+175, y, 25);
        circle(x+175, y, 10);
        line(x + 200, y, x + 250, y);
        line(x + 150 + 80, y - 50, x + 250, y - 50);
        line(x + 250, y, x + 250, y - 50);
        ellipse(x + 150, y - 50, 0, 180, 80, 50);
    }
    void Menu(int x, int y){
        setcolor(14);
        char loi1[200], loi2[200], loi3[200], loi4[200], menu[200];
        strcpy(menu, "MENU");
        strcpy(loi1, " + Khong bien so");
        strcpy(loi2, " + Vi pham den giao thong");
        strcpy(loi3, " + Uong ruou bia");
        strcpy(loi4, " + Su dung dien thoai");
        outtextxy(x + 70, y + 50, menu);
        outtextxy(x + 30, y + 100, loi1);
        outtextxy(x + 30, y + 150, loi2);
        outtextxy(x + 30, y + 200, loi3);
        outtextxy(x + 30, y + 250, loi4);
        rectangle(x, y, x + 300, y + 350);
    }

    int main(){
        SetConsoleOutputCP(65001);

        initwindow(1200, 800, "Do hoa", 50, 30);
        VeDuong(600);
        VeTram(200, 600, 1);
        char loi1[200], loi2[200], loi3[200], loi4[200], menu[200], nopPhat[100], bienBan[100];
        strcpy(menu, "MENU");
        strcpy(loi1, " + Khong bien so");
        strcpy(loi2, " + Vi pham den giao thong");
        strcpy(loi3, " + Uong ruou bia");
        strcpy(loi4, " + Su dung dien thoai");
        strcpy(nopPhat, " NOP PHAT");
        strcpy(bienBan, " BIEN BAN");
        getch();
        for(int i=0; i<20; i++){
             VeDuong(600);
             if(i == 19) VeTram(200, 600, 0);
             else if(i < 10) VeCot(550, 600, 3);
             else if(i < 15) VeCot(550, 600, 2);
             else VeCot(550, 600, 0);
             Xe(900 - i*20, 700, 0);
             Xe(900 - (i+1)*20, 700, 11);
             Sleep(500);
        }
        int xChuot, yChuot;
        int x = 700, y = 10, DanhSach = 0;
        Menu(x, y);
        long TongTien = 0;
        char DS[100];
        setcolor(11);
        outtextxy(220, 0, bienBan);
        outtextxy(25, 25, "Loi vi pham");   outtextxy(350, 25, "Phat tien");
        outtextxy(200, 400, nopPhat);
        do{
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, xChuot, yChuot);
                if(xChuot >= x + 30 && xChuot <= x + 230)
                    if(yChuot >= y + 90 && yChuot <= y + 125){
                        strcpy(DS, loi1);
                        outtextxy(50, 60 + DanhSach*50, DS);    outtextxy(350, 60 + DanhSach*50, "6000000 VND");
                        DanhSach++;
                        TongTien += 6000000;
                    }else if(yChuot >= y + 90 + 50 && yChuot <= y + 125 + 50){
                        strcpy(DS, loi2);
                        outtextxy(50, 60 + DanhSach*50, DS);    outtextxy(350, 60 + DanhSach*50, "5000000 VND");
                        DanhSach++;
                        TongTien += 5000000;
                    }else if(yChuot >= y + 90 + 100 && yChuot <= y + 125 + 100){
                        strcpy(DS, loi3);
                        outtextxy(50, 60 + DanhSach*50, DS);    outtextxy(350, 60 + DanhSach*50, "2000000 VND");
                        DanhSach++;
                        TongTien += 2000000;
                    }else if(yChuot >= y + 90 + 150 && yChuot <= y + 125 + 150){
                        strcpy(DS, loi4);
                        outtextxy(50, 60 + DanhSach*50, DS);    outtextxy(350, 60 + DanhSach*50, "18000000 VND");
                        DanhSach++;
                        TongTien += 18000000;
                    }
                char a[100];
                sprintf(a, "%d\n", TongTien);
               outtextxy(150, 300, "Tong tien: ");    outtextxy(350, 300, strcat(a, " VND"));
               if(xChuot >= 200 && xChuot <= 300 && yChuot >= 390 && yChuot <= 430)
                    goto End;
            }
        }while(1);
        End:
        for(int i=0; i<30; i++){
             VeDuong(600);
             if(i %11 == 10) VeTram(200, 600, 0);
             if(i % 11 == 0)    VeTram(200, 600, 4);
             if(i%11 < 6) VeCot(550, 600, 3);
             else if(i % 11 < 9) VeCot(550, 600, 2);
             else if(i % 11 < 10)    VeCot(550, 600, 0);
             Xe(500 - i*30, 700, 0);
             Xe(500 - (i+1)*30, 700, 11);
             Sleep(500);
        }
        closegraph();
        return 0;
    }

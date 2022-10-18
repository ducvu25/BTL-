#include<iostream>
#include"graphics.h"
#include "winbgim.h"
#include<mmsystem.h>
#include<cmath>
#include <iomanip>
#include<windows.h>

using namespace std;

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
    // Xoa man hinh
    void clrscr(){
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
    }
    struct NuocUong{
        char Name[50];
        int sl;
    };
    NuocUong Nhap(int y){
        NuocUong a;
        gotoxy(0, y); cout << "Nhập tên đồ uống: "; cin.ignore(); cin .getline(a.Name, 49);
        gotoxy(0, y+1); cout << "Nhập số lượng: "; cin >> a.sl;
        return a;
    }
    void Xuat(NuocUong *a, int n){
        clrscr();
        cout << "\n\t\t\tDANH SACH NUOC\n\n";
        cout << "| " << setw(5) << left << "STT" << " |" << setw(30) << "Ten nuoc" << " |" << setw(10) << "So luong" << " |\n";
        for(int i=0; i<n; i++)
            cout << "| " << setw(5) << left << i + 1 << " |" << setw(30) << a[i].Name << " |" << setw(10) << a[i].sl << " |\n";
    }

    int main()
    {

        // xuất ra chữ tiếng việt
        SetConsoleOutputCP(65001);
        char c;
        NuocUong a[100];
        int n=0;
        do{
            cout << "Ban co phai nhan vien khong(y/n)? ";
            cin >> c;
            switch(c){
                case 'n':{
                    goto Thoat;
                    break;
                }
                case 'y':{
                    clrscr();
                    int k;
                    do{
                        cout << "\n1. Nhap them san pham";
                        cout << "\n2. Xuat danh sach nuoc";
                        cout << "\n0. Thoat";
                        cout << "\n\tChuc nang: "; cin >> k;
                        switch(k){
                            case 1:{
                                clrscr();
                                a[n] = Nhap(3*n + 1);
                                n++;
                                break;
                            }
                            case 2:{
                                Xuat(a, n);
                                break;
                            }
                            case 0:{
                                goto Thoat;
                            }
                        }
                    }while(1);
                    break;
                }
            }
        }while(1);
        Thoat:
        initwindow(1200, 800, "Cua hang", 0, 0);
        int x = 20, y = 50, chuotX, chuotY, DS = 0;
        settextstyle(3,0,2);
        outtextxy(x + 400, 5, "May ban hang");
        outtextxy(x + 175, y + 50, "Gio hang");   outtextxy(x + 800, y + 50, "Danh sach nuoc");
        rectangle(x + 650, y + 25, x + 1050, y + 600);
        rectangle(x + 100, y + 25, x + 450, y + 600);
        outtextxy(x + 700, y + 100, "STT");
        outtextxy(x + 800, y + 100, "Ten");
        outtextxy(x + 1000, y + 100, "SL");
        outtextxy(x + 1000, y + 650, "Ket thuc");
        rectangle(x + 975, y + 650, x + 1100, y + 700);
        do{
            for(int i=0; i<n; i++){
                char *STT = new char[2];
                char *SL = new char[4];
                sprintf(STT, "%d\n", i + 1);
                outtextxy(x + 700, y + (i+3)*50, STT);
                outtextxy(x + 800, y + (i+3)*50, a[i].Name);
                sprintf(SL, "%d\n", a[i].sl);
                outtextxy(x + 1000, y + (i+3)*50, SL);
            }
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, chuotX, chuotY);
                if(chuotX >= x + 700 && chuotX <= x + 1100){
                for(int i=0; i<n; i++)
                    if(chuotY >= (i + 4)*50 - 25 && chuotY <= (i + 4)*50 + 25){
                        outtextxy(x + 150, y + 100 + 50*DS, a[i].Name);
                        outtextxy(x + 300, y + 100 + 50*DS, "1");
                        DS++;
                        a[i].sl--;
                        char *ds = new char[5];
                        sprintf(ds, "%d\n", DS);
                        outtextxy(x + 350, y + 700, "So luong: ");
                        outtextxy(x + 550, y + 700, ds);
                        break;
                    }
                }
                if(chuotX >= x + 975 && chuotX <= x + 1100 && chuotY >= y + 650 && chuotY <= y + 700)
                    goto END;
            }

        }while(1);
        END:
        closegraph();
        return 0;
    }

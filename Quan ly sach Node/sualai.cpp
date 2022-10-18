#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <windows.h>
#include <fstream>
#include <iomanip>

using namespace std;
string menu[3][4] = {"MENU", "Quan ly sach", "Quan ly phieu muon", "Thoat", "QUAN LY SACH", "Hien thi thong tin sach", "Them sach", "Xoa sach", "QUAN LY PHIEU MUON", "Hien thi phieu muon", "Muon sach", "Tra sach"};
int xx = 20, yy = 5;
int mauKhung = 15;
int mauChu = 14;
int mauTieuDe = 11;

struct date{
	int ngay;
	int thang;
	int nam;
	void layThoiGian(){
		time_t hientai = time(0);
		tm *t = localtime(&hientai);
		nam = 1900 + t->tm_year;
		thang = 1 + t->tm_mon;
		ngay = t->tm_mday;
	}
};
class Admin{
	private:
		string User;
		string Pass;
	public:
		Admin *next;
		void Tao(string _User, string _Pass, Admin* _next){
			User = _User;
			Pass = _Pass;
			next = _next;
		}
		int KiemTra(string _User, string _Pass){
			if(User == _User && Pass == _Pass)
				return 1;
			return 0;
		}
		string user(){
			return User;
		}
};
class QuanLyAdmin{
	private:
		Admin *headAD;
	public:
		void KhoiTao(){
			headAD = NULL;
		}
		Admin* Add(string _User, string _Pass){
			Admin* p = new Admin;
			p->Tao(_User, _Pass, headAD);
			return p;
		}
		void Nhap(){
			ifstream input;
			input.open("./admin.txt");
			int n;
			input >> n;
			string _User, _Pass;
			while(n > 0){
				input >> _User >> _Pass;
				headAD = this->Add(_User, _Pass);
				n--;
			}
		}
		void Xuat(){
			Admin* i = headAD;
			while(i != NULL){
				cout << i->user() << endl;
				i = i->next;
			}
		}
		int KiemTra(string _User, string _Pass){
			Admin* i = headAD;
			while(i != NULL){
				if(i->KiemTra(_User, _Pass) == 1){
					return 1;	
				}
				i = i->next;
			}
			return 0;	
		}
};

void TextColor (int color);
void gotoXY (int column, int line);
void Khung(int cot, int hang, int m, int n);
int DangNhap(QuanLyAdmin quanLy);
int Menu(int k);
class Sach{
	private:
		string ma;
		string tenSach;
		string tacGia;
		string nhaXuatBan;
		int gia;
		int namPhatHanh;
		int soTrang;
		date ngayNhapKho;
		int tinhTrangSach;
	public:
		Sach* next;
		string Ma(){
			return ma;
		}
		int TinhTrangSach(int capNhat){
			if(capNhat != -1)
				tinhTrangSach = capNhat;
			return tinhTrangSach;
		}
		int KiemTra(string _ma){
			if(ma.compare(_ma) == 0)
				return 1;
			return 0;
		}
		void Nhap(){
			string s;
			char c;
			TextColor(mauTieuDe);
			gotoXY(2*xx, yy);
			cout << "Nhap thong tin sach:";
			gotoXY(2*xx, yy + 2);	cout << "Nhap ma: ";
			cin >> ma;
			getline(cin, s);
			gotoXY(2*xx, yy + 3);		cout << "Nhap ten sach: ";
			getline(cin, tenSach);
			gotoXY(2*xx, yy + 4);		cout << "Nhap ten tac gia: ";
			getline(cin, tacGia);
			gotoXY(2*xx, yy + 5);		cout << "Nhap nha xuat ban: ";
			getline(cin, nhaXuatBan);
			gotoXY(2*xx, yy + 6);		cout << "Nhap gia ban: ";
			cin >> gia;
			gotoXY(2*xx, yy + 7);		cout << "Nhap nam phat hanh: "; 
			cin >> namPhatHanh;
			gotoXY(2*xx, yy + 8);		cout << "Nhap so trang: ";
			cin >> soTrang;
			gotoXY(2*xx, yy + 9);		cout << "Nhap ngay nhap kho(dd/mm/yyyy): "; 
			cin >> ngayNhapKho.ngay >> c >> ngayNhapKho.thang >> c >> ngayNhapKho.nam ;
			gotoXY(2*xx, yy + 10);		cout << "Nhap tinh trang sach: ";
			cin >> tinhTrangSach;
		}
		int NhapFile(ifstream &input){
			string s;
			char c;
			if(!(input >> ma))
				return 0;
			getline(input, s);
			getline(input, tenSach);
			getline(input, tacGia);
			getline(input, nhaXuatBan);
			input >> gia >> namPhatHanh >> soTrang >> ngayNhapKho.ngay >> c >> ngayNhapKho.thang >> c >> ngayNhapKho.nam >> tinhTrangSach;
			return 1;
		}
		void XuatFile(ofstream &out){
			out << ma << endl;
			out << tenSach << endl;
			out << tacGia << endl;
			out << nhaXuatBan << endl;
			out << gia << endl;
			out << namPhatHanh << endl;
			out << soTrang << endl;
			out << ngayNhapKho.ngay << "/" << ngayNhapKho.thang << "/" << ngayNhapKho.nam << endl;
			out << tinhTrangSach << endl;
		}
		void Xuat(int x, int y, int color){
			TextColor(color);
			gotoXY(x, y);
			cout << left << setw(10) << ma << setw(30) << tenSach << setw(20) << tacGia << setw(20) << nhaXuatBan 
					 << setw(10) <<	gia << setw(20) << namPhatHanh << setw(15) << soTrang 
					 << setw(2) << right << ngayNhapKho.ngay << "/" << setw(2) << ngayNhapKho.thang << "/" << left << setw(10) << ngayNhapKho.nam
					 << setw(10) << tinhTrangSach << endl;
		}
};
class BanDoc{
	private:
		string ma;
		string name;
		date ngayDK;
	public:
		BanDoc* next;
		string Ma(){
			return ma;
		}
		void NhapFile(ifstream &input){
			char c;
			string enter;
			getline(input, ma);
			getline(input, name);
			input >> ngayDK.ngay >> c >> ngayDK.thang >> c >> ngayDK.nam;
			getline(input, enter);
		}	
};
class PhieuMuon{
	private:
		int soPhieuMuon = 1;
		string maBanDoc;
		string maSach;
		date ngayMuon;
		date ngayTra;
		int tinhTrangPhieuMuon = 1;
	public:
		PhieuMuon* next;
		int SPM(){
			return soPhieuMuon;
		}
		string MaSach(){
			return maSach;
		}
		void Tao(string _maSach, string _maBanDoc, int _soPhieuMuon){
			soPhieuMuon = _soPhieuMuon;
			maSach = _maSach;
			maBanDoc = _maBanDoc;
			ngayMuon.layThoiGian();
			ngayTra = ngayMuon;
			ngayTra.ngay += 7;
		}
		int NhapFile(ifstream &in){
			char c;
			string enter;
			if(!(in  >> soPhieuMuon))
				return 0;
				in >> maBanDoc
				>> maSach
				>> ngayMuon.ngay >> c >> ngayMuon.thang >> c >> ngayMuon.nam
				>> ngayTra.ngay >> c >> ngayTra.thang >> c >> ngayTra.nam;
		}
		void HienThi(int x, int y, int color){
			TextColor(color);
			gotoXY(x, y);
			cout<< left << setw(15) << soPhieuMuon << setw(15)  << maBanDoc << setw(15) << maSach
				<< setw(2) << right << ngayMuon.ngay << "/" << setw(2) << ngayMuon.thang << "/" << setw(9) << left << ngayMuon.nam
				<< setw(2) << right << ngayTra.ngay << "/" << setw(2) << ngayTra.thang << "/" << setw(9) << left << ngayTra.nam
				<< setw(10)<< tinhTrangPhieuMuon << endl;
		}
		void GhiFile(ofstream &out){
			out << soPhieuMuon << endl;
			out << maBanDoc << endl;
			out << ngayMuon.ngay << "/" << ngayMuon.thang << "/" << ngayMuon.nam << endl;
			out << ngayTra.ngay << "/" << ngayTra.thang << "/" << ngayTra.nam << endl;
			out << tinhTrangPhieuMuon << endl;
		}
		
};
class QuanLySach{
	private:
		Sach* headS;
		BanDoc* headB; 
		PhieuMuon* headP;
	public:
		void KhoiTao(){
			headS = NULL;
			headB = NULL;
			headP = NULL;
		}
		int KiemTra(string _ma, int tinhTrang){
			Sach* i = headS;
			while(i != NULL){
				if(i->KiemTra(_ma) == 0){
					i->TinhTrangSach(tinhTrang);
					return 1;
				}
				i = i->next;
			}
			return 0;
		}
		void ThemSach(){
			Sach* p = new Sach;
			p->Nhap();
			p->next = NULL;
			if(this->KiemTra(p->Ma(), -1) == 0){
				gotoXY(3*xx, yy + 10);
				cout << "Ma sach da co trong kho vui long kiem tra lai!";
				return;
			}
			Sach* i = headS;
			while(i->next != NULL)
				i = i->next;
			i->next = p;
			gotoXY(3*xx, yy + 10);
			cout << "Da them vao kho thanh cong!";
			this->XuatFileS();
		}	
		void DocFileS(){
			Sach* i;
			ifstream input;
			input.open("./sach.txt");
			while(!input.eof()){
				Sach* p = new Sach;
				if(!p->NhapFile(input))
					return;
				if(headS == NULL){
					headS = p;
					i = p;
				}
				else{
					i->next = p;
					i = i->next;
				}
			}
		}
		void XuatFileS(){
			ofstream out;
			out.open("./sach.txt");
			Sach* i = headS;
			while(i != NULL){
				i->XuatFile(out);
				i = i->next;
			}
		}
		void XuatS(){
			Sach* i = headS;
			int x = 2;
			if(i != NULL){
				TextColor(mauKhung);
				for(int ii=0; ii<=10 + 30 + 20 + 20 + 10 + 20 + 15 + 15 + 10; ii++){
					gotoXY(xx + ii, yy - 1);		cout << char(196);
					gotoXY(xx + ii, yy + 1);		cout << char(196);
					gotoXY(xx + ii, yy + 3);		cout << char(196);
				}
				TextColor(mauTieuDe);
				gotoXY(4*xx, yy);		cout << "DANH SACH\n";
				gotoXY(xx, yy + 2);
				cout << left << setw(10) << "Ma" << setw(30) << "Ten sach" << setw(20) << "Tac gia" << setw(20) << "Nha xuat ban"
							 << setw(10) <<	"Gia" << setw(20) << "Nam phat hanh" << setw(15) << "So trang" << setw(15) << "Ngay nhap" 
							 << setw(10) << "Tinh trang\n";
				while(i != NULL){
					i->Xuat(xx, yy + 2*x++, mauChu);
					TextColor(mauKhung);
					for(int ii=0; ii<=10 + 30 + 20 + 20 + 10 + 20 + 15 + 15 + 10; ii++){
						gotoXY(xx + ii, yy + 2*x - 1);		cout << char(196);
					}
					i = i->next;
				}
			}
		}
		void XoaS(string _ma){
			Sach* i = headS;
			if(i->Ma().compare(_ma) == 0){
				if(i->TinhTrangSach(-1) == 1){
					headS = headS->next;
					cout << "\nDa xoa sach khoi danh sach!";
					return;
				}else{
					cout << "\nMa co nguoi muon!";
					return;
				}		
			}
			while(i->next != NULL){
				if(i->next->KiemTra(_ma) == 1){
					if(i->TinhTrangSach(-1) == 1){
						i->next = i->next->next;
						cout << "\nDa xoa sach khoi danh sach!";
						this->XuatFileS();
					}else{
						cout << "\nKhong the xoa vi sach da duoc muon!";
					}
					return; // ket thuc 
				}
				i = i->next;
			}
			cout << "\nMa khong co trong danh sach!";
		}
		int KiemTraB(string _ma){
			BanDoc* i = headB;
			while(i != NULL){
				if(i->Ma() == _ma)
					return 1;
				i = i->next;
			}
			return 0;
		}
		int KiemTraTT(string _ma, string _maBanDoc){
			Sach* i = headS;
			while(i != NULL){
				if(i->KiemTra(_ma) == 1 && i->TinhTrangSach(-1) == 1 && KiemTraB(_maBanDoc) == 1){
					i->TinhTrangSach(0);
					return 1;
				}
				i = i->next;
			}
			return 0;
		}
		void DocFileB(){
			BanDoc* i;
			ifstream input;
			input.open("./Bandoc.txt");
			while(!input.eof()){
				BanDoc* p = new BanDoc;
				p->NhapFile(input);
				p->next = NULL;
				if(headB == NULL){
					headB = p;
					i = p;
				}
				else{
					i->next = p;
					i = i->next;
				}
			}
		//	headB = headB->next;
		}
		void DocFileP(){
			PhieuMuon* i;
			ifstream input;
			input.open("./PhieuMuon.txt");
			while(!input.eof()){
				PhieuMuon* p = new PhieuMuon;
				p->NhapFile(input);
				p->next = NULL;
				if(headP == NULL){
					headP = p;
					i = headP;
				}
				else{
					i->next = p;
					i = i->next;
				}
			}
		}
		void ThemPhieuMuon(){
			string _maSach;
			string _maBanDoc;
			gotoXY(2*xx, yy + 2); cout << "Nhap ma sach: "; cin >> _maSach;
			gotoXY(2*xx, yy + 4); cout << "Nhap ma ban doc: "; cin >> _maBanDoc;
			if(this->KiemTraTT(_maSach, _maBanDoc) == 1){
				PhieuMuon* i = headP;
				while(i->next != NULL)
					i = i->next;
				PhieuMuon* p = new PhieuMuon;
				p->Tao(_maSach, _maBanDoc, i->SPM() + 1);
				p->next = NULL;
				i->next = p;
//				i->HienThi(xx, yy + 2, 14);
//				i->next->HienThi(xx, yy, 14);
				gotoXY(2*xx, yy + 6);
				cout << "Them thanh cong";
			}
			else{
				gotoXY(2*xx, yy + 6);
				cout << "Them phieu muon that bai do ma sach khong ton tai hoac ban doc chua dang ky!";
			}
		}
		void HienThiPhieu(){
			PhieuMuon* i = headP;
			int x = 2;
			if(i != NULL){
				TextColor(mauKhung);
				for(int ii=0; ii<=15 + 15 + 15 + 15 + 15 + 10; ii++){
					gotoXY(xx + ii, yy - 1);		cout << char(196);
					gotoXY(xx + ii, yy + 1);		cout << char(196);
					gotoXY(xx + ii, yy + 3);		cout << char(196);
				}
				TextColor(mauTieuDe);
				gotoXY(3*xx, yy);		cout << "DANH SACH\n";
				gotoXY(xx, yy + 2);
				cout << left << setw(15) << "So phieu" << setw(15) << "Ma ban doc" << setw(15) << "Ma sach" << setw(15) << "Ngay muon" << setw(15) << "Ngay tra"
							 << setw(10) << "Tinh trang\n";
				while(i != NULL){
					i->HienThi(xx, yy + 2*x++, mauChu);
					TextColor(mauKhung);
					for(int ii=0; ii<=15 + 15 + 15 + 15 + 15 + 10; ii++){
						gotoXY(xx + ii, yy + 2*x - 1);		cout << char(196);
					}
					i = i->next;
				}
			}
		}
		void XoaPhieu(){
			int _ma;
			gotoXY(2*xx, yy + 2); cout << "Nhap so phieu muon: ";
			cin >> _ma;
			PhieuMuon* i= headP;
			if(i->SPM() == _ma){
				this->KiemTra(i->MaSach(), 1);
				headP = headP->next;
				gotoXY(2*xx, yy + 6);
				cout << "Xoa thanh cong";
				return;
			}
			while(i->next != NULL){
				if(i->next->SPM() == _ma){
					this->KiemTra(i->next->MaSach(), 1);
					 i->next = i->next->next;
					 gotoXY(2*xx, yy + 6);
					 cout << "Xoa thanh cong";
					 return;
				}
				i = i->next;
			}
			gotoXY(2*xx, yy + 6);
			cout << "Phieu khong ton tai";
		}
	 	
};

int main(){
	QuanLyAdmin quanLy;
	quanLy.KhoiTao();
	quanLy.Nhap();
	
	QuanLySach quanLyS;
	quanLyS.KhoiTao();
	quanLyS.DocFileS();
	quanLyS.DocFileB();
	quanLyS.DocFileP();
	
//	quanLyS.ThemPhieuMuon();
//	getch();
//	quanLyS.HienThiPhieu();
	if(DangNhap(quanLy) == 1){
	while(1){
		switch(Menu(0)){
			case 1:{
				while(1){
					switch(Menu(1)){
						case 1:{
							quanLyS.XuatS();
							break;
						}
						case 2:{
							quanLyS.ThemSach();
							break;
						}
						case 3:{
							string _ma;
							gotoXY(2*xx, yy);
							cout << "Nhap ma sach: ";	cin >> _ma;
							quanLyS.XoaS(_ma);
							break;
						}
						case 0:{
							goto Out1;
							break;
						}
					}
					getch();
					system("cls");
				}
				Out1:
				break;
			}
			case 2:{
				while(1){
					switch(Menu(2)){
						system("cls");
						case 1:{
							quanLyS.HienThiPhieu();
							break;
						}
						case 2:{
							quanLyS.ThemPhieuMuon();
							break;
						}
						case 3:{
							quanLyS.XoaPhieu();
							break;
						}
						case 0:{
							goto Out2;
							break;
						}
					}
					getch();
					system("cls");
				}
				Out2:
				break;
			}
			case 3:
			case 0:{
				gotoXY(3*xx, yy); cout << "TAM BIET!"; 
				return 0;
			}
		}
	}	
	}
}
void TextColor (int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
void gotoXY (int column, int line){
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void Khung(int cot, int hang, int m, int n){
	TextColor(14);
	for(int i=0; i<m; i+=2){
		gotoXY(cot + i, hang); cout << "*";
		gotoXY(cot + i, hang + n); cout << "*";
	}
	for(int i=0; i<=n; i++){
		gotoXY(cot, hang + i); cout << "*";
		gotoXY(cot + m, hang + i); cout << "*";
	}
	cout << endl;
}

int Menu(int k){
	int num = 3; 	// so lan dang nhap
	int x = 2; 		// toa do hang bat dau cua khung
	int y = 25;		// toa do cot bat dau cua khung
	int m = 50; 	// do rong cua khung
	int n = 10; 	// chieu cao cua khung
	int d = 1;		// bien chuc nang
	char c;
	Khung(y, x, m, n);	
	Khung(y, x, m, n - 8);
	TextColor(10);
	gotoXY(y + m/2 - menu[k][0].size()/2, x  + 1); cout << menu[k][0];
	gotoXY(y + 5, x  + 5); cout << menu[k][2];
	gotoXY(y + 5, x  + 7); cout << menu[k][3];
	TextColor(11);
	gotoXY(y + 5, x  + 3); cout << menu[k][1];
	while(1){
		if(kbhit()){
			TextColor(10);
			gotoXY(y + 5, x  + 3); cout << menu[k][1];
			gotoXY(y + 5, x  + 5); cout << menu[k][2];
			gotoXY(y + 5, x  + 7); cout << menu[k][3];
			c = getch();
			switch(c){
				case 27:{
					system("cls");
					return 0;
				}
				case 13:{
					system("cls");
					return d;
				}
				case 'w':{
					d--;
					if(d == 0)
						d = 3;
					break;
				}
				case 'z':{
					d++;
					if(d == 4)
						d = 1;
					break;
				}
			}
			TextColor(11);
			gotoXY(y + 5, x  + 1 + 2*d);	cout << menu[k][d];
		}
	}
}
int DangNhap(QuanLyAdmin quanLy){
	int num = 3; 	// so lan dang nhap
	int x = 2; 		// toa do hang bat dau cua khung
	int y = 25;		// toa do cot bat dau cua khung
	int m = 50; 	// do rong cua khung
	int n = 10; 	//
	Khung(y, x, m, n);	
	Khung(y, x, m, n - 8);
	TextColor(10);
	gotoXY(y + m/2 - 5, x  + 1); cout << "DANG NHAP";
	gotoXY(y + 5, x  + 3); cout << "User: ";
	gotoXY(y + 5, x  + 6); cout << "Password: ";
	while(num > 0){
		TextColor(7);
		string tk, mk;
		char c;			// ki tu de lay mat khau
		gotoXY(y + 5, x  + 4);	cin >> tk;
		gotoXY(y + 5 + mk.size(), x + 7);
		while(1){
			if(kbhit()){
				c = getch();
				switch(c){
					case 13:{
						goto Out;
						break;
					}
					case 8:{
						if(mk.size() > 0){
							gotoXY(y + 5 + mk.size(), x + 7);
							mk.erase(mk.size() - 1, 1);
							cout << " ";
						}
						break;
					}
					default:{
						mk.push_back(c);
						gotoXY(y + 5 + mk.size(), x + 7);
						cout << "*";
						break;
					}
				}	
			}
		}
		Out:
		if(quanLy.KiemTra(tk, mk) == 0){
			TextColor(4);
			gotoXY(y - 3, x + n + 3);
			cout << "Tai khoan hoac mat khau khong chinh xac! Vui long kiem tra lai.";	
			Sleep(1000);	// dung chuong trinh 1s
			gotoXY(y - 3, x + n + 3);
			cout << "                                                               "; //  Xoa dong thong bao
			for(int i=1; i<m; i++){
				gotoXY(y + i, x + 4); cout << " ";
				gotoXY(y + i, x + 7); cout << " ";
			}
			num--;	
		}else{
			system("cls");
			return 1;	// dang nhap thanh cong
		}	
	}
	system("cls");
	return 0;	// dang nhap that bai
}	
	
	
	
	
	

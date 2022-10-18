#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
using namespace std;

class ThietBi{
	private:
		string ID;
		string Ten;
		string Hang;
		int Gia;
		int SoLuong;
	public:
		void Nhap(){
			cout << "\n\tNhap ID: "; cin >> ID;
			cout << "\tNhap ten thiet bi: "; cin.ignore(); getline(cin, Ten);
			cout << "\tNhap ten thuong hieu: "; cin >> Hang;
			cout << "\tNhap gia: "; cin >> Gia;
			cout << "\tNhap so luong: "; cin >> SoLuong;
		}
		void NhapFile(ifstream &input){
			string s;
			input >> ID;
			getline(input, s);
			getline(input, Ten);
			input >> Hang >> Gia >> SoLuong;
		}
		void Xuat(){
			cout << "\n\tID: " << ID;
			cout << "\n\tTen thiet bi: " << Ten;
			cout << "\n\tThuong hieu: " << Hang;
			cout << "\n\tGia: " << Gia << " VND";
			cout << "\n\tSo luong: " << SoLuong;
		}
		void XuatFile(ofstream &output){
			output << setw(10) << left << ID << setw(20) << Ten << setw(15) << Hang << setw(10) << Gia << setw(10) << SoLuong;
		}
		int SL(){
			return SoLuong;
		}
		string id(){
			return ID;
		}
		void XuatKho(int n){
			if(SoLuong < n)
				cout << "\n\tTrong kho khong du so luong de xuat!";
			else{
				cout << "\n\tDa xuat " << n << " san pham!";
				SoLuong -= n;
			}
		}
		void NhapThem(int n){
			SoLuong+= n;
		}
};
class DienThoai: public ThietBi{
	private:
		string DoPhanGiai;
		int DungLuongPin;
	public:
		void Nhap(){
			ThietBi :: Nhap();
			cout << "\tNhap do phan giai: "; cin >> DoPhanGiai;
			cout << "\tNhap dung luong pin: "; cin >> DungLuongPin;
		}
		void NhapFile(ifstream &input){
			ThietBi :: NhapFile(input);
			input >> DoPhanGiai >> DungLuongPin;
		}
		void Xuat(){
			ThietBi :: Xuat();
			cout << "\n\tDo phan giai: " << DoPhanGiai;
			cout << "\n\tDung luong pin: " << DungLuongPin << " mAh\n";
		}
		void XuatFile(ofstream &output){
			ThietBi :: XuatFile(output);
			output << setw(15) << left << DoPhanGiai << setw(10) << DungLuongPin << endl;
		}
};
class PhuKien: public ThietBi{
	private:
		int LoaiHang;
	public:
	void Nhap(){
		ThietBi :: Nhap();
		cout << "\tNhap loai hang(1: real, 0: fake): "; cin >> LoaiHang;
	}
	void NhapFile(ifstream &input){
		ThietBi :: NhapFile(input);
		input >> LoaiHang;
	}
	void Xuat(){
		ThietBi :: Xuat();
		cout << "\n\tLoai: ";
		if(LoaiHang == 1)	cout << "real\n";
		else				cout << "fake\n";
	}
	void XuatFile(ofstream &output){
		ThietBi :: XuatFile(output);
		if(LoaiHang == 1)
			output << setw(10) << "real\n";
		else
			output << setw(10) << "fake\n";
	}
};
class QuanLy{
	DienThoai 	DT[100];
	PhuKien		PK[100];
	int dt, pk;
	public:
	void Menu(){ 
		system("cls");
		cout << "\n\t\tMENU\n";
		cout << "\n\t1. Khoi tao cua hang";
		cout << "\n\t2. Nhap them thiet bi";
		cout << "\n\t3. Xuat danh sach thiet bi";
		cout << "\n\t4. Ban thiet bi";
		cout << "\n\t5. Cap nhat thiet bi";
		cout << "\n\t6. Xoa thiet bi";
		cout << "\n\t7. Tim kiem thiet bi";
		cout << "\n\t8. Xuat file";
		cout << "\n\t0. Thoat";
		cout << "\n\tChuc nang: ";
	}
	void Kho(){
		ifstream input;
		input.open("D:\\C++\\BTL\\ClassQuanLyCuaHangDienThoai\\input.txt");
		input >> dt;
		for(int i=0; i<dt; i++)
			DT[i].NhapFile(input);
		input >> pk;
		for(int i=0; i<pk; i++)
			PK[i].NhapFile(input);
	}
	void NhapHang(int ChucNang){
		int sl;
		string ids;
		switch(ChucNang){
			case 1:{
				DienThoai t;
				t.Nhap();
				for(int i=0; i<dt; i++)
					if(DT[i].id().compare(t.id()) == 0){
						DT[i].NhapThem(t.SL());
						cout << "\n\tDa bo sung them thanh cong!";
						return;
					}
				DT[dt++] = t;
				cout << "\n\tDa bo sung them thanh cong!";
				break;
			}
			case 2:{
				PhuKien t;
				t.Nhap();
				for(int i=0; i<pk; i++)
					if(PK[i].id().compare(t.id()) == 0){
						PK[i].NhapThem(t.SL());
						cout << "\n\tDa bo sung them thanh cong!";
						return;
					}
				PK[pk++] = t;
				cout << "\n\tDa bo sung them thanh cong!";
				break;
			}
			default:{
				cout << "\n\tChuc nang khong hop le!";
				break;
			}
		}
	}
	void XuatHang(int ChucNang){
		switch(ChucNang){
			case 1:{
				cout << "\n\tDanh sach dien thoai:\n";
				for(int i=0; i<dt; i++)
					DT[i].Xuat();
				break;
			}
			case 2:{
				cout << "\n\tDanh sach phu kien:\n";
				for(int i=0; i<pk; i++)
					PK[i].Xuat();
				break;
			}
			default:{
				cout << "\n\tChuc nang khong hop le!";
				break;
			}
		}
	}
	void Ban(int ChucNang){
		int sl;
		string ids;
		switch(ChucNang){
			case 1:{
				cout << "\n\tNhap ID: "; cin >> ids;
				for(int i=0; i<dt; i++)
					if(DT[i].id().compare(ids) == 0){
						cout << "\n\tNhap so luong: "; cin >> sl;
						DT[i].XuatKho(sl);
						return;
					}
				cout << "\n\tSan pham khong co trong kho!";
				break;
			}
			case 2:{
				cout << "\n\tNhap ID: "; cin >> ids;
				for(int i=0; i<pk; i++)
					if(PK[i].id().compare(ids) == 0){
						cout << "\n\tNhap so luong: "; cin >> sl;
						PK[i].XuatKho(sl);
						return;
					}
				cout << "\n\tSan pham khong co trong kho!";
				break;
			}
			default:{
				cout << "\n\tChuc nang khong hop le!";
				break;
			}
		}
	}
	void CapNhat(int ChucNang){
		int sl;
		string ids;
		switch(ChucNang){
			case 1:{
				cout << "\n\tNhap ID: "; cin >> ids;
				for(int i=0; i<dt; i++)
					if(DT[i].id().compare(ids) == 0){
						DT[i].Nhap();
						return;
					}
				cout << "\n\tSan pham khong co trong kho!";
				break;
			}
			case 2:{
				cout << "\n\tNhap ID: "; cin >> ids;
				for(int i=0; i<pk; i++)
					if(PK[i].id().compare(ids) == 0){
						PK[i].Nhap();
						return;
					}
				cout << "\n\tSan pham khong co trong kho!";
				break;
			}
			default:{
				cout << "\n\tChuc nang khong hop le!";
				break;
			}
		}
	}
	void Xoa(int ChucNang){
		string ids;
		switch(ChucNang){
			case 1:{
				cout << "\n\tNhap ID: "; cin >> ids;
				for(int i=0; i<dt; i++)
					if(DT[i].id().compare(ids) == 0){
						dt--;
						for(; i<dt; i++)
							DT[i] = DT[i+1];
						cout << "\n\tDa xoa thanh cong!";
						return;
					}
				cout << "\n\tSan pham khong co trong kho!";
				break;
			}
			case 2:{
				cout << "\n\tNhap ID: "; cin >> ids;
				for(int i=0; i<pk; i++)
					if(PK[i].id().compare(ids) == 0){
						pk--;
						for(; i<pk; i++)
							PK[i] = PK[i+1];
						cout << "\n\tDa xoa thanh cong!";
						return;
					}
				cout << "\n\tSan pham khong co trong kho!";
				break;
			}
			default:{
				cout << "\n\tChuc nang khong hop le!";
				break;
			}
		}
	}
	void TimKiem(int ChucNang){
		string ids;
		switch(ChucNang){
			case 1:{
				cout << "\n\tNhap ID: "; cin >> ids;
				for(int i=0; i<dt; i++)
					if(DT[i].id().compare(ids) == 0){
						cout << "\n\tThong tin san pham: \n";
						DT[i].Xuat();
						return;
					}
				cout << "\n\tSan pham khong co trong kho!";
				break;
			}
			case 2:{
				cout << "\n\tNhap ID: "; cin >> ids;
				for(int i=0; i<pk; i++)
					if(PK[i].id().compare(ids) == 0){
						cout << "\n\tThong tin san pham: \n";
						PK[i].Xuat();
						return;
					}
				cout << "\n\tSan pham khong co trong kho!";
				break;
			}
			default:{
				cout << "\n\tChuc nang khong hop le!";
				break;
			}
		}
	}
	void XuatFile(){
		ofstream output;
		output.open("D:\\C++\\BTL\\ClassQuanLyCuaHangDienThoai\\output.txt");
		output << "\n\t\tDANH SACH DIEN THOAI\n\n";
		output << setw(10) << left << "ID" << setw(20) << "Ten" << setw(15) << "Thuong hieu" << setw(10) << "Gia" << setw(10) << "So luong" << setw(15) << "Do phan giai" << setw(10) << "Dung luong pin" << endl;
		for(int i=0; i<dt; i++)
			DT[i].XuatFile(output);
		
		output << "\n\t\tDANH SACH PHU KIEN\n\n";
		output << setw(10) << left << "ID" << setw(20) << "Ten" << setw(15) << "Thuong hieu" << setw(10) << "Gia" << setw(10) << "So luong" << setw(10) << "Loai" << endl;
		for(int i=0; i<pk; i++)
			PK[i].XuatFile(output);
	}
};
int main(){
	int ChucNang1, ChucNang2;
	QuanLy QL;
	do{
		QL.Menu();
		cin >> ChucNang1;
		if(ChucNang1 != 1 && ChucNang1 !=  8 && ChucNang1 != 0){
			cout << "\n\t1. Dien thoai";
			cout << "\n\t2. Phu kien";
			cout << "\n\tChuc nang: ";
			cin >> ChucNang2;
		}
		switch(ChucNang1){
			case 1:{
				QL.Kho();
				cout << "\n\tKhoi tao thanh cong!";
				break;
			}
			case 2:{
				QL.NhapHang(ChucNang2);
				break;
			}
			case 3:{
				QL.XuatHang(ChucNang2);
				break;
			}
			case 4:{
				QL.Ban(ChucNang2);
				break;
			}
			case 5:{
				QL.CapNhat(ChucNang2);
				break;
			}
			case 6:{
				QL.Xoa(ChucNang2);
				break;
			}
			case 7:{
				QL.TimKiem(ChucNang2);
				break;
			}
			case 8:{
				QL.XuatFile();
				break;
			}
			case 0:{
				cout << "\n\tKet thuc";
				break;
			}
			default:{
				cout << "\n\tChuc nang khong hop le!";
				break;
			}
		}
	cout << "\n\tBam phim bat khi de tiep tuc!";
	getch();
	}while(ChucNang1 != 0);
} 

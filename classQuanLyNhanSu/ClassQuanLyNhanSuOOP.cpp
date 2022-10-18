#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <iomanip> // thu vien chua cac ham dinh dang nhap xuat

using namespace std;
struct ngay{
	int d, m, y; 
};
class NhanSu{
	private:
		string 	name;
		string 	id;
		ngay 	birth;
		int 	sex;
		string 	address;
		ngay	dateOfWork;
		float 	wage;
	public:
		void Nhap(){
			char c;
			// Moi chay thi nhap so luong 5\n nguyen an
			cout << "\n\tNhap ho va ten: "; cin.ignore(); 	getline(cin, name); // doc khi den khi het dong (\n)
			cout << "\tNhap id: ";							cin >> id;
			cout << "\tNhap ngay sinh(d/m/y): ";			cin >> birth.d >> c >> birth.m >> c >> birth.y;
			cout << "\tNhap gioi tinh(1: Nam, 0: Nu): "; 	cin >> sex;
			cout << "\tNhap dia chi: "; 	cin.ignore(); 	getline(cin, address);
			cout << "\tNhap ngay vao cong ty(d/m/y): ";		cin >> dateOfWork.d >> c >> dateOfWork.m >> c >> dateOfWork.y;
			cout << "\tNhap luong: "; 						cin >> wage;
		}
		void NhapFile(ifstream &input){
			string s; // xau tam
			char c;
			getline(input, s);	// doc dau xuong dong
			getline(input, name);
			input >> id;
			input >> birth.d >> c >> birth.m >> c >> birth.y;
			input >> sex;
			getline(input, s);	// doc dau xuong dong
			getline(input, address);
			input >> dateOfWork.d >> c >> dateOfWork.m >> c >> dateOfWork.y;
			input >> wage;	
		}
		void Xuat(){
			cout << "\tHo va ten: " << name << endl;
			cout << "\tID: "<< id << endl;
			cout << "\tNgay sinh: " << setw(2) << birth.d << "/" << setw(2) << birth.m << "/" << setw(4) << birth.y << endl;
			if(sex == 1)	cout << "\tGioi tinh: Nam\n";
			else			cout << "\tGioi tinh: Nu\n";
			cout << "\tDia chi: " << address << endl;
			cout << "\tNgay vao cong ty: " << setw(2) << dateOfWork.d << "/" << setw(2) << dateOfWork.m << "/" << setw(4) << dateOfWork.y << endl;	
		}
		void XuatFile(ofstream &output){
			output << setw(20) << left << name << setw(10) << id << setw(2) << right << birth.d << "/" << setw(2) << birth.m << "/" << setw(10) << left << birth.y;
			if(sex == 1) output << setw(14) << left << "Nam";
			else output << setw(14) << left << "Nu";
			output << setw(20) << left << address << setw(2) << right << dateOfWork.d << "/" << setw(2) << dateOfWork.m << "/" << setw(10) << left << dateOfWork.y;		
		}
		int Sex(){
			return sex;
		}	
		string ID(){
			return id;
		}	
};
class NhanVienVP : public	NhanSu{
	private:	
		string room;
	public:
		void Nhap(){
			NhanSu :: Nhap();
			cout << "\tNhap ma phong: "; cin >> room;	
		}
		void Xuat(){
			cout << "\tMa phong: " << room << endl;
			NhanSu :: Xuat();
			cout << endl;
		}
		void XuatFile(ofstream &output){
			NhanSu :: XuatFile(output);
			output << setw(10) << left << room << endl;
		}
		void NhapFile(ifstream &input){
			NhanSu :: NhapFile(input);
			input >> room;
		}
};
class CongNhanSX : public NhanSu{
	private:
		int quota; // dinh muc
		string dayOff; // ngay nghi
	public:
		void DangKiNghi(){
			if(NhanSu :: Sex() == 1)	dayOff = "Chu Nhat";
			else	{
				cout << "\tNhap ngay ban muon nghi: ";
				cin.ignore();
				getline(cin, dayOff);
			}
		}
		string NgayNghi(){
			return dayOff;
		}
		void Nhap(){
			NhanSu :: Nhap();
			cout << "\tNhap dinh muc san pham: "; cin >> quota;
			CongNhanSX :: DangKiNghi();
		}
		void NhapFile(ifstream &input){
			NhanSu :: NhapFile(input);
			input >> quota;
			if(NhanSu :: Sex() == 1)	dayOff = "Chu Nhat";
			else{
				string s;
				getline(input, s);
				getline(input, dayOff);
			}
		}
		void Xuat(){
			NhanSu :: Xuat();
			cout << "\tDinh muc: " << quota << endl;
			cout << "\tNgay nghi: " << dayOff << endl << endl;
		}
		void XuatFile(ofstream &output){
			NhanSu :: XuatFile(output);
			output << setw(10) << left << quota << setw(10) << dayOff << endl;
		}
};
class CongNhanDiChuyen: public NhanSu{
	private:
		ngay dateOutWork;
	public:
		void Nhap(){
			char c;
			NhanSu :: Nhap();
			cout << "\tNhap ngay roi di: ";
			cin >> dateOutWork.d >> c >> dateOutWork.m >> c >> dateOutWork.y;
		}
		void NhapFile(ifstream &input){
			char c;
			NhanSu :: NhapFile(input);
			input >> dateOutWork.d >> c >> dateOutWork.m >> c >> dateOutWork.y;
		}
		void Xuat(){
			NhanSu :: Xuat();
			cout << "\tNgay roi cong ty: " <<	setw(2) << dateOutWork.d << "/" << setw(2) << dateOutWork.m << "/" << setw(4) << dateOutWork.y << endl << endl;	
		}
		void XuatFile(ofstream &output){
			NhanSu :: XuatFile(output);
			output << setw(2) << dateOutWork.d << "/" << setw(2) << dateOutWork.m << "/" << setw(4) << dateOutWork.y << endl;
		}
};

class QuanLy{
	private:
		NhanVienVP NVVP[100];
		CongNhanSX CNSX[100];
		CongNhanDiChuyen CNDC[100];
		int VP, SX, DC;
	public:
		int TongNV(){
			return VP + SX;
		}
		int SoNVDC(){
			return DC;
		}
		void Nhap(){
			int n;
			cout << "Nhap so luong nhan vien van phong: "; cin >> n;
			for(int i=0; i<n; i++)
			// VP = 1
				NVVP[VP++].Nhap();
			cout << "Nhap so luong cong nhan san xuat: "; cin >> n;
			for(int i=0; i<n; i++)
				CNSX[SX++].Nhap();
			cout << "Nhap so luong cong nhan di chuyen: "; cin >> n;
			for(int i=0; i<n; i++)
				CNDC[DC++].Nhap();		
		}
		void NhapFile(){
			ifstream input;
			input.open("D:\\C++\\classQuanLyNhanSu\\input.txt");
			if(input == NULL){
				cout << "\n\tFile khong ton tai! Vui long kiem tra lai.";
				return;
			}
			input >> VP;
			for(int i=0; i<VP; i++)
				NVVP[i].NhapFile(input);
			input >> SX;
			for(int i=0; i<SX; i++)
				CNSX[i].NhapFile(input);
			input >> DC;
			for(int i=0; i<DC; i++)
				CNDC[i].NhapFile(input);
		}
		void Xuat(){
			cout << "\n\t\t\tThong tin nhan vien van phong:\n";
			for(int i=0; i<VP; i++)
				NVVP[i].Xuat();
			cout << "\n\t\t\tThong tin cong nhan san xuat:\n";
			for(int i=0; i<SX; i++)
				CNSX[i].Xuat();
			if(DC == 0)	return;
			cout << "\n\t\tThong tin nhan vien roi di:\n";
			for(int i=0; i<DC; i++)
				CNDC[i].Xuat();
		}
		void XuatFile(){
			ofstream output;
			output.open("D:\\C++\\classQuanLyNhanSu\\output.txt");
			output << "\n\t\t\tDANH SACH NHAN VIEN VAN PHONG\n";
			output << setw(20) << left << "Ho va Ten" << setw(10) << "Ma NV" << setw(16) << "Ngay sinh" << setw(14) << "Gioi tinh" << setw(20) << "Dia chi" << setw(16) << "Ngay di lam"  << "Phong\n";
			for(int i=0; i<VP; i++)
				NVVP[i].XuatFile(output);
			
			output << "\n\n\t\t\tDANH SACH CONG NHAN SAN XUAT\n";
			output << setw(20) << left << "Ho va Ten" << setw(10) << "Ma NV" << setw(16) << "Ngay sinh" << setw(14) << "Gioi tinh" << setw(20) << "Dia chi" << setw(16) << "Ngay di lam" << setw(10) << "He so" << "Ngay nghi\n";
			for(int i=0; i<SX; i++)
				CNSX[i].XuatFile(output);
			
			if(DC == 0){
				output << "\n\n\t\tKHONG CO CONG NHAN CHUYEN DI";
				return;
			}
			output << "\n\n\t\t\tDANH SACH CONG NHAN CHUYEN DI\n";
			output << setw(20) << left << "Ho va Ten" << setw(10) << "Ma NV" << setw(16) << "Ngay sinh" << setw(14) << "Gioi tinh" << setw(20) << "Dia chi" << setw(16) << "Ngay di lam"  << "Ngay roi\n";
			for(int i=0; i<DC; i++)
				CNDC[i].XuatFile(output);
		}
		void Menu(){
			system("cls"); // xoa man hinh
			cout << "\n\t\tMENU";
			cout << "\n\t1. Nhap nhan vien.";
			cout << "\n\t2. Cap nhatnhan vien van phong.";
			cout << "\n\t3. Tim cong nhan san xuat.";
			cout << "\n\t4. Xoa cong nhan chuyen di.";
			cout << "\n\t5. Hien thi thong tin nhan vien.";
			cout << "\n\t6. Thong ke so nhan vien nu dang ki nghi theo thu trong tuan.";
			cout << "\n\t7. Thong ke nhan vien chuyen di.";
			cout << "\n\t8. Xuat file";
			cout << "\n\t0. Thoat";
			cout << "\n\t\tChuc nang: ";
		}
		void ThongKe(){
			int d = 0;
			for(int i=0; i<SX; i++)
				if(CNSX[i].NgayNghi() == "Thu Hai" && CNSX[i].Sex() == 0){
					if(d == 0){
						d = 1; // co nhan vien
						cout << "\n\tDanh sach cong nhan nu nghi Thu Hai:\n";
					}
					CNSX[i].Xuat();
				}
			d = 0;
			for(int i=0; i<SX; i++)
				if(CNSX[i].NgayNghi() == "Thu Ba" && CNSX[i].Sex() == 0){
					if(d == 0){
						d = 1;
						cout << "\n\tDanh sach cong nhan nu nghi Thu Ba:\n";
					}
					CNSX[i].Xuat();
				}
			for(int i=0; i<SX; i++)
				if(CNSX[i].NgayNghi() == "Thu Tu" && CNSX[i].Sex() == 0){
					if(d == 0){
						d = 1;
						cout << "\n\tDanh sach cong nhan nu nghi Thu Tu:\n";
					}
					CNSX[i].Xuat();
				}
			for(int i=0; i<SX; i++)
				if(CNSX[i].NgayNghi() == "Thu Nam" && CNSX[i].Sex() == 0){
					if(d == 0){
						d = 1;
						cout << "\n\tDanh sach cong nhan nu nghi Thu Nam:\n";
					}
					CNSX[i].Xuat();
				}
			for(int i=0; i<SX; i++)
				if(CNSX[i].NgayNghi() == "Thu Sau" && CNSX[i].Sex() == 0){
					if(d == 0){
						d = 1;
						cout << "\n\tDanh sach cong nhan nu nghi Thu Sau:\n";
					}
					CNSX[i].Xuat();
				}
			for(int i=0; i<SX; i++)
				if(CNSX[i].NgayNghi() == "Thu Bay" && CNSX[i].Sex() == 0){
					if(d == 0){
						d = 1;
						cout << "\n\tDanh sach cong nhan nu nghi Thu Bay:\n";
					}
					CNSX[i].Xuat();
				}
			for(int i=0; i<SX; i++)
				if(CNSX[i].NgayNghi() == "Chu Nhat" && CNSX[i].Sex() == 0){
					if(d == 0){
						d = 1;
						cout << "\n\tDanh sach cong nhan nu nghi Chu Nhat:\n";
					}
					CNSX[i].Xuat();
				}
		}
		void NhanVienChuyenDi(){
			cout << "\n\tCo: " << DC << " chuyen di gom:\n";
			for(int i=0; i<DC; i++)
				CNDC[i].Xuat();
		}
		void UpdateNVVP(string ids){
			for(int i=0; i<VP; i++)
				if(NVVP[i].ID().compare(ids) == 0){
					cout << "\n\tNhap lai thong tin:\n";
					NVVP[i].Nhap();
					return;
				}
			cout << "\n\tKhong co nhan vien van phong ban muon tim!";
		}
		void SearchCNSX(string ids){
			for(int i=0; i<VP; i++)
				if(CNSX[i].ID().compare(ids) == 0){
					cout << "\n\tThong tin cong nhan san xuat ban can tim:\n";
					CNSX[i].Xuat();
					return;
				}
			cout << "\n\tKhong cong nhan san xuat ban muon tim!";
		}
		void DeleteCNDC(string ids){
			for(int i=0; i<VP; i++)
				if(CNDC[i].ID().compare(ids) == 0){
					DC--;
					for(int j=i; j<DC; j++)
						CNDC[j] = CNDC[j+1]; // day sang trai tu vi tri i
					return;
				}
			cout << "\n\tKhong co cong nhan chuyen di ban muon tim!";
		}
};
int main(){
	QuanLy a;
	a.NhapFile(); 
	int chucNang;
	do{
		a.Menu();
		cin >> chucNang;
		switch(chucNang){
			case 1:{
				a.Nhap();
				cout << "\n\tDa nhap xong!";
				break;
			}
			case 2:{
				string ids;
				cout << "Nhap id: "; cin >> ids;
				a.UpdateNVVP(ids);
				break;
			}
			case 3:{
				string ids;
				cout << "Nhap id: "; cin >> ids;
				a.SearchCNSX(ids);
				break;
			}
			case 4:{
				string ids;
				cout << "Nhap id: "; cin >> ids;
				a.DeleteCNDC(ids);
				break;
			}
			case 5:{
				cout << "\nCo " << a.TongNV() << " nhan vien.";
				cout << "\nCo " << a.SoNVDC() << " nhan vien chuyen di";
				a.Xuat();
				break;
			}
			case 6:{
				cout << "\n\tThong ke theo thu trong tuan";
				a.ThongKe();
				break;
			}
			case 7:{
				a.NhanVienChuyenDi();
				break;
			}
			case 8:{
				a.XuatFile();
				break;
			}
			case 0:{
				cout << "\n\tKet thuc.";
				return 0;
			}
			default:{
				cout << "\n\tThao tac khong hop le! Vui long kiem tra lai.";
				break;
			}
		}
		cout << "\n\tBam phim bat ki de tiep tuc!";
		getch(); // su kien ban phim 
	}while(1);
}

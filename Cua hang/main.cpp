#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>

using namespace std;

//struct Phong{
//	string 	maPhong;
//	int 	tinhTrang;
//	Time 	ngayDat;
//	string Ten;
//	string SDT;
//	string Cmnd;
//	string diaChi;
//	string 	Loai;
//};
void NhapPhong(string a[][8], int &n){
	string x[8];
	cout << "\nNhap thong tin phong:\n";
	cout << "Nhap ma phong: ";	cin >> x[0];
	for(int i=0; i<n; i++)
		if(a[i][0] == x[0]){
			cout << "\n\tMa phong da ton tai.";
			return;
		}
	cout << "Nhap loai phong: ";	cin.ignore(); 	getline(cin, x[7]);
	x[1] = "0";
	x[2] = "";
	x[3] = "";
	x[4] = "";
	x[5] = "";
	x[6] = "";
	for(int i=0; i<8; i++)
		a[n][i] = x[i];
	n++;
}
void NhapFile(string a[][8], int &n){
	ifstream in;
	in.open("./input.txt");
	in >> n;
	string s;
	for(int i=0; i<n; i++){
		in >> a[i][0] >> a[i][1];
		if(a[i][1] == "1"){
			in 	>> a[i][2];
			getline(in, s);
			getline(in, a[i][3]);
			in >> a[i][4] >> a[i][5];
			getline(in, s);
			getline(in, a[i][6]);
		}else{
			a[i][2] = "";
			a[i][3] = "";
			a[i][4] = "";
			a[i][5] = "";
			a[i][6] = "";
			getline(in, s);
		}
		getline(in, a[i][7]);
	}
}
void XuatPhong(string x[8]){
	if(x[1] == "1")
		cout << left << setw(10) << x[0] << setw(15) << "Het phong" 
		<< setw(15) << x[7] << endl;
	else
		cout << left << setw(10) << x[0] << setw(15) << "Trong" 
		<< setw(15) << x[7] << endl;
}
void XuatDSP(string a[][8], int n){
	cout << "\n\n\tDANH SACH PHONG";
	cout << "\n" << setw(10) << left << "Ma" << setw(15) 
	<< "Tinh trang" << setw(15) << "Loai" << endl;
	for(int i=0; i<n; i++)
		XuatPhong(a[i]);
}
void XuatPhongTrong(string a[][8], int n){
	cout << "\n\n\tDANH SACH PHONG TRONG";
	cout << "\n" << setw(10) << "Ma" << setw(15) << "Tinh trang" 
	<< setw(15) << "Loai" << endl;
	for(int i=0; i<n; i++)
		if(a[i][1] == "0")
			XuatPhong(a[i]);
}
void XuatChiTiet(string x[8]){
	cout << "\nThong tin phong: " << x[0] << endl;
	cout << "Tinh trang: ";
	if(x[1] == "1"){
		cout << "Co nguoi thue" << endl;
		cout << "Ngay dat: " << x[2] << endl;
		cout << "Thong tin khach: " << endl;
		cout << "\tTen: " << x[3] << endl;
		cout << "\tSDT: " << x[4] << endl;
		cout << "\tCMND: " << x[5] << endl;
		cout << "\tDia chi:" << x[6] << endl;
		cout << "Loai phong:" << x[7] << endl;
	}else
		cout << "Trong\n";
}
void DatPhong(string a[][8], int n, string maPhong){
	string s;
	for(int i=0; i<n; i++)
		if(a[i][0] == maPhong && a[i][1] == "0"){
			cout << "\nNhap ngay muon dat: ";
			cin >> a[i][2];
			getline(cin, s);
			cout << "Nhap ten chu: ";	getline(cin, a[i][3]);
			cout << "Nhap sdt: ";	cin >> a[i][4] ;
			cout << "Nhap so cccd/cmnd: ";	cin >> a[i][5];
			getline(cin, s);
			cout << "Nhap que quan: ";	getline(cin, a[i][6]);
			cout << "\n\tDat thanh cong!";
			a[i][1] = "1";
			return;
		}
	cout << "\n\tLoi dat phong! Vui long kiem tra lai ma phong hoac tinh trang phong!";
}
void TraPhong(string a[][8], int n, string maPhong){
	char c;
	for(int i=0; i<n; i++)
		if(a[i][1] == maPhong && a[i][1] == "1"){
			cout << "\nNhap ngay muon tra: ";
			string x;
			cin >> x;
			a[i][1] = "0";
			a[i][2] = "";
			a[i][3] = "";
			a[i][4] = "";
			a[i][5] = "";
			a[i][6] = "";
			cout << "\nTra thanh cong!";
			return;
		}
	cout << "\n\tLoi dat phong! Vui long kiem tra lai ma phong hoac tinh trang phong!";
}
void ThongTinPhong(string a[][8], int n, string maPhong){
	for(int i=0; i<n; i++)
		if(a[i][0] == maPhong){
			XuatChiTiet(a[i]);
			return;
		}
	cout << "\n\tMa Phong khong dung!";
}
void CapNhatPhong(string a[][8], int n, string maPhong){
	for(int i=0; i<n; i++){
		if(a[i][0] == maPhong){
			cout << "\nCap nhat phong:\n";
			cout << "Nhap loai phong moi: "; cin.ignore(); getline(cin, a[i][7]);
			cout << "\n\tCap nhat thanh cong!";
			return;
		}
	}
	cout << "\n\tMa phong khong hop le!";
}
void XuatFile(string a[][8], int n){
	ofstream coutfile;
	coutfile.open("./output.txt");
	for(int i=0; i<n; i++){
		coutfile << "\nThong tin phong: " << a[i][0] << endl;
		coutfile << "Tinh trang: ";
		if(a[i][1] == "1"){
			coutfile << "Co nguoi thue" << endl;
			coutfile << "Ngay dat: " << a[i][2] << endl;
			coutfile << "Thong tin khach: " << endl;
			coutfile << "\tTen: " << a[i][3] << endl;
			coutfile << "\tSDT: " << a[i][4] << endl;
			coutfile << "\tCMND: " << a[i][5] << endl;
			coutfile << "\tDia chi:" << a[i][6] << endl;
		}else
			coutfile << "Trong\n";
		coutfile << "Loai phong:" << a[i][7] << endl;
	}
}
void Menu(){
	cout << "\n\t\t\tMENU\n";
	cout << "1. Nhap them phong\n";
	cout << "2. Hien thi danh sach phong\n";
	cout << "3. Hien thi danh sach phong trong\n";
	cout << "4. Dat phong\n";
	cout << "5. Tra phong\n";
	cout << "6. Thong tin phong\n";
	cout << "7. Cap nhat phong\n";
	cout << "8. Xuat file\n";
	cout << "0. Thoat\n";
	cout << "\tChuc nang: ";
}
int main(){
	int n = 0;
	string a[100][8];
	NhapFile(a, n);
	int chucNang;
	do{
		Menu();
		cin >> chucNang;
		switch(chucNang){
			case 1:{
				NhapPhong(a, n);
				break;
			}
			case 2:{
				XuatDSP(a, n);
				break;
			}
			case 3:{
				XuatPhongTrong(a, n);
				break;
			}
			case 4:{
				string maPhong;
				cout << "Nhap ma phong muon dat: "; cin >> maPhong;
				DatPhong(a, n, maPhong);
				break;
			}
			case 5:{
				string maPhong;
				cout << "Nhap ma phong muon tra: "; cin >> maPhong;
				TraPhong(a, n, maPhong);
				break;
			}
			case 6:{
				string maPhong;
				cout << "Nhap ma phong: "; cin >> maPhong;
				ThongTinPhong(a, n, maPhong);
				break;
			}
			case 7:{
				string maPhong;
				cout << "Nhap ma phong: "; cin >> maPhong;
				CapNhatPhong(a, n, maPhong);
				break;
			}
			case 8:{
				XuatFile(a, n);
				break;
			}
			case 0:{
				cout << "\n\t\tKET THUC";
				break;
			}
			
		}
	}while(chucNang != 0);
	return 0;
}

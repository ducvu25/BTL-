#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//struct ThongTin{
//	string ma;
//	string ten;
//	int	tuoi;
//	string diaChi;
//	string tinhTrang;
//	string ngayMac;
//	string Phong;
//};
string* Nhap(){
	string* x = new string[7];
	cout << "\nNhap thong tin:\n";
	cout << "Nhap ma: "; 	cin >> x[0];
	cout << "Nhap ten: ";;	cin.ignore(); getline(cin, x[1]);
	cout << "Nhap tuoi: "; 	cin >> x[2];
	cout << "Nhap dia chi: "; cin.ignore();	getline(cin, x[3]);
	cout << "Nhap tinh trang: "; cin >> x[4];
	cout << "Nhap ngay mac: "; cin >> x[5];
	cout << "Nhap phong cach ly: "; cin >> x[6];
	return x;
}
void Xuat(string* x){
	cout << left << setw(10) << x[0] << setw(30) << x[1] 
	<< setw(8) << x[2] << setw(25) << x[3] 
	<< setw(15) << x[4] << setw(15) << x[5] 
	<< setw(10) << x[6] << endl;
}
void XuatDS(string a[][7], int n){
	cout << "\n\t\tDANH SACH\n";
	cout << left << setw(10) << "Ma" << setw(30) << "Ho ten" 
	<< setw(8) << "tuoi" << setw(25) << "Dia chi" 
	<< setw(15) << "Tinh trang" << setw(15) << "Ngay mac" 
	<< setw(10) << "Phong" << endl;
	for(int i=0; i<n; i++)
		Xuat(a[i]);
}
void ThemBN(string a[][7], int &n, string* x){
	for(int i=0; i<n; i++)
		if(a[i][0] == x[0]){
			cout << "\nMa benh nhan da ton tai!";
			return;
		}
	for(int i=0; i<7; i++)
		a[n][i] = x[i];
	n++;
	cout << "\nThem thanh cong!";
}
void XuatBNP(string a[][7], int n, string Phong){
	cout << "\n\t\tDANH SACH\n";
	cout << left << setw(10) << "Ma" << setw(30) 
	<< "Ho ten" << setw(8) << "tuoi" << setw(25) << "Dia chi" 
	<< setw(15) << "Tinh trang" << setw(15) << "Ngay mac" 
	<< setw(10) << "Phong" << endl;
	for(int i=0; i<n; i++)
		if(a[i][6] == Phong)
			Xuat(a[i]);
}
void Update(string a[][7], int n, string ma){
	for(int i=0; i<n; i++)
		if(a[i][0] == ma){
			cout << "\nCap nhat tinh trang: "; cin >> a[i][4];
			cout << "Cap nhat phong cach ly: "; cin >> a[i][6];
			cout << "Cap nhat thanh cong!";
			return;
		}
	cout << "\nMa khong co trong danh sach";
}
void Delete(string a[][7], int &n, string ma){
	for(int i=0; i<n; i++)
		if(a[i][0] == ma){
			for(int j=i; j<n-1; j++)
				for(int k=0; k<7; k++)
					a[j][k] = a[j+1][k];
			n--;
			cout << "\nXoa thanh cong!";
			return;
		}
	cout << "\nMa khong co trong danh sach";
}
void Sort(string a[][7], int n){
	for(int i=0; i<n-1; i++)
		for(int j=i+1; j<n; j++)
			if(a[i][4]< a[j][4]){
				string x[7];
				for(int k=0; k<7; k++)
					x[k] = a[i][k];
				for(int k=0; k<7; k++)
					a[i][k] = a[j][k];
				for(int k=0; k<7; k++)
					a[j][k] = x[k];
			}
	cout << "\nSap xep thanh cong!";
}
void DocFile(string a[][7], int &n){
	ifstream fb;
	fb.open("./input.txt");
	fb >> n;
	string tam;
	for(int i=0; i<n; i++){
		fb >> a[i][0];	
		getline(fb, tam);	getline(fb, a[i][1]);
		fb >> a[i][2];
		getline(fb, tam);	getline(fb, a[i][3]);
		fb >> a[i][4];
		fb >> a[i][5];
		fb >> a[i][6];
	}
}
void XuatFile(string a[][7], int n){
	ofstream out;
	out.open("./output.txt");
	out << "\n\t\tDANH SACH\n";
	out << left << setw(10) << "Ma" << setw(30) << "Ho ten" 
	<< setw(8) << "tuoi" << setw(25) << "Dia chi" 
	<< setw(15) << "Tinh trang" << setw(15) << "Ngay mac" 
	<< setw(10) << "Phong" << endl;
	for(int i=0; i<n; i++)
		out <<left << setw(10) << a[i][0] << setw(30) 
		<< a[i][1] << setw(8) << a[i][2] << setw(25) 
		<< a[i][3] << setw(15) << a[i][4] << setw(15) 
		<< a[i][5] << setw(10) << a[i][6] << endl;
}
int Menu(){
	int k;
	cout << "\n\n\t\tMENU\n";
	cout << "1. Nhap them benh nhan\n";
	cout << "2. Xuat danh sach benh nhan\n";
	cout << "3. Xuat danh sach benh nhan theo phong\n";
	cout << "4. Cap nhat thong tin cua benh nhan\n";
	cout << "5. Xoa benh nhan\n";
	cout << "6. Sap xep benh nhan theo tinh trang\n";
	cout << "7. Xuat file\n";
	cout << "0. Thoat\n";
	cout << "Chuc nang: ";	cin >> k;
	return k;
}
int main(){
	string a[100][7];
	int n;
	DocFile(a, n);
	while(1){
		switch(Menu()){
			case 0:{
				return 0;
			}
			case 1:{
				ThemBN(a, n, Nhap());
				break;
			}
			case 2:{
				XuatDS(a, n);
				break;
			}
			case 3:{
				string Phong;
				cout << "\nNhap ma phong: "; cin >> Phong;
				XuatBNP(a, n, Phong);
				break;
			}
			case 4:{
				string ma;
				cout << "\nNhap ma benh nhan: "; cin >> ma;
				Update(a, n, ma);
				break;
			}
			case 5:{
				string ma;
				cout << "\nNhap ma benh nhan: "; cin >> ma;
				Delete(a, n, ma);
				break;
			}
			case 6:{
				Sort(a, n);
				break;
			}
			case 7:{
				XuatFile(a, n);
				break;
			}
		}
	}
}

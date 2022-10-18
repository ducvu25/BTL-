#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

struct suKien{
	int ma;
	string chuThuat;
	string ma1, ma2;
	int maTrix[8][8];
	vector <int> mang;
	int giaTri;
};
int chuyenDoiSangSo(string s){
	int gtri = 0;
	int coSo = 1;
	for(int i=s.size() - 1; i>=0; i--){
		gtri += coSo*(s[i] - 48);
		coSo *= 10;
	}
	return gtri;
}
vector <suKien> DocDuLieu(){
	ifstream in;
	in.open("./input.txt");
	string s;
	vector <suKien> sk;
	getline(in, s);
	string t;
	int d = 0;
	for(int i=1; i<s.size(); i++){
		if(s[i] == '#' || s[i] == '!'){
			suKien x;
			t = s.substr(1, i - 1);
			s.erase(1, i);
			if(d == 1){
				int vitri = t.find(" ");
				x.ma = chuyenDoiSangSo(t.substr(0, vitri));
				t.erase(0, vitri+1);
				switch(x.ma){
					case 6:{
						x.chuThuat = t;
						break;
					}
					case 12:{
						vitri = t.find(" ");
						x.ma1 = t.substr(0, vitri);
						t.erase(0, vitri+1);
						x.ma2 = t;
						break;
					}
					case 13:{
						for(int xx=1; xx<8; xx++)
							for(int yy=1; yy<8; yy++){
								vitri = t.find(" ");
								int	gtri = chuyenDoiSangSo(t.substr(0, vitri));
								t.erase(0, vitri+1);
								x.maTrix[xx][yy] = gtri;
							}
						break;
					}
					case 14:{
						vitri = t.find(" ");
						int	gtri = chuyenDoiSangSo(t.substr(0, vitri));
						t.erase(0, vitri+1);
						x.giaTri = gtri;
						do{
							vitri = t.find(" ");
							gtri = chuyenDoiSangSo(t.substr(0, vitri));
							t.erase(0, vitri+1);
							x.mang.push_back(gtri);
						}while(vitri != -1);
						break;
					}
				}
			}else
				x.ma = chuyenDoiSangSo(t);
			sk.push_back(x);
			i = 0;	
		}
		if(s[i] == 32){
			d = 1;
		}	
	}
	return sk;
}
int main(){
	
	for(int i=0; i<sk.size(); i++){
		cout << sk[i].ma << "+";
		switch(sk[i].ma){
			case 6:{
				cout << sk[i].chuThuat;
				break;
			}
			case 12:{
				cout << sk[i].ma1 << "+" << sk[i].ma2 << "+";
				break;
			}
			case 13:{
				for(int xx=1; xx<8; xx++){
					for(int yy=1; yy<8; yy++)
						cout << sk[i].maTrix[xx][yy] << " ";
					cout << endl;
				}
				break;
			}
			case 14:{
				for(int j=0; j<sk[i].mang.size(); j++)
					cout << sk[i].mang[j] << "+";
				break;
			}
		}
		cout << endl;
	}
}

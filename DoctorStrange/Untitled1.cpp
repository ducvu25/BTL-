#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;
int sk8 = 0;
struct ThongTin{
	int HPmax;
	int HP;
	int LV;
	int EXP;
	int TS;
	int BiCuop = 0;
	int SDAo = -1;
	int TuocAo = 0;
	int PhuThuy = -2;
	int That = 1;
	int Nam = 0;
};
struct suKien{
	int ma;
	string chuThuat;
	string ma1, ma2;
	int maTrix[8][8];
	vector <int> mang;
	int giaTri;
};
int chuyenDoiSangSo(string s);
vector <suKien> DocDuLieu(ifstream &input);
void ChuanHoa(ThongTin &x);
void TTQuai(int &LVo, int &dame, int &Exp, int i, int sk); // Thong tin quai
void SK1_5(ThongTin &x, int i, int sk); // sk 1->5
void SK6(ThongTin &x, int i);
int KTNT(int n);
int NTGanNhat(int n);
int SK12(string s1, string s2);
int fbnc(int x);
int TongMatrix(int a[8][8], int x, int y, int m);
int KTDayTang(int a[][8], int x, int y, int m);
int main(){
	ThongTin nv[100];
	int i = 0, tt = 0;
	int sk15 = 0;
	int quaynguoc;
	char c;
	ifstream input;
	input.open("./input.txt");
	input >> nv[0].HPmax >> nv[0].LV >> nv[0].EXP >> nv[0].TS;
	nv[0].HP = nv[0].HPmax;
	string docDauEnter;
	getline(input, docDauEnter);
	vector <suKien> sk = DocDuLieu(input);
	
	do{
		i++;
		nv[i] = nv[i-1];
		X:
		switch(sk[i-1].ma){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:{
				SK1_5(nv[i], i, sk[i-1].ma);
				if(nv[i].HP < 0){
					if(nv[i].TS > 0){
								nv[i].TS--;
								nv[i].HP = nv[i].HPmax;
							}else{
								cout << -1;
								return 0;
							}
				}
				break;
			}
			case 6:{
				string s = sk[i-1].chuThuat;
				int F = (i + s.size()) & 100;
				int att = 0;
				int def = 0;
				for(int i1=0   ; i1<s.size() - 5; i1++)	if(s[i1] == 'a' || s[i1] == 'A')
				for(int i2=i1+1; i2<s.size() - 4; i2++)	if(s[i2] == 't' || s[i2] == 'T')
				for(int i3=i2+1; i3<s.size() - 3; i3++)	if(s[i3] == 't' || s[i3] == 'T')
				for(int i4=i3+1; i4<s.size() - 2; i4++)	if(s[i4] == 'a' || s[i4] == 'A')
				for(int i5=i4+1; i5<s.size() - 1; i5++)	if(s[i5] == 'c' || s[i5] == 'C')
				for(int i6=i5+1; i6<s.size() - 0; i6++)	if(s[i6] == 'k' || s[i6] == 'K')
					att++;
				for(int i1=0   ; i1<s.size() - 6; i1++)	if(s[i1] == 'd' || s[i1] == 'D')
				for(int i2=i1+1; i2<s.size() - 5; i2++)	if(s[i2] == 'e' || s[i2] == 'E')
				for(int i3=i2+1; i3<s.size() - 4; i3++)	if(s[i3] == 'f' || s[i3] == 'F')
				for(int i4=i3+1; i4<s.size() - 3; i4++)	if(s[i4] == 'e' || s[i4] == 'E')
				for(int i5=i4+1; i5<s.size() - 2; i5++)	if(s[i5] == 'n' || s[i5] == 'N')
				for(int i6=i5+1; i6<s.size() - 1; i6++)	if(s[i6] == 's' || s[i6] == 'S')
				for(int i7=i6+1; i7<s.size() - 0; i7++)	if(s[i7] == 'e' || s[i7] == 'E')
					def++;
				att *= 10;
				def *= 10;
				if(att > F){
					nv[i].EXP += 200;
					nv[i].TS++;
					ChuanHoa(nv[i]);
				}else{
					if(def < 100)
						if(nv[i].HP < 100){ // chet
							if(nv[i].TS > 0){
								nv[i].TS--;
								nv[i].HP = nv[i].HPmax;
							}else{
								cout << -1;
								return 0;
							}
						}else
							nv[i].HP -= nv[i].HP*(100 - def)/100;
				}
				break;
			}
			case 7:{
				if(nv[i].SDAo == -1 && nv[i].TuocAo == 0){
					nv[i].LV += 2;
					if(nv[i].LV > 10)
						nv[i].LV = 10;	
					nv[i].SDAo = 0;
				}
				break;
			}
			case 8:{ // loi
				if(sk8 == 1 && nv[i].PhuThuy == 4 && nv[i].LV < 7)
					nv[i].That = -1;
				else
					nv[i].That = 0;
				if(sk8 == 0){
					nv[i].PhuThuy = 0;
					sk8 = 1;
					nv[i].That = 1;
				}
				break;
			}
			case 9:{
				nv[i].HP = nv[i].HPmax;
				nv[i].Nam = 0;
				if(nv[i].That == -1 && nv[i].PhuThuy != -1)
					nv[i].PhuThuy = -1; // duoi di
				if(nv[i].SDAo == 4)
					nv[i].SDAo = -1;
				break;
			}
			case 10:{
				nv[i].HP += fbnc(nv[i].HP);
				if(nv[i].HP > nv[i].HPmax)
					nv[i].HP = nv[i].HPmax;
				break;
			}
			case 11:{
				if(!(nv[i].PhuThuy != -1 && nv[i].That == 1)){
					nv[i].HP -= 50;
					if(nv[i].Nam == -1){
						if(nv[i].HP > 0){
							nv[i].LV -= 2;
						if(nv[i].LV <= 0)
							nv[i].LV = 1;
						}
						if(nv[i].HP <= 0 && nv[i].TS > 0){
							if(nv[i].That == -1 && nv[i].PhuThuy != -1)
								nv[i].PhuThuy = -1;
							nv[i].TS--;
							nv[i].HP = nv[i].HPmax;
						}
						nv[i].Nam = 0;
					}
				}		
				break;
			}
			case 12:{
				string s1;
				string s2;
				s1 = sk[i-1].ma1;
				s2 = sk[i-1].ma2;
				if(SK12(s1, s2) == 1){
					nv[i].HP = nv[i].HP*0.9 + 0.5; //  lam tron
					nv[i].HPmax = nv[i].HPmax*0.9 + 0.5;
					nv[i].EXP += 30;
					tt = 1;
				}else{
					nv[i].TuocAo = 1;
					nv[i].BiCuop = nv[i].TS;
					nv[i].TS = 0;
					nv[i].EXP += 15;
					tt = -1;
				}
				ChuanHoa(nv[i]);
				break;
			}
			case 13:{ 
				int matrix[8][8];
				for(int x=1; x<8; x++)
					for(int y=1; y<8; y++)
						matrix[x][y] = sk[i-1].maTrix[x][y];
				int m = (i % 7) > 2 ? (i % 7) : 2;
				int x = 1, y = 1, max = TongMatrix(matrix, x, y, m);
				for(int cot=1; cot < 8 - m; cot++)
					for(int hang=1; hang < 8 - m; hang++)
						if(max > TongMatrix(matrix, hang, cot, m)){
							max = TongMatrix(matrix, hang, cot, m);
							x = hang;
							y = cot;
						}
				if(KTDayTang(matrix, x, y, m) == 1){
					nv[i].HP += max*(x+y);
					if(nv[i].HP > nv[i].HPmax)
						nv[i].HP = nv[i].HPmax;
				}else
					nv[i].HP -= max*(x+y);	
				if(nv[i].HP < 0)
					if(tt == 1)
						nv[i].HP = 1;
					else
						if(nv[i].TS > 0){
							nv[i].TS--;
							nv[i].HP = nv[i].HPmax;
						}else{
							cout << -1;
							return 0;
						}
				break;
			}
			case 14:{
				int gtri = sk[i-1].giaTri;
				int dem = sk[i-1].mang.size();
				int max = log(dem)/log(2);
				int dau = 0, cuoi = dem - 1, luot = 0;
				while(max != 0){
					luot++;
					int giua = (dau + cuoi)/2;
					if(sk[i-1].mang[giua] < gtri){
						cuoi = giua - 1;
					}else if(sk[i-1].mang[giua] > gtri){
						dau = giua + 1;
					}else{
						nv[i].HP -= luot*(i % 10) *7;
						nv[i].LV = 1;
						break;
					}
					max --;
				}
				if(max == 0){
					nv[i].EXP += 150;
					nv[i].TuocAo = 0;
					if(tt == -1)
						nv[i].TS = nv[i].BiCuop;
				}
				ChuanHoa(nv[i]);
				break;
			}
			case 15:{
				if(nv[i].TS > 0 && sk15 == 0){
					ThongTin min = nv[i];
					quaynguoc = i;
					for(int ii = i -1; ii >= 0; ii--)
						if(nv[ii].HP > min.HP){
							min = nv[ii];
							quaynguoc = ii;
						}
					nv[quaynguoc].TS = nv[i].TS - 1;
					nv[quaynguoc].LV = 10;
					nv[quaynguoc].EXP = 100;
					int t = i;
					i = quaynguoc;
					quaynguoc = t;
					sk15 = 1;
					goto X;
				}
				break;
			}
		}
		if(nv[i].That == 1)
			nv[i].PhuThuy++;
		if(sk8 == 1 && nv[i].PhuThuy == 4)
			sk8 = -1;
		if(nv[i].Nam != 0){
			nv[i].Nam++;
			if(nv[i].Nam == 4){
				nv[i].Nam = -1;
				nv[i].LV = nv[i-3].LV;
			}
		}
	//	cout << nv[i].HP << " " << nv[i].LV << " " << nv[i].EXP << " " <<nv[i].TS << endl;
	}while(i - 1 < sk.size());
		cout << nv[i].HP + nv[i].LV + nv[i].EXP + nv[i].TS << endl;
	for(int i=0; i<sk.size(); i++)
		cout << nv[i].HP << " " << nv[i].LV << " " << nv[i].EXP << " " <<nv[i].TS << endl;
	
	return 0;
}
int chuyenDoiSangSo(string s){
	int gtri = 0;
	int coSo = 1;
	for(int i=s.size() - 1; i>=0; i--){
		gtri += coSo*(s[i] - 48);
		coSo *= 10;
	}
	return gtri;
}
vector <suKien> DocDuLieu(ifstream &in){
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
void ChuanHoa(ThongTin &x){
	int d = 0;
	if(x.LV < 10 && x.EXP >= 100){
		d = x.EXP / 100;
		x.LV += d;
		x.EXP %= 100;
		if(x.LV > 10){
			d = x.LV - 10;
			x.LV = 10;
		}
		x.HPmax += 50*d;
		x.HP += 10*d;
		if(x.HPmax > 999)
			x.HPmax = 999;
		if(x.HP > x.HPmax)
			x.HP = x.HPmax;
	}else	if(x.EXP > 100)
		x.EXP = 100;
}
void TTQuai(int &LVo, int &dame, int &Exp, int i, int sk){
	int b = i % 10;
	LVo = i > 6 ? (b > 5 ? b : 5) : b;
	float bDame;
	switch(sk){
		case 1:{
			bDame = 1.5;
			Exp = 10;
			break;
		}
		case 2:{
			bDame = 2.5;
			Exp = 20;
			break;
		}
		case 3:{
			bDame = 4.5;
			Exp = 40;
			break;
		}
		case 4:{
			bDame = 7.5;
			Exp = 50;
			break;
		}
		case 5:{
			bDame = 9.5;
			Exp = 70;
			break;
		}
	}
	dame = bDame*LVo*10;
}
void SK1_5(ThongTin &x, int i, int sk){
//	cout << x.HP << " " << x.LV << " " << x.EXP << " " <<x.TS << endl;
	int LVo, dame, Exp;
	TTQuai(LVo, dame, Exp, i, sk);
//	cout << LVo << " " <<Exp << " " << x.LV << endl;
	if(x.That == -1 && x.PhuThuy != -1)	goto Die;
	if(sk8 == 1)	goto Win;
	
	if(x.LV > LVo){
		Win:
		x.EXP += Exp;
	}else	if(x.LV == LVo)
		x.EXP += Exp/2;
	else{
		Die:
		if(x.SDAo != -1 && x.SDAo < 4){
			int y = NTGanNhat(x.HP);
			int G = (i + y) % 100;
			dame *= (100 - G);
			dame /= 100;
			x.SDAo++;
			if(x.SDAo == 4){
				x.LV -=2;
				if(x.LV <= 0)
					x.LV = 1;
			}
		}
		x.HP -= dame;
	}
	if(x.HP <= 0 && x.TS > 0){
		if(x.That == -1 && x.PhuThuy != -1)
			x.PhuThuy = -1;		
		x.TS--;
		x.HP = x.HPmax;
	}
	ChuanHoa(x);
//	cout << x.HP << " " << x.LV << " " << x.EXP << " " <<x.TS << endl;
}
int KTNT(int n){
	for(int i=2; i<=sqrt(n); i++)
		if(n % i == 0)	return 0;
	return n > 1;
}
int NTGanNhat(int n){
	int i = n+1;
	while(KTNT(i) != 1){
		i++;
	}
	return i;
}
int SK12(string s1, string s2){
	char c;
	int tt = s1.size()/2;
	if(tt != 0){
		for(int i=0; i<tt; i++){
			char t = s1[i];
			s1[i] = s1[tt-i-1];
			s1[tt-i-1] = t;
			t = s1[tt + i + 1];
			s1[tt + i + 1] = s1[s1.size()-i -1];
			s1[s1.size()-i - 1] = t;
		}
	}
	int ith = s2.size() % 10;
	for(int i=0; i<s1.size(); i++){
		s1[i] += ith;
		if(s1[i] >= 'z'){
			s1[i] = s1[i] - 'z' + 'a';
		}
		if(s1[i] >= 'Z'){
			s1[i] = s1[i] - 'Z' + 'A';
		}
	}
	if(s1.find(s2) != 0)
		return 1;
	return 0;
}
int fbnc(int x){
	int a = 1;
	int b = 1;
	int c = a + b;
	while(c < x){
		c = a + b;
		a = b;
		b = c;
	}
	return a;
}
int TongMatrix(int a[8][8], int x, int y, int m){
	int sum = 0;
	for(int i=0; i<m; i++)
		for(int j=0; j<m; j++)
			sum += a[x+i][y+j];
	return sum;
}
int KTDayTang(int a[][8], int x, int y, int m){
	for(int i=0; i<m; i++)	// cot
		for(int j=1; j<m; j++)
			if(a[x + j][y + i] > a[x + j-1][y + i])
				return 0;
	return 1;
}

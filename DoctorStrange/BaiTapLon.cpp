#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;


int main(){
	int x, z;
	char y;
	ifstream input;
	input.open("D:\\C++\\BTL\\DoctorStrange\\input.txt");
	do{
		x = -1;
		input >> x;
	}while(x != -1);
	input >> z;
	cout << z;
//	int HpMax, Hp, Lv, Exp, Ts;
//	char sk[100];
////	Doc("D:\\C++\\BTL\\DoctorStrange\\input.txt", Hp, Lv, Exp, Ts, sk);
//	HpMax = Hp;
//	int j = -1, i = 0;
//	do{
//		j+= 2;
//		i++;
//		cout << Hp << " " << Lv << " " << Exp << " " << Ts << endl;
//		SuKien(HpMax, Hp, Lv, Exp, Ts, sk[j] - 48, i);
//	//	cout << Hp << " " << Lv << " " << Exp << " " << Ts << " " << sk[i] - 48 << endl;
//		if(Hp <= 0){
//			cout << -1;
//			return 0;
//		}
//	}while(sk[j+1] != '!');
//	cout << Hp + Lv + Exp + Ts;
}

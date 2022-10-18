#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct ChiSo{
	int hp1;
	int hp2;
	int d;
	char t[100];
	int S;	
}CS;

CS Input(char *s);
int KtNguyenTo(int n);
int KtArmstrong(int n);
double P(CS a);
void XuLyDuLieu(CS a, int *P1, int *P2, int *P3, int *P4);
int gs(int s);
int Tx(int n);
double Pt(int s, char *t);
int main(){
//	CS a = Input("D:\\C\\maiAnTiem\\Input.txt");
//	FILE *fb;
//	fb = fopen("D:\\C\\maiAnTiem\\Output.txt", "a");
//	fprintf(fb, "%0.3lf", P(a));

	CS a;
	scanf("%d%d%d%s%d", &a.hp1, &a.hp2, &a.d, a.t, &a.S);
	int p1, p2, p3, p4, g;
	XuLyDuLieu(a, &p1, &p2, &p3, &p4);
	printf("g = %d\n", gs(a.S));
	printf("%d %d %d %d\n", p1, p2, p3, p4);
	printf("p = %0.3lf", P(a));
	return 0;
}


CS Input(char *s){
	CS a;
	FILE *fp = NULL;
	fp = fopen(s, "r");
	fscanf(fp, "%d%d%d%s%d", &a.hp1, &a.hp2, &a.d, a.t, &a.S);
	return a;
}
int KtNguyenTo(int n){
	if(n < 2)	return 0;
	int i;
	for(i = 2; i<= sqrt(n); i++)
		if(n % i == 0)	return 0;
	return 1;
}
int KtArmstrong(int n){
	int sum = 0;
	int m = n;
	while(n != 0){
		sum += pow(n % 10, 3);
		n /= 10;
	}
	if(m == sum)	return 1;
	return 0;
}
double P(CS a){
	double f;
	double p;
	int P1, P2, P3, P4;
	XuLyDuLieu(a, &P1, &P2, &P3, &P4);
	if(KtArmstrong(a.hp1) == 1 && KtArmstrong(a.hp2) == 1)	return 1;
	if(a.d < 200){
		f = 0;
	}else if(a.d < 300){
		double die = ((a.d + P1 + P2) + (a.d + P3 + P4))*1.0/2000;
		if(die > 0.8) return 0;
		else{
			a.hp1 -= 100;
			a.hp2 -= 50;
			a.d += 100;
			XuLyDuLieu(a, &P1, &P2, &P3, &P4);
		}
	}
	if(300 <= a.d && a.d <= 800){
		f = (40 - abs(a.d - 500)*1.0/20 + gs(a.S))*(1.0 + Pt(a.S, a.t));
	}else	if(a.d > 800){
		f = (-a.d*a.S*1.0)/1000;
	}
	printf("%0.3lf\n", f);
	p = (P1 + P2*f)/(1000 + abs(P2*f)) + (P3 + P4*f)/(1000 + abs(P4*f));
	p /= 2;
	if(p < 0)	return 0;
	if(p > 1) 	return 1;
	return p;
}
void XuLyDuLieu(CS a, int *P1, int *P2, int *P3, int *P4){
	if(KtNguyenTo(a.hp1) == 1){
		*P1 = 1000;
		*P2 = (a.hp1 + a.S) % 1000;
	}else{
		*P1 = a.hp1;
		*P2 = (a.hp1 + a.d) % 100;
	}
	if(KtNguyenTo(a.hp2) == 1){
		*P3 = a.hp2;
		*P4 = (a.hp2 + a.d) % 100;
	}else{
		*P3 = 1000;
		*P4 = (a.hp2 + a.S) % 1000;
	}
}
int gs(int s){
	if(s % 6 == 0)	return 2*s;
	if(s % 6 == 1)	return s/2;
	if(s % 6 == 2)	return -pow(s%9, 3)/5;
	if(s % 6 == 3)	return -pow(s%30, 2) + 3*s;
	if(s % 6 == 4)	return -s;
	if(s % 6 == 5)	return -Tx((s%5) + 5);
}
int Tx(int n){
	if(n == 1)	return 1;
	return n + Tx(n - 1);
}
double Pt(int s, char *t){
	double x;
	if(strcmp(t, "Flood") == 0)	x = 0;
	else	if(strcmp(t, "Storm") == 0)	x = 5;
	else	if(strcmp(t, "Rain") == 0)	x = 10;
	else	if(strcmp(t, "Shower") == 0)	x = 15;
	else	if(strcmp(t, "Drizzle") == 0)	x = 20;
	else	if(strcmp(t, "Cloudy") == 0)	x = 25;
	
	int d = s % 6;
	switch(d){
		case 5:{
			x -= 0;
			break;
		}
		case 4:{
			x -= 5;
			break;
		}
		case 0:{
			x -= 10;
			break;
		}
		case 1:{
			x -= 15;
			break;
		}
		case 2:{
			x -= 20;
			break;
		}
		case 3:{
			x -= 25;
			break;
		}
	}
	return x/100.0;
}

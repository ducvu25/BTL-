#include <stdio.h>
#include <string.h>
#include <math.h>
void DocDuLieu(int *hp1, int *hp2, int *d, char *t, int *s, char *a){
	FILE *file = NULL;
	file = fopen(a, "r");
	fscanf(file, "%d%d%d%s%d", hp1, hp2, d, t, s);
}
int KiemTraSNT(int a){
	int i;
	for(i = 2; i <= sqrt(a); i++)
		if( a % i == 0)	return 0;
	return a >= 2;
} 

int KiemTraSAT(int a){
	int i, sum = a;
	while(a > 0){
		sum -= pow(a % 10, 3);
		a /= 10;
	}
	return sum == 0;
}
void TinhToanP1(int hp1, int d, int s, int *p1, int *p2, int k){ // k == 1: tinh hp1, k == 0 tinh hp2
	if((KiemTraSNT(hp1) == 1 && k == 1) ||  (k == 0 && KiemTraSNT(hp1) == 0)){
		*p1 = 1000;
		*p2 = (hp1 + s) % 1000;
	}else{
		*p1 = hp1;
		*p2 = (hp1 + d) % 100;
	}
}
void TinhToanP(int hp1, int hp2, int d, int s, int *p1, int *p2, int *p3, int *p4){
	TinhToanP1(hp1, d, s, p1, p2, 1);
	TinhToanP1(hp2, d, s, p3, p4, 0);	
}
double TinhPt(char *t, int s){
	int kq;
	if(s % 6 == 5)	kq = 0;
	else if(s % 6 == 4)	kq = -5;
	else if(s % 6 == 0)	kq = -10;
	else if(s % 6 == 1)	kq = -15;
	else if(s % 6 == 2)	kq = -20;
	else if(s % 6 == 3)	kq = -25;
	
	char ss1[100], ss2[100], ss3[100], ss4[100], ss5[100], ss0[100];
	strcpy(ss0, "Flood");
	strcpy(ss1, "Storm");
	strcpy(ss2, "Rain");
	strcpy(ss3, "Shower");
	strcpy(ss4, "Drizzle");
	strcpy(ss5, "Cloudy");
	
	if(strcmp(ss0, t) == 0)	kq += 0;
	else	if(strcmp(ss1, t) == 0)	kq += 5;
	else	if(strcmp(ss2, t) == 0)	kq += 10;
	else	if(strcmp(ss3, t) == 0)	kq += 15;
	else	if(strcmp(ss4, t) == 0)	kq += 20;
	else	if(strcmp(ss5, t) == 0)	kq += 25;
	
	return kq*1.0/100;
}
int TinhT(int n){
	return (n + 1)*n/2;
}
int main(){
	int hp1, hp2, d, s;
	char t[100];
	int p1, p2, p3, p4, g;
	double f, p, ran;
	DocDuLieu(&hp1, &hp2, &d, t, &s, "D:\\C\\maiAnTiem2\\input.txt");
	FILE *out;
	out = fopen("D:\\C\\maiAnTiem2\\output.txt", "w");
	if(KiemTraSAT(hp1) == 1 && KiemTraSAT(hp2) == 1){
		fprintf(out, "1.000");
		return 0;
	}
	if(d < 200){
		f = 0;
	}else if(d < 300){
		TinhToanP(hp1, hp2, d, s, &p1, &p2, &p3, &p4);
		ran = (double) (2*d + p1 + p2 + p3 + p4) / 2000;
		if(ran > 0.8){
			fprintf(out, "0.000");
			return 0;
		}
		hp1 -= 100;
		hp2 -= 50;
		d 	+= 100;
	}
	TinhToanP(hp1, hp2, d, s, &p1, &p2, &p3, &p4);
	if(300 <= d && d <= 800){
		if(s % 6 == 0)	g = 2*s;
		else if(s % 6 == 1) g = s/2;
		else if(s % 6 == 2) g = -pow(s % 9, 3) / 5;
		else if(s % 6 == 3) g = -pow(s % 30, 2) + 3*s;
		else if(s % 6 == 4) g = -s;
		else if(s % 6 == 5) g = -TinhT((s % 5) + 5);
		
		f = (40 - sqrt(pow(d - 500, 2))/20 + g)*(1 + TinhPt(t, s));
	}else if(d > 800){
		f = (double) (-d*s)/1000;
	}
	p = ((p1 + p2*f)/(1000 + sqrt(pow(p2*f, 2))) + (p3 + p4*f)/(1000 + sqrt(pow(p4*f, 2))))/2.0;
	if(p < 0)	p = 0;
	if(p > 1)	p = 1;
	fprintf(out, "%0.3lf", p);
}

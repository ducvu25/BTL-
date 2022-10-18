#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Birth{
	int d;
	int m;
	int y;
}Date;
typedef struct Student{
	char STCode[5];
	char Name[25];
	Date Birthday;
	char Sex[5];
	float Marks;
	char LCapacity[20];	
}ST;
void Standardized(char *a){
	int i;
	if(a[strlen(a) - 1] == '\n')
		a[strlen(a) - 1] = '\0';
	if(a[0] <=122 && a[0] >= 95) a[0] -= 32;
	for(i=1; i<strlen(a); i++){
		if(a[i] == 32 && a[i+1] >= 95 && a[i+1] <=122 ) a[i+1] -= 32;
		else	if(a[i] <=90 && a[i] >= 65 && a[i-1] != 32) a[i] += 32;
	}
}
ST Enter(){
	ST a;
	char c;
	printf("Nhap MSV: ");	scanf("%s", a.STCode);
	printf("Nhap ten: ");	fflush(stdin); fgets(a.Name, sizeof(a.Name), stdin);	Standardized(a.Name);
	printf("Nhap ngay sinh: ");	scanf("%d%c%d%c%d", &a.Birthday.d, &c, &a.Birthday.m, &c, &a.Birthday.y);
	printf("Nhap gioi tinh: ");	scanf("%s", a.Sex); Standardized(a.Sex);
	printf("Nhap diem: "); scanf("%f", &a.Marks);
	if(a.Marks >= 9) {strcpy(a.LCapacity, "Gioi");
	}else
	if(a.Marks >= 8){strcpy(a.LCapacity, "Kha");
	}else
	if(a.Marks >= 6){strcpy(a.LCapacity, "Trung binh"); // copy xau trung binh vao a.LCapacity
	}else			strcpy(a.LCapacity, "Yeu");
	return a;
}
void Export(ST a){
	printf("%-8s %-25s %-2d/%-2d/%-10d %-15s %-10.2f %-10s\n", a.STCode, a.Name, a.Birthday.d, a.Birthday.m, a.Birthday.y, a.Sex, a.Marks, a.LCapacity);
}
int Login(){
	char c;
	int count = 3;
	while(count > 0){
		char ID[9];
		char Pass[9];
		int num = 0;
		printf("\n\t\tDang nhap");
		printf("\n\tTK: "); scanf("%s", ID);
		printf("\n\tMK: "); 
		do{
			if(kbhit()){ // kiem tra co bam ban phim hay khong
				c = getch(); // gan ki tu vua nhap vao c
				if(c != 13){
					Pass[num] = c;
					num++;
					printf("*");
				}else
					break;
			}
		}while(1);
		if(strcmp(ID, "Nhom7") == 0 && strcmp(Pass, "nhom7") == 0)
			return 1;
		else{
			printf("\n\tSai tk hoac mk!");
			count--;
			getch();
			system("cls"); //  xoa man hinh
		}
	}
	return 0;
}
void EnterSTList(ST *x, int *n, char *s){
	FILE *input;
	input = fopen(s, "r");
	fscanf(input, "%d", n);
	int i;
	char t[10];
	char c;
	for(i=0; i<*n; i++){
		ST a;
		fscanf(input, "%s", a.STCode);
		fgets(t, sizeof(t), input);
		 fgets(a.Name, sizeof(a.Name), input);	Standardized(a.Name);
		fscanf(input, "%d%c%d%c%d", &a.Birthday.d, &c, &a.Birthday.m, &c, &a.Birthday.y);
		fscanf(input, "%s", a.Sex); Standardized(a.Sex);
		fscanf(input, "%f", &a.Marks);
		if(a.Marks >= 9) 			strcpy(a.LCapacity, "Gioi");
		else	if(a.Marks >= 8)		strcpy(a.LCapacity, "Kha");
		else	if(a.Marks >= 6)		strcpy(a.LCapacity, "Trung binh");
		else							strcpy(a.LCapacity, "Yeu");
		x[i] = a;
	}
}
void ExportList(ST *a, int n){
	printf("================================== DANH SACH SINH VIEN ======================================\n");
	printf("%-8s %-25s %-16s %-15s %-10s %-10s\n", "MSV", "Ho va Ten", "Ngay sinh", "Gioi tinh", "Diem", "Hoc luc");
	int i;
	for(i=0; i<n; i++)
		Export(a[i]);	
}

void Delete(ST *a, int *n, char *STCodes){
	int i, d = 0; //  bien d kiem xem id co trong ds k
	for(i=0; i<*n; i++){
		if(strcmp(a[i].STCode, STCodes) == 0){
			d = 1;
			break;
		}
	}
	if(d == 0){
		printf("\n%s khong co trong ds", STCodes);
		return;
	}
	*n -= 1;
	for(; i<*n; i++)
		a[i] = a[i+1];
}
void Update(ST *a, int n, char *STCodes){
	int i;
	char c;
	// strcmp: so sanh 
	// strcpy: sao chep
	for(i=0; i<n; i++){
		if(strcmp(a[i].STCode, STCodes) == 0 ){
			printf("Nhap ten: ");	fflush(stdin); fgets(a[i].Name, sizeof(a[i].Name), stdin);	Standardized(a[i].Name);
			printf("Nhap ngay sinh: ");	scanf("%d%c%d%c%d", &a[i].Birthday.d, &c, &a[i].Birthday.m, &c, &a[i].Birthday.y);
			printf("Nhap gioi tinh: ");	scanf("%s", a[i].Sex); Standardized(a[i].Sex);
			printf("Nhap diem: "); scanf("%f", &a[i].Marks);
			if(a[i].Marks >= 9) {strcpy(a[i].LCapacity, "Gioi");
			}else	if(a[i].Marks >= 8){strcpy(a[i].LCapacity, "Kha");
			}else	if(a[i].Marks >= 6){strcpy(a[i].LCapacity, "Trung binh"); // copy xau trung binh vao a.LCapacity
			}else			strcpy(a[i].LCapacity, "Yeu");
			printf("\nCap nhat ten thanh cong!");
			return;
		}
	}
	printf("\nID khong co trong danh sach!");
}
void Search(ST *a, int n, char *STCodes){
	int i;
	for(i=0; i<n; i++)
		if(strcmp(a[i].STCode, STCodes) == 0){
			printf("Sinh vien co ID: %s.\n", STCodes);
			Export(a[i]);
			return;
		}
	printf("Danh sach sinh vien khong co ID: %s.\n", STCodes);
}
void GhiFile(ST *b, int n, char *x){
	FILE* output = fopen(x, "w");
	int i;
	fprintf(output, "====================================== DANH SACH SINH VIEN =============================================\n\n");
	fprintf(output, "%-8s %-25s %-16s %-15s %-10s %-10s\n", "MSV", "Ho va Ten", "Ngay sinh", "Gioi tinh", "Diem", "Hoc luc");
	
	for(i=0; i<n; i++){
		ST a = b[i];
		fprintf(output, "%-8s %-25s %-2d/%-2d/%-10d %-15s %-10.2f %-10s\n", a.STCode, a.Name, a.Birthday.d, a.Birthday.m, a.Birthday.y, a.Sex, a.Marks, a.LCapacity);
	}
	fclose(output);
}

int main(){
	int d = Login();
	if(d == 0)	return 0;
	system("cls");
	int m = 0, n;
	ST a[100];
	EnterSTList(a, &n, "D:\\C\\quanLiSV\\input.txt");	
	int k;
	do{
		system("cls");
		printf("\n===============MENU=============\n");
		printf("1. Them sinh vien.\n");
		printf("2. Hien thi danh sach.\n");
		printf("3. cap nhat sinh vien theo MSV.\n");
		printf("4. Xoa sinh vien theo MSV.\n");
		printf("5. Tim sinh vien theo ten.\n");
		printf("6. Ghi vao file.\n");
		printf("0. Ket thuc.\n");
		printf("Lua chon thao tac: "); scanf("%d", &k);
		switch (k){
			case 1: {
				char c;
				do{
					a[n] = Enter();
					n++;
					printf("Ban co muon nhap tiep khong(y/n)? ");
					fflush(stdin);
					scanf("%c", &c);
				}while(c == 'y');
				break;		
			}
			case 2: {
				ExportList(a, n);
				break;
			}
			case 3: {
				printf("Nhap MSV: ");
				char x[5]; scanf("%s", x);
				Update(a, n, x);
				break;
			}
			case 4: {
				printf("Nhap MSV: ");
				char x[5]; scanf("%s", x);
				Delete(a, &n, x);
				break;
			}
			case 5: {
				printf("Nhap ten ID: "); char x[5]; fflush(stdin); fgets(x, sizeof(x), stdin); 
				Search(a, n, x);
				break;
			}
			case 6:{
				GhiFile(a, n, "D:\\C\\quanLiSV\\output.txt");
				break;
			}
			case 0:{
				printf("================================== Cam on da su dung =================================");
				break;
			}
		}
	printf("\nBam phim bat ki de tro ve!");
	getch();
	}while (k != 0);
	return 0;
}








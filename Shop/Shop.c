#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Product{
	char Id[10];
	char Name[15];
	int Price;
	int Value;
}P;
void DeleteEnter(char *s){
	if(s[strlen(s) - 1] == '\n')
		s[strlen(s) - 1] = '\0';
}
P EnterP(){
	char temp;
	P a;
	printf("\n\tEnter product information:");
	printf("\nEnter id: ");		scanf("%s", a.Id);
	printf("Enter product: ");	fflush(stdin);	fgets(a.Name, sizeof(a.Name), stdin);	DeleteEnter(a.Name);
	printf("Enter price: ");	scanf("%d", &a.Price);
	printf("Enter value: "); 	scanf("%d", &a.Value);
	return a;
}
void ReadFile(P *a, int *n, char *s){
	FILE *input = fopen(s, "r");
	
	fscanf(input, "%d", n);
	int i;
	char c;
	for(i=0; i<*n; i++){
		fscanf(input, "%s", a[i].Id);
		fscanf(input, "%c", &c);
		fgets(a[i].Name, sizeof(a[i].Name), input);	DeleteEnter(a[i].Name);
		fscanf(input, "%d", &a[i].Price);
		fscanf(input, "%d", &a[i].Value);
	}
	fclose(input);
}
void ExportListP(P *a, int n, char *s){
	int i;
	FILE *output = fopen(s, "w");
	
	fprintf(output, "\n\t\t\tLIST PRODUCT \n\n");
	fprintf(output, "\t%-5s %-10s %-20s %-10s %-10s\n", "STT", "ID", "Product's name", "Price", "Value");
	for(i=0; i<n; i++){
		if(a[i].Value != 0)
			fprintf(output, "\t%-5d %-10s %-20s %-10d %-10d\n", i + 1, a[i].Id, a[i].Name, a[i].Price, a[i].Value);
		else
			fprintf(output, "\t%-5d %-10s %-20s %-10d %-10s\n", i + 1, a[i].Id, a[i].Name, a[i].Price, "Out of stock");
		}
	fclose(output);
}
void Menu(){
	printf("\n\tBlackMoji store\n");
	printf("\n\t\tMENU");
	printf("\n\t1. Start shop");
	printf("\n\t2. Insert product");
	printf("\n\t3. Search product");
	printf("\n\t4. Delete product");
	printf("\n\t5. Update product");
	printf("\n\t6. Arrange product");
	printf("\n\t7. Export list product");
	printf("\n\t0. Exit");
	printf("\n\t\tFunction: ");
}
void Search(P *a, int n, char *Ids){
	int i;
	for(i=0; i<n; i++)
		if(strcmp(a[i].Id, Ids) == 0){
			printf("\n\tProduct information you find:");
			printf("\n\tID: %s", a[i].Id);
			printf("\n\tProduct's name: %s", a[i].Name);
			printf("\n\tPrice: %d",a[i].Price);
			printf("\n\tValue: %d", a[i].Value);
			return;
		}
	printf("\n\t\tNo product with that Id: %s", Ids);
}
void Delete(P *a, int *n, char *Ids){
	int i;
	for(i=0; i<*n; i++)
		if(strcmp(a[i].Id, Ids) == 0)
			break;
	if(i == *n){
		printf("\n\t\tNo product with that Id: %s", Ids);
		return;
	}
	int m = *n;
	m--;
	*n = m;
	for(; i<*n; i++)
		a[i] = a[i+1];
	printf("\n\tDeleted product.");
}
void Update(P *a, int n, char *Ids){
	int i;
	for(i=0; i<n; i++)
		if(strcmp(a[i].Id, Ids) == 0){
			printf("Enter product: ");	fflush(stdin);	fgets(a[i].Name, sizeof(a[i].Name), stdin);	
			printf("Enter price: ");	scanf("%d", &a[i].Price);
			printf("Enter value: "); 	scanf("%d", &a[i].Value);
			printf("\n\tUpdated complete!");
			return;
		}
	printf("\n\t\tNo product with that Id: %s", Ids);
}
void Sort(P *a, int n){
	int i, j;
	for(i=0; i<n-1; i++)
		for(j=i+1; j<n; j++)
			if(a[i].Value > a[j].Value){
				P t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
}
int Login(){
	char Account[20];
	char Password[20];
	int count = 3;
	char c;
	while(count > 0){
		printf("\n\t\tLogin\n");
		printf("\tAccount: ");	scanf("%s", Account);
		printf("\tPassword: ");
		int i = 0;
		do{
			if(kbhit()){
				c = getch();
				if(c == 13)
					break;
				else{
					Password[i] = c;
					i++;
					printf("*");
				}
			}
		}while(1);
		if(strcmp(Account,"huyhoang") == 0 && strcmp(Password, "123456") == 0)
			return 1;
		printf("\nWrong account or password");
		count--;
		getch();
		system("cls");
	}
	return 0;
}
int main(){
//	if(Login() != 1)	return 0;
	int k, n;
	P a[100];
	do{
		system("cls"); // Xoa man hinh
		Menu();
		scanf("%d", &k);
		fflush(stdin);
		switch(k){
			case 1:{
				printf("\n\tFunction 1: Start shop");
				ReadFile(a, &n, "D:\\C++\\anhHoang\\input.txt");
				printf("\n\t\t Started shop!"); 
				break;
			}
			case 2:{
				printf("\n\tFunction 2: Insert product");
				char c;
				do{
					a[n] = EnterP();
					n++; // so luong sp
					printf("\n\tDo you want to continue(y/n)?");
					fflush(stdin);
					scanf("%c", &c);
					} 
				while(c == 'y');
				break;
			}
			case 3:{
				printf("\n\tFunction 3: Search product");
				char Ids[10];
				printf("\n\tEnter product ID: ");
				scanf("%s", Ids);
				Search(a, n, Ids);
				break;
			}
			case 4:{
				printf("\n\tChuc nang 4: Delete product"); // 
				char Ids[10];
				char c;
				printf("\n\tEnter product ID: ");
				scanf("%s", &Ids);
				printf("\n\tAre you sure you want to delete that product?(y/n)?");
				fflush(stdin);
				scanf("%c", &c);
				if(c == 'y')	Delete(a, &n, Ids);
				else	printf("\n\t\taction has been cancelled"); 
				break;
			}
			case 5:{
				printf("\n\tChuc nang 5: Update product");
				char Ids[10];
				printf("\n\tEnter product ID: ");
				scanf("%s", Ids);
				Update(a, n, Ids);
				break;
			}
			case 6:{
				printf("\n\tChuc nang 6: Sort product (Sort by quantity)");
				Sort(a, n);
				printf("\n\tSorted complete!");
				break;
			}
			case 7:{
				if(n <= 0)	printf("\n\tThe stall is empty or not started!");
				else	ExportListP(a, n, "D:\\C++\\anhHoang\\output.txt");
				break;
			}
			case 0:{
				printf("\n\t\tGoodbye!");
				return 0;
			}
		}
		printf("\n\t\tPress any key to go back!");
		getch();
	}while(k != 0);
}

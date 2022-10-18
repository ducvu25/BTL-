#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
#include <conio.h> 
using namespace std;
#define MAXSIZE 10000 // số lượng tối đa khách
#define MAXSIZEQUEUE 100 // số lượng hàng đợi tối đa
#define MAXSIZETELLER 100 // số lượng giao dịch viên tối đa
int nCus = 0; // số lượng khách
int top = 0; // số lượng khách ở đợi
int nTel = 2; // số lượng giao dịch viên
float spaceTime = 0; // tổng thời gian rảnh
float timeserver = 0; // tổng thời gian phục vụ
float waitingTime = 0; // tổng thời gian chờ
struct Customer { //Cấu trúc khách hàng
	float arrivalTime; // thời gian đến
	float time; // thời gian cần giao dịch
	int priority; // độ ưu tiên
};
struct Teller {
	float time;
	int cus;
};
void pop();
void Push(Customer x);
bool isEmpty();
Customer customers[MAXSIZE]; // danh sách khách
Customer Cqueue[MAXSIZEQUEUE]; // danh sách hàng đợi
Teller Tellers[MAXSIZETELLER]; // danh sách giao dịch viên

bool Input(char* s);
void InitTellers();

void Mega(Customer* a, int left, int mid, int right, bool tangDan);
void MegaSort(Customer* a, int left, int right, bool tangDan);
int main() {
	clockt start, end;
	start = clock();
	char input[] = "D:/Nam 2/codethue/Nganhang/Nganhang/as-sample.txt";
	if (Input(input) == false) {
		cout << "Not file input!";
	}
	else {
		int lenQueueMax = 0;
		// Xử lý khách có thể
	 	InitTellers();
		int n = 0; // số lượng khách hàng được thực hiện
		while(n < nCus){
			while (1) {
				int index = -1; // khong nhan vien nao ranh
				float max = -1;
				for (int i = 0; i < nTel; i++) {
					float time = customers[n].arrivalTime - Tellers[i].time;
					if (time >= 0 && time > max) {
						max = time;
						index = i;
					}
				}
				if (index == -1) // không còn nhân viên rảnh
					goto Out;
				spaceTime += customers[n].arrivalTime - Tellers[index].time;
				Tellers[index].time = customers[n].arrivalTime + customers[n].time;
				Tellers[index].cus++;
				n++;
				// thong tin nhan vien
				// cout << "\nNhan vien:\n";
				// for (int x = 0; x < nTel; x++)
				// 	cout << Tellers[x].cus << "\t\t" << Tellers[x].time << endl;
				// cout << "Tong thoi gian ranh: " << spaceTime << endl;
				// getch();
				if (n == nCus)
					goto Stop;
			}
		Out:
			//cout << "Tong thoi gian ranh: " << spaceTime << endl;
			// Xử lý khách ở hàng đợi
			top = 0;
			do{
				// tìm nhân viên xong sớm nhất
				int index = 0; // nhân viên đầu tiên;
				for(int i=1; i<nTel; i++)
					if(Tellers[i].time < Tellers[index].time)
						index = i;
				// vi tri tim duoc
				// cout << "vi tri nhan vien: " << index << endl;
				// getch();
				// tìm được nhân viên sắp xong
				for(int i=n; i<nCus; i++)
					if(customers[i].arrivalTime <= Tellers[index].time){// them khach vao hang doi
						Push(customers[i]);
						n++;
					}else
						break;
				if(top > lenQueueMax)
					lenQueueMax = top;
				MegaSort(Cqueue, 0, top - 1, false);
				// thong tin trong hang doi
				// cout << "Hang doi:\n";
				// for(int i=0; i<top; i++)
				// 	cout << Cqueue[i].arrivalTime  << " " << Cqueue[i].time << " " << Cqueue[i].priority << endl;
				// cout << endl;
				Customer p = Cqueue[0];
				pop();
				waitingTime += (Tellers[index].time -  p.arrivalTime);// thời gian chờ = thời gian bắt đầu xử lí - thời gian đến
				Tellers[index].time += p.time; // thời gian làm việc
				Tellers[index].cus ++;
				// thong tin nhan vien
				// cout << "Thong tin nhan vien sau:\n";
				// for (int x = 0; x < nTel; x++)
				// 	cout << Tellers[x].cus << "\t\t" << Tellers[x].time << endl;
				// cout << endl;
				// getch();
			}while(isEmpty() != true);// thuc hien den khi hang doi het
		}
		Stop:
		for(int i=0; i<nTel; i++){
			if(Tellers[i].time < customers[n-1].arrivalTime){
				float t = customers[n-1].arrivalTime + customers[n-1].time - Tellers[i].time;
				if(t > 0)
					spaceTime += t;
			}
		}
		cout << "Tong thoi gian ranh: " << spaceTime << endl;
		cout << "Thong tin so khach cua tung nhan vien:\n";
		for (int x = 0; x < nTel; x++)
			cout << "Nhan vien so " << x << ": " <<  Tellers[x].cus << endl;
		cout << endl;
	}
	end = clock();
	cout << "\nTime: " << double(end - start) / CLOCKSPERSEC;
	return 0;
}
void pop() {
	if(top <= 0)
		return;
	top--;
	for (int i = 0; i < top; i++)
		Cqueue[i] = Cqueue[i + 1];
}
void Push(Customer x){
	Cqueue[top] = x;
	top++;
}
bool isEmpty() {
	if (top == 0)
		return true;
	return false;
}
bool Input(char* s) {
	ifstream cin(s);
	if (cin) {
		float x, y;
		int z;
		do {
			cin >> x >> y;
			if (x == y && y == 0)
				break;
			cin >> z;
			customers[nCus].arrivalTime = x;
			customers[nCus].time = y;
			timeserver += y; // thời gian phục vụ
			customers[nCus].priority = z;
			nCus++;
		} while (1);
		timeserver /= nCus; // thời gian trung bình
		cin.close();
		return true;
	}
	return false;
}
void InitTellers() {
	//cout << "Enter the number teller: "; cin >> nTel;
	for (int i = 0; i < nTel; i++) {
		Tellers[i].time = 0; // bắt đầu làm việc
		Tellers[i].cus = 0; // số lượng người đã làm việc 0
	}
}
// sap xep 
void Mega(Customer* a, int left, int mid, int right, bool tangDan) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	Customer* a1 = new Customer[n1];
	Customer* a2 = new Customer[n2];
	// copy day ben trai
	for(int i=0; i < n1; i++){
		a1[i] = a[left + i];
	}
	// copy day ben phai
	for (int i = 0; i < n2; i++) {
		a2[i] = a[mid + 1 + i];
	}
	int x1 = 0, x2 = 0;
	for (int i = left; i <= right; i++) {
		if ((a1[x1].priority < a2[x2].priority == tangDan && x1 < n1) || x2 == n2) {
			a[i] = a1[x1];
			x1++;
		}
		else {
			a[i] = a2[x2];
			x2++;
		}
	}
}
void MegaSort(Customer* a, int left, int right, bool tangDan) {
	if (left < right) {
		int mid = (left + right) / 2;
		MegaSort(a, left, mid, tangDan);
		MegaSort(a, mid + 1, right, tangDan);
		Mega(a, left, mid, right, tangDan);
	}
}


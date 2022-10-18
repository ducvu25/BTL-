#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <iomanip>
#include "input.h"
#include "Sort.h"
#include "BieuDien.h"
using namespace std;

int main() {
	string name[] = { "Selection", "Interchanger", "InsertionSort", "BubbleSort", "MegaSort", "Quick-Sort" };
	vector <double> time;
	char input[] = { "./input.txt" };
	int n, max, min;
	cout << "Nhap so luong: ";	 cin >> n;
	cout << "Nhap khoang gia tri: "; cin >> min >> max;
	KhoiTao(input, n, max, min);
	clockt start, end;
	int* a;

	a = Input(input, n);
	/*
	start = clock();
	SelectionSort(a, n, true);
	end = clock();
	time.pushback(double(end - start) / CLOCKSPERSEC);

	a = Input(input, n);
	start = clock();
	InterchangerSort(a, n, true);
	end = clock();
	time.pushback(double(end - start) / CLOCKSPERSEC);

	a = Input(input, n);
	start = clock();
	InsertionSort(a, n, true);
	end = clock();
	time.pushback(double(end - start) / CLOCKSPERSEC);

	a = Input(input, n);
	start = clock();
	BubbleSort(a, n, true);
	end = clock();
	time.pushback(double(end - start) / CLOCKSPERSEC);

	a = Input(input, n);
	start = clock();
	MegaSort(a, 0, n-1, true);
	end = clock();
	time.pushback(double(end - start) / CLOCKSPERSEC);

	a = Input(input, n);
	start = clock();
	QuickSort(a, 0, n-1, true);
	end = clock();
	time.pushback(double(end - start) / CLOCKSPERSEC);
	for (int i = 0; i < time.size(); i++)
		cout << name[i] << "\t\t\t" << fixed << setprecision(5) << time[i] << endl;
	*/
	//SelectionSortDT(a, n);
	//InterchangerSortDT(a, n, true);
	//BubbleSortDT(a, n, true);
	Cout(a, n);
	QuickSort(a, 0, n - 1, true);
	/*
	QuickSortDT(a, 0, n-1, true);
	DoThi(a, n, -1, - 1, - 1, 1);
	//MegaSortDT(a, 0, n-1, true);
	QuickSortDT(a, 0, n-1, true);
	DoThi(a, n, -1, -1, -1, 1);
	*/
	gotoXY(setX, setY + 5);
	Cout(a, n);
	return 0;
}
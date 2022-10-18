#include "DoThi.h"

using namespace std;

void TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STDOUTPUTHANDLE), color);
}
void gotoXY(int i, int j) {
	COORD coord;
	coord.X = i;
	coord.Y = j;
	SetConsoleCursorPosition(GetStdHandle(STDOUTPUTHANDLE), coord);
}
void DoThi(int* a, int n, int x, int y, int min, int d) {
	if (d == 1)
		for (int i = 0; i < n; i++) {
			if (i == x)
				TextColor(setColorX);
			else if (i == y)
				TextColor(setColorY);
			else if (i == min)
				TextColor(setColorMin);
			else
				TextColor(setColorN);
			gotoXY(setX + i * 3, setY + 2);
			cout << a[i];
			if (a[i] == 0) {
				gotoXY(setX + i * 3, setY - 1);
				cout << char(95);
			}
			for (int j = 1; j <= a[i]; j++) {
				gotoXY(setX + i * 3, setY - j);
				cout << char(219);
			}
		}
	else
		for (int i = 0; i < n; i++) {
			gotoXY(setX + i * 3, setY + 2);
			cout << "   ";
			for (int j = 1; j <= setY - 3; j++) {
				gotoXY(setX + i * 3, setY - j);
				cout << " ";
			}
		}
}

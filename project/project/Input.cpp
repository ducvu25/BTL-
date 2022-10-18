#include "input.h"

using namespace std;

void KhoiTao(char* s, int n, int max, int min) {
    ofstream cout(s);
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        int x = rand() %(max - min + 1) + min;
        cout << x << endl;
    }
}
int* Input(char* s, int& n) {
    ifstream cin(s);
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    return a;
}
void Cout(int* a, int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}
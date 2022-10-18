#include "BieuDien.h"

using namespace std;

void SelectionSortDT(int* a, int n) {
    DoThi(a, n, -1, -1, -1, 1);
    gotoXY(setX + n * 3 / 2 - 10, setY + 1);
    cout << "Selection - ducvu25 - UET";
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min])
                min = j;
            DoThi(a, n, i, j, min, 0);
            DoThi(a, n, i, j, min, 1);
            Sleep(timeDelete);
        }
        if (a[min] < a[i]) {
            int t = a[min];
            a[min] = a[i];
            a[i] = t;
        }
        DoThi(a, n, i, -1, min, 0);
        DoThi(a, n, i, -1, min, 1);
        Sleep(timeStop);
    }
    DoThi(a, n, -1, -1, -1, 1);
}
void InterchangerSortDT(int* a, int n, bool tangDan) {
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if (a[i] > a[j] == tangDan) {
                DoThi(a, n, i, j, -1, 1);
                Sleep(timeDelete);
                DoThi(a, n, i, j, -1, 0);
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
                DoThi(a, n, i, j, -1, 1);
                Sleep(timeStop);
                DoThi(a, n, i, j, -1, 0);
            }
    DoThi(a, n, -1, -1, -1, 1);
}
void InsertionSortDT(int* a, int n, bool tangDan) {
    DoThi(a, n, -1, -1, -1, 1);
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1] == tangDan) {
            int t = a[i];
            int j = i + 1;
            for (; j > 0; j--) {
                if (a[j] < t == tangDan)
                    break;
                else
                    a[j] = a[j - 1];
                DoThi(a, n, i, j, -1, 1);
                Sleep(timeDelete);
                DoThi(a, n, i, j, -1, 0);
            }
            a[j] = t;
            DoThi(a, n, i, j, -1, 1);
            Sleep(timeStop);
            DoThi(a, n, i, j, -1, 0);
        }
    }
    DoThi(a, n, -1, -1, -1, 1);
}
void BubbleSortDT(int* a, int n, bool tangDan) {
    DoThi(a, n, -1, -1, -1, 1);
    for(int i=0; i<n-1; i++)
        for (int j = n - 1; j > i; j--) {
            if (a[j] < a[j - 1] == tangDan) {
                int t = a[j];
                a[j] = a[j - 1];
                a[j - 1] = t;
            }
            DoThi(a, n, i, j, -1, 1);
            Sleep(timeDelete);
            DoThi(a, n, i, j, -1, 0);
        }
    DoThi(a, n, -1, -1, -1, 1);
}
void MegaDT(int* a, int left, int mid, int right, bool tangDan) {
    int n1 = mid - left + 1,
        n2 = right - mid;
    int* a1 = new int[n1],
        * a2 = new int[n2];
    for (int i = 0; i < n1; i++)
        a1[i] = a[left + i];
    for (int i = 0; i < n2; i++)
        a2[i] = a[mid + 1 + i];

    int x1 = 0, x2 = 0;
    for (int i = left; i <= right; i++) {
        if ((a1[x1] < a2[x2] == tangDan && x1 < n1) || x2 == n2) {
            a[i] = a1[x1];
            x1++;
        }
        else {
            a[i] = a2[x2];
            x2++;
        }
        DoThi(a, right - left + 1, i, -1, -1, 1);
        Sleep(timeDelete);
        DoThi(a, right - left + 1, left + i, -1, -1, 0);
    }
}
void MegaSortDT(int* a, int left, int right, bool tangDan) {
    if (left < right) {
        int mid = (left + right) / 2;
        MegaSortDT(a, left, mid, tangDan);
        MegaSortDT(a, mid+1, right, tangDan);
        MegaDT(a, left, mid, right, tangDan);
    }
}
int QuickDT(int* a, int left, int right, bool tangDan) {
    int index = right;
    int i = left;
    for (int j = left; j < right; j++)
        if (a[j] < a[index] == tangDan) {
            int t = a[j];
            a[j] = a[i];
            a[i] = t;
            i++;
            DoThi(a, right - left + 1, i, j, index, 1);
            Sleep(timeDelete);
            DoThi(a, right - left + 1, i, j, index, 0);
        }
    if (a[i] > a[index] == tangDan) {
        int t = a[i];
        a[i] = a[index];
        a[index] = t;
        DoThi(a, right - left + 1, -1, -1, i, 1);
        Sleep(timeDelete);
        DoThi(a, right - left + 1, -1, -1, i, 0);
        return i;
    }
    return -1;
}
void QuickSortDT(int* a, int left, int right, bool tangDan) {
    if (left < right) {
        int index = QuickDT(a, left, right, tangDan);
        if (index == -1)
            return;
        QuickSortDT(a, left, index - 1, tangDan);
        QuickSortDT(a, index + 1, right, tangDan);
    }
}
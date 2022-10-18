#include <iostream>
#include <vector>
using namespace std;

int kiemTra(vector <int> a, int x){
	for(int i=0; i<a.size(); i++)
		if(a[i] == x)
			return 0;
	return 1;
}
void kq(int a[][100], int m, int n){
	vector <int> A;
	int max = 0;
	int x;
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			if(kiemTra(A, a[i][j])){
				int dem = 0;
				for(int k=i; k<m; k++)
					for(int h=j; h<n; h++)
						if(a[i][j] == a[k][h])
							dem++;
				A.push_back(a[i][j]);
				if(max < dem){
					max = dem;
					x = a[i][j];
				}
			}
	cout << x;
}
int main(){
	int m, n;
	cin >> m >> n;
	int a[100][100];
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			cin >> a[i][j];
	kq(a, m, n);
}

#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
using namespace std;

class SOTIETKIEM{
	private:
		char ma[6];
		char loai[11];
		char ten[31];
		int cmnd;
		float tien;
	public:
		void Nhap(){
			cout << "\nNhap thong tin: ";
			cout << "Nhap ma: "; cin >> ma;
			cin.ignore(); cout << "Nhap loai: ";	cin.getline(loai, 10);
			cout << "Nhap ten: "; cin.getline(ten, 30);
			cout << "Nhap cmnd: "; cin >> cmnd;
			cout << "Nhap tien: "; cin >> tien;
		}
		void Xuat(){
			cout << setw(10) << left << ma 
			<< setw(15) << loai << setw(30) << ten 
			<< setw(10) << cmnd << setw(10) << tien << endl;
		}
		float Tien(){
			return tien;
		}
		int CMND(){
			return cmnd;
		}
};
struct Node{
	SOTIETKIEM data;
	Node* next;
};
Node* newNode(SOTIETKIEM x){
	Node* p = new Node;
	p->data = x;
	p->next = NULL;
	return p;
}
Node* Input(){
	Node* head = NULL;
	int n;
	cout << "Nhap so luong: "; cin >> n;
	for(int i=0; i<n; i++){
		SOTIETKIEM x;
		x.Nhap();
		Node* p =newNode(x);
		p->next = head;
		head = p;
	}
	return head;
}
void Xuat(Node* head){
	cout << "\n\t\t\tDANH SACH\n";
	for(Node* i=head; i != NULL; i = i->next)
		i->data.Xuat();
}
float Sum(Node* head){
	float sum = 0;
	for(Node* i=head; i != NULL; i = i->next)
		sum += i->data.Tien();
	return sum;
}
Node* Search(Node *head, int cmnd){
	for(Node* i=head; i != NULL; i = i->next)
		if(i->data.CMND() == cmnd)
			return i;
	return NULL;
}
int main(){
	Node *head = Input();
	Xuat(head);
	cout << "Tong tien: " << Sum(head) << endl;
	int x;
	cout << "Nhap cmnd: "; cin >> x;
	cout << "Dia chi " << Search(head, x);
}

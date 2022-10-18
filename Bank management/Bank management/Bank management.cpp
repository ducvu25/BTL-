#include <iostream>
#include <fstream>
using namespace std;

#define MAXSIZE 10000 // max size customer
#define MAXSIZEQUEUE 100 // max size queue
#define MAXSIZETELLER 100 // max size teller
int nCus = 0; // number customer
int top = 0; // number queue
int nTel = 0; // number teller
float spaceTime = 0; // Total free time
float timeserver = 0; // Total service time
float waitingTime = 0; //Total waiting time
float simulation_Time = 0; // Simulation time
float queue_time = 0;
int number_queue = 0;
struct Customer { 
	float arrivalTime; 
	float time; 
	int priority; 
};
struct Teller {
	float time;
	int cus;
};
void pop();
void Push(Customer x);
bool isEmpty();
Customer customers[MAXSIZE]; // array customer
Customer Cqueue[MAXSIZEQUEUE]; // array queue
Teller Tellers[MAXSIZETELLER]; // array teller

bool Input(char* s);
void InitTellers();

void Merge(Customer* a, int left, int mid, int right, bool ascending);
void MergeSort(Customer* a, int left, int right, bool ascending);
int main() {
	string input[] = "./as-sample.txt";
	if (Input(input) == false) {
		cout << "Not file input!";
	}
	else {
		int lenQueueMax = 0; // max lenght queue
		int number = 0; //Number of people not involved in queue
		// Guest treatment can
		InitTellers();
		int n = 0; // The number of customers is made
		while (n < nCus) { // Perform until the end of the guest
			while (1) {
				int index = -1; // No employee is free
				float max = -1;
				for (int i = 0; i < nTel; i++) {
					float time = customers[n].arrivalTime - Tellers[i].time;
					if (time >= 0 && time > max) {
						max = time;
						index = i;
					}
				}
				if (index == -1) // No employee is free
					goto Out;

				spaceTime += customers[n].arrivalTime - Tellers[index].time; // Free time = Time to receive jobs - Time is done before
				Tellers[index].time = customers[n].arrivalTime + customers[n].time; //Time finished work
				Tellers[index].cus++;
				number++;
				timeserver += customers[n].time;
				n++;

				if (n == nCus) {
					simulation_Time = Tellers[index].time;
					for (int i = 0; i < nTel; i++) {
						if (Tellers[i].time < customers[n - 1].arrivalTime) {
							float t = customers[n - 1].arrivalTime + customers[n - 1].time - Tellers[i].time;
							if (t > 0)
								spaceTime += t;
						}
					}
					goto Stop;
				}
			}
		Out:

			//Handling guests in queue
			top = 0;
			float denta = customers[n].arrivalTime;
			float end = -1;
			do {
				//Find the employee finished the earliest
				int index = 0; // first teller
				for (int i = 1; i < nTel; i++)
					if (Tellers[i].time < Tellers[index].time)
						index = i;


				// Find the employee is about to finish
				for (int i = n; i < nCus; i++)
					if (customers[i].arrivalTime <= Tellers[index].time) {// add customer to queue
						Push(customers[i]);
						n++;
					}
					else
						break;
				if (top > lenQueueMax)
					lenQueueMax = top;
				MergeSort(Cqueue, 0, top - 1, false);

				Customer p = Cqueue[0];
				pop();
				waitingTime += (Tellers[index].time - p.arrivalTime);//Standing time = Starting time - arrival time
				end = Tellers[index].time;
				Tellers[index].time += p.time; //working time
				Tellers[index].cus++;

				if (n == nCus)
					simulation_Time = Tellers[index].time;
			} while (isEmpty() != true);// work where queue not is empty
			if (end != -1) {
				number_queue++;
				queue_time += (end - denta);
			}
		}
	Stop:
		cout << "Total free time of employees: " << spaceTime << endl;
		cout << "Number of customers of each employee:\n";
		for (int x = 0; x < nTel; x++)
			cout << "Teller number " << x << ": " << Tellers[x].cus << endl;
		cout << "Simulation time: " << simulation_Time << endl;
		cout << "Average service time: " << timeserver / number << endl;
		cout << "The average waiting time of each customer: " << waitingTime / (nCus - number) << endl;
		cout << "Maximum length of the queue: " << lenQueueMax << endl;
		cout << "The average length of the queue: " << queue_time / number_queue << endl;
		cout << "The ratio is leisurely: " << spaceTime / simulation_Time << endl;
	}
	return 0;
}
void pop() {
	if (top <= 0)
		return;
	top--;
	for (int i = 0; i < top; i++)
		Cqueue[i] = Cqueue[i + 1];
}
void Push(Customer x) {
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
			customers[nCus].priority = z;
			nCus++;
		} while (1);
		timeserver /= nCus; // The average time
		cin.close();
		return true;
	}
	return false;
}
void InitTellers() {
	cout << "Enter the number teller: "; cin >> nTel;
	for (int i = 0; i < nTel; i++) {
		Tellers[i].time = 0; //start work
		Tellers[i].cus = 0; // Number of people working 0
	}
}
// sort
void Merge(Customer* a, int left, int mid, int right, bool ascending) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	Customer* a1 = new Customer[n1];
	Customer* a2 = new Customer[n2];
	// copy array left
	for (int i = 0; i < n1; i++) {
		a1[i] = a[left + i];
	}
	// copy array right
	for (int i = 0; i < n2; i++) {
		a2[i] = a[mid + 1 + i];
	}
	int x1 = 0, x2 = 0;
	for (int i = left; i <= right; i++) {
		if ((a1[x1].priority < a2[x2].priority == ascending && x1 < n1) || x2 == n2) {
			a[i] = a1[x1];
			x1++;
		}
		else {
			a[i] = a2[x2];
			x2++;
		}
	}
}
void MergeSort(Customer* a, int left, int right, bool ascending) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(a, left, mid, ascending);
		MergeSort(a, mid + 1, right, ascending);
		Merge(a, left, mid, right, ascending);
	}
}

/*
test khac
1 3 1
2 5 1
3 8 2
4 5 2
4 2 3
5 3 3
5 1 1
20 2 1
21 5 2
22 7 1
22 8 1
23 3 3
24 5 3
0 0
*/

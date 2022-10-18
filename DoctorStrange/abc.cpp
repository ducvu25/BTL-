//The library here is concretely set, students are not allowed to include any other libraries.

#include "doctorStrange.h"
using namespace std;
int readFile(const string & filename, string & HP, string & LV, string & EXP, string & TS, string & events) {
    //This function is used to read the input file,
    //DO NOT MODIFY THIS FUNTION
    ifstream myfile;
    myfile.open("D:\\C++\\BTL\\DoctorStrange\\input.txt");
        myfile >> HP
               >> LV
               >> EXP
               >> TS;
    string s;
    getline(myfile, s);
    getline(myfile, events);
    
    return 1;
}

int main(int argc, char* argv[]) {
	cout << "hi";
    string filename = "D:\\C++\\BTL\\DoctorStrange\\input.txt";
    string HP, LV, EXP, TS, events;

    bool isRead = readFile(filename, HP, LV, EXP, TS, events);
    if (isRead) {
        cout << handleEvents(HP, LV, EXP, TS, events);
    }
    else {
    //	cout << "hi";
        cout << "Cannot read input file!";
    }
    return 0;
}

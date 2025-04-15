#include"SortingSystem.h"
#include<iostream>
#include<fstream>
using namespace std;

int main() {
    ifstream fileINT("fileINT.txt");
    ifstream fileDouble("fileDouble.txt");
    ifstream fileString("fileString.txt");
    int n, choice;

    if(!fileINT) cout << "Error while opening the INT file Try again. ";
    if(!fileDouble) cout << "Error while opening the Double file Try again. ";
    if(!fileString) cout << "Error while opening the String file Try again. ";

    cout << "1- Int\n"; cout <<"2- double\n"; cout << "3- string\n";
    cout <<"Enter the type of the data: ";
    cin >> choice;

    
    if(choice == 1){
        fileINT >> n;
        cout << "Data size = " << n  << endl;
        SortingSystem<int> sorter(n);
        sorter.showMenu();
    }
    else if(choice == 2){
        fileDouble >> n;
        cout << "Data size = " << n  << endl;
        SortingSystem<double> sorter(n);
        sorter.showMenu();
    }
    else if(choice == 3){
        fileString >> n;
        cout << "Data size = " << n  << endl;
        SortingSystem<string> sorter(n);
        sorter.showMenu(); 
    }
    else{
        cout <<"Invalid Choice.";
    }
    fileINT.close();
    fileDouble.close();
    fileString.close();
    return 0;
}

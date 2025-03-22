#include"SortingSystem.h"
#include<iostream>
#include<fstream>
using namespace std;

int main() {
    ifstream file("test.txt");
    int n, choice;

    if(!file) cout << "Error while opening the file Try again. ";
    cout << "1- Int\n"; cout <<"2- float\n"; cout << "3- string\n";
    cout <<"Enter the type of the data: ";
    cin >> choice;
    file >> n;
    cout << "Data size = " << n  << endl;
    if(choice == 1){
        SortingSystem<int> sorter(n);
        sorter.showMenu();
    }else if(choice == 2){
        SortingSystem<float> sorter(n);
        sorter.showMenu();
    }
    else if(choice == 3){
        SortingSystem<string> sorter(n);
        sorter.showMenu();
        
    }
    else{
        cout <<"Invalid Choice.";
    }
    file.close();
    return 0;
}

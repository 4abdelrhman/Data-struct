#include"SortingSystem.h"
#include<iostream>
#include<fstream>
using namespace std;

int main() {
    ifstream file("test.txt");
    if(!file) cout << "Error while opening the file Try again. ";
    int n;
    file >> n;
    cout << "Data size = " << n  << endl;
    SortingSystem<int> sorter(n);
    sorter.showMenu();
    file.close();
    return 0;
}

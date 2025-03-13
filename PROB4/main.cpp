#include"SortingSystem.h"
#include<iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    SortingSystem<int> sorter(n);
    sorter.showMenu();
    return 0;
}



//g++ -o sorting main.cpp 
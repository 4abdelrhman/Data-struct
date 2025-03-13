#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

template <typename T>
class SortingSystem {
private:
    T* data;
    int size;
public:
    SortingSystem(int n);//
    ~SortingSystem();//

    void insertionSort();//
    void selectionSort();//
    void bubbleSort();//
    void shellSort();//
    void mergeSort(int left, int right);//
    void quickSort(int left, int right);//
    void countSort();
    void radixSort();
    void bucketSort();

    void merge(int left, int mid, int right);//
    int partition(int low, int high);//

    void displayData();//
    void measureSortTime(void(SortingSystem::*sortFunc)());

    void showMenu();//
};



//Implementation

template <typename T>
SortingSystem<T>::SortingSystem(int n) {
    size = n;
    data = new T[size];
    cout << "Enter " << size << " elements " << endl;
    cin.ignore();
    for (int i = 0; i < size; i++) {
        cout << "Enter data " << i + 1 << ": ";
        cin >> data[i];
    }
}

template<typename T>
SortingSystem<T>::~SortingSystem() {
    delete[] data;
}

template<typename T>
void SortingSystem<T>::displayData() {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if(i < size - 1){
            cout << ", ";
        }
    }
    cout << "]" << endl;
}


// Insertion Sort 
template<typename T>
void SortingSystem<T>::insertionSort() {
    cout << "\nSorting using Insertion Sort...\n";
    cout << "Initial Data: ";
    displayData();

    for (int i = 1; i < size; i++) {
        T key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;

        cout << "Iteration " << i << ": ";
        displayData();
    }

    cout << "Sorted Data: ";
    displayData();
}

// Selection Sort
template<typename T>
void SortingSystem<T>::selectionSort() {
    cout << "\nSorting using Selection Sort...\n";
    cout << "Initial Data: ";
    displayData();

    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (data[j] < data[minIdx]) {
                minIdx = j;
            }
        }
        swap(data[i], data[minIdx]);

        cout << "Iteration " << i + 1 << ": ";
        displayData();
    }

    cout << "Sorted Data: ";
    displayData();
}

// Bubble Sort
template<typename T>
void SortingSystem<T>::bubbleSort() {
    cout << "\nSorting using Bubble Sort...\n";
    cout << "Initial Data: ";
    displayData();

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
            }
        }

        cout << "Iteration " << i + 1 << ": ";
        displayData();
    }

    cout << "Sorted Data: ";
    displayData();
}

// Shell Sort
template<typename T>
void SortingSystem<T>::shellSort() {
    cout << "\nSorting using Shell Sort...\n";
    cout << "Initial Data: ";
    displayData();

    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            T temp = data[i];
            int j;
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }

        cout << "Iteration (gap = " << gap << "): ";
        displayData();
    }

    cout << "Sorted Data: ";
    displayData();
}

// Merge Sort
template<typename T>
void SortingSystem<T>::mergeSort(int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    merge(left, mid, right);

    cout << "After merging [" << left << " - " << right << "]: ";
    displayData();
}


//Merg Sort Helper function
template<typename T>
void SortingSystem<T>::merge(int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    vector<T> leftArr(leftSize);
    vector<T> rightArr(rightSize);

    for (int i = 0; i < leftSize; i++) leftArr[i] = data[left + i];
    for (int j = 0; j < rightSize; j++) rightArr[j] = data[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            data[k++] = leftArr[i++];
        } else {
            data[k++] = rightArr[j++];
        }
    }
    while (i < leftSize) data[k++] = leftArr[i++];
    while (j < rightSize) data[k++] = rightArr[j++];
}

// Quick Sort
template<typename T>
void SortingSystem<T>::quickSort(int left, int right) {
    if (left >= right) return;

    int pivotIndex = partition(left, right);

    cout << "Pivot: " << data[pivotIndex] << " → [";
    for (int i = left; i < pivotIndex; i++) cout << data[i] << (i < pivotIndex - 1 ? ", " : "");
    cout << "] " << data[pivotIndex] << " [";
    for (int i = pivotIndex + 1; i <= right; i++) cout << data[i] << (i < right ? ", " : "");
    cout << "]\n";

    quickSort(left, pivotIndex - 1);
    quickSort(pivotIndex + 1, right);
}


//Quick Sort Helper function
template<typename T>
int SortingSystem<T>::partition(int low, int high) {
    T pivot = data[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (data[j] < pivot) {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

//Count Sort
template<typename T>
void SortingSystem<T>::countSort() {
    cout << "\nSorting using Count Sort...\n";
    cout << "Initial Data: ";
    displayData();

    T maxVal = data[0], minVal = data[0];
    for (int i = 1; i < size; i++) {
        if (data[i] > maxVal) maxVal = data[i];
        if (data[i] < minVal) minVal = data[i];
    }

    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);

    for (int i = 0; i < size; i++) {
        count[data[i] - minVal]++;
    }

    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            data[index++] = i + minVal;
            count[i]--;

            cout << "Iteration (value = " << i + minVal << "): ";
            displayData();
        }
    }

    cout << "Sorted Data: ";
    displayData();
}


//Menu
template <typename T>
void SortingSystem<T>::showMenu() {
    vector<T> oriData(data, data + size); // Store initial data
    int choice;

    do {
        cout << "\nChoose a sorting algorithm:\n";
        cout << "1. Insertion Sort\n";
        cout << "2. Selection Sort\n";
        cout << "3. Bubble Sort\n";
        cout << "4. Shell Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Quick Sort\n";
        cout << "7. Count Sort (Only for integers)\n";
        cout << "8. Radix Sort (Only for integers)\n";
        cout << "9. Bucket Sort\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 6) {
            // Restore original data before sorting
            copy(oriData.begin(), oriData.end(), data);
            
            // Display original data
            cout << "Initial Data: [";
            for (size_t i = 0; i < oriData.size(); i++) {
                cout << oriData[i];
                if (i < oriData.size() - 1) cout << ", "; // Avoid trailing comma
            }
            cout << "]\n";
        }

        switch (choice) {
            case 1:
                insertionSort();
                cout << "\nSorting using Insertion Sort...\n";
                break;
            case 2:
                selectionSort();
                cout<<"\nsorting using Selection Sort...";
                break;
            case 3:
                bubbleSort();
                cout << "\nSorting using Bubble Sort...\n";
                break;
            case 4:
                shellSort();
                cout << "\nSorting using Shell Sort...\n";
                break;
            case 5:
                mergeSort(0, size - 1);
                cout << "\nSorting using Merge Sort...\n";
                break;
            case 6:
                cout << "\nSorting using Quick Sort...\n";
                quickSort(0, size - 1);
                displayData();
                break;
            case 7:
                cout << "\nSorting using Count Sort...\n";
                countSort();
                break;
            case 8:
                cout << "\nSorting using Radix Sort...\n";
                //radixSort();
                break;
            case 9:
                cout << "\nSorting using Bucket Sort...\n";
                //bucketsort();
                break;
            case 10:
                cout << "Exiting program...";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 10);
}



#endif

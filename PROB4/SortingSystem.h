#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H
#include <iostream>
#include<algorithm>
#include <chrono>
#include<fstream>
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
    void measureSortTime(void(SortingSystem::*sortFunc)(int left, int right));


    void showMenu();//
};

//Implementation
template <typename T>
SortingSystem<T>::SortingSystem(int n) {
    ifstream fileINT("fileINT.txt");
    ifstream fileDouble("fileDouble.txt");
    ifstream fileString("fileString.txt");

    if(!fileINT || !fileDouble || !fileString){
        cout << "Error, Couldn't open the file.\n";
        exit(1);
    }
    size = n;
    data = new T[size];
    if constexpr (is_same<T, int>::value){
        fileINT.ignore();
        cout <<"Reading " << size << " data from the file...\n";
        for (int i = 0; i < size; i++) {
            fileINT >> data[i];
        }
        cout << "Data entered: ";
        displayData();
    }else if constexpr(is_same<T, double>::value){
        fileDouble.ignore();
        cout <<"Reading " << size << " data from the file...\n";
        for (int i = 0; i < size; i++) {
            fileDouble >> data[i];
        }
        cout << "Data entered: ";
        displayData();
    }else if constexpr(is_same<T, string>::value){
        fileString.ignore();
        cout <<"Reading " << size << " data from the file...\n";
        for (int i = 0; i < size; i++) {
            fileString >> data[i];
        }
        cout << "Data entered: ";
        displayData();
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

// Measure Sorting Time (No Parameters)
template <typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem::*sortFunc)()) {
    T* originalData = new T[size];
    copy(data, data + size, originalData);

    auto start = chrono::high_resolution_clock::now();
    (this->*sortFunc)();
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Sorting time: " << elapsed.count() << " Sec.\n";

    copy(originalData, originalData + size, data);
    delete[] originalData;
}



// Measure Sorting Time (With Two Parameters)
template <typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem::*sortFunc)(int, int)) {
    T* originalData = new T[size];
    copy(data, data + size, originalData);

    auto start = chrono::high_resolution_clock::now();
    (this->*sortFunc)(0, size - 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Sorting time: " << elapsed.count() << " Sec.\n";

    copy(originalData, originalData + size, data);
    delete[] originalData;
}

// Insertion Sort 
template<typename T>
void SortingSystem<T>::insertionSort() {
    
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
    if(left < right){
        int mid = left + (right - left) / 2;
        mergeSort(left , mid);
        mergeSort(mid + 1, right);
        merge(left, mid , right);
    }
    cout << "Data: ";
    displayData();
}


//Merge Sort Helper function
template<typename T>
void SortingSystem<T>::merge(int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    T* leftArr = new T[leftSize];
    T* rightArr = new T[rightSize];
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

    cout << "Pivot: " << data[pivotIndex] << " -> [";
    for (int i = left; i < pivotIndex; i++) cout << data[i] << (i < pivotIndex - 1 ? ", " : "");
    cout << "] " << data[pivotIndex] << " [";
    for (int i = pivotIndex + 1; i <= right; i++) cout << data[i] << (i < right ? ", " : "");
    cout << "]\n";

    quickSort(left, pivotIndex - 1);
    quickSort(pivotIndex + 1, right);


    if(left == 0 && right == size - 1){
        cout << "Sorted data: ";
        displayData();
    }
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
template<>
void SortingSystem<int>::countSort() {

    if (size == 0) return;

    // Find the maximum and minimum values in the array
    int maxVal = *max_element(data, data + size);
    int minVal = *min_element(data, data + size);

    // Create a count array to store the count of each unique element
    int range = maxVal - minVal + 1;
    int* count = new int[range]();

    // Store the count of each element in the count array
    for (int i = 0; i < size; i++) {
        count[data[i] - minVal]++;
    }

    // Modify the count array to store the cumulative count
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // Create an output array to store the sorted elements
    int* output = new int[size]();

    // Build the output array by placing elements in their correct position
    for (int i = size - 1; i >= 0; i--) {
        output[count[data[i] - minVal] - 1] = data[i];
        count[data[i] - minVal]--;

        cout << "Step " << size - i << ": [";
        for (int j = 0; j < size; j++) {
            if (output[j] != 0 || j < count[data[i] - minVal]) {
                cout << output[j];
            } else {
                cout << "-";    
            }
            if (j < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < size; i++) {
        data[i] = output[i];
    }

    // Free dynamically allocated memory
    delete[] count;
    delete[] output;

    // Display the sorted data
    cout << "Sorted Data: ";
    displayData();
}


// Radix Sort
template<>
void SortingSystem<int>::radixSort() {
    // Find the maximum absolute value to determine the number of digits
    int maxVal = abs(data[0]);
    for (int i = 1; i < size; i++) {
        if (abs(data[i]) > maxVal) {
            maxVal = abs(data[i]);
        }
    }
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        int output[size] = {0};
        int count[10] = {0};
        // Count occurrences of each digit at the current place value (exp)
        for (int i = 0; i < size; i++) {
            int digit = (abs(data[i]) / exp) % 10;
            count[digit]++;
        }
        // Modify count array to store cumulative counts
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        // Build the output array by placing elements in their correct position
        for (int i = size - 1; i >= 0; i--) {
            int digit = (abs(data[i]) / exp) % 10;
            output[count[digit] - 1] = data[i];
            count[digit]--;
        }
        for (int i = 0; i < size; i++) {
            data[i] = output[i];
        }
        cout << "sorting by digit " << exp << ": ";
        displayData();
    }
    cout << "Sorted Data: ";
    displayData();
}



//Bucket Sort
template<typename T>
void SortingSystem<T>::bucketSort() {
    if (size <= 0) return;

    T minVal = data[0], maxVal = data[0];
    for (int i = 1; i < size; i++) {
        if (data[i] < minVal) minVal = data[i];
        if (data[i] > maxVal) maxVal = data[i];
    }
    //Initialize the bucket
    //bucketCount is the number of buckets
    //buckets is the array of buckets
    //bucketSizes is the array of sizes of each bucket
    //bucketCapacities is the array of capacities of each bucket
    int bucketCount = size;
    T** buckets = new T*[bucketCount];
    int* bucketSizes = new int[bucketCount]();
    int* bucketCapacities = new int[bucketCount]();

    for (int i = 0; i < size; i++) {
        int index;
        
        if constexpr (is_arithmetic<T>::value) {
            index = static_cast<int>((bucketCount * (data[i] - minVal)) / (maxVal - minVal + 1));
        }
        //Resize the bucket if it's full
        //copy existing elements to a new bucket
        if (bucketSizes[index] == bucketCapacities[index]) {
            bucketCapacities[index] = bucketCapacities[index] == 0 ? 1 : bucketCapacities[index] * 2;
            T* newBucket = new T[bucketCapacities[index]];
            if (bucketSizes[index] > 0) {
                copy(buckets[index], buckets[index] + bucketSizes[index], newBucket);
                delete[] buckets[index];
            }
            buckets[index] = newBucket;
        }
        buckets[index][bucketSizes[index]++] = data[i];
    }

    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        sort(buckets[i], buckets[i] + bucketSizes[i]);
        for(int j = 0; j < bucketSizes[i];j++){
            data[index++] = buckets[i][j];
            cout << "Inserted Element " << data[index-1] << ": ";
            displayData();
        }
    }
    cout << "Sorted Data: ";
    displayData();

    
    for (int i = 0; i < bucketCount; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
    delete[] bucketCapacities;

}


//Menu
template <typename T>
void SortingSystem<T>::showMenu() {
    // Store initial data
    T* oriData= new T[size]; 
    copy(data, data + size, oriData);
    char repeat;

    do {
        int choice;
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
        cout << "Enter your choice(1-9): ";
        cin >> choice;

        if (choice >= 1 && choice <= 9) {
            // Restore original data before sorting
            copy(oriData, oriData + size, data);
        }

        switch (choice) {
            case 1:
                cout << "\nSorting using Insertion Sort...\n";
                cout <<"Initial data: "; displayData();
                cout << endl;
                measureSortTime(&SortingSystem<T>::insertionSort);
                break;
            case 2:
                cout<<"\nSorting using Selection Sort...\n";
                cout <<"Initial data: "; displayData();
                cout << endl;
                measureSortTime(&SortingSystem<T>::selectionSort);
                break;
            case 3:
                cout << "\nSorting using Bubble Sort...\n";
                cout <<"Initial data: "; displayData();
                cout << endl;
                measureSortTime(&SortingSystem<T>::bubbleSort);
                break;
            case 4:
                cout << "\nSorting using Shell Sort...\n";
                cout <<"Initial data: "; displayData();
                cout << endl;
                measureSortTime(&SortingSystem<T>::shellSort);
                break;
            case 5:
                cout << "\nSorting using Merge Sort...\n";
                cout <<"Initial data: "; displayData();
                cout << endl;
                measureSortTime(&SortingSystem<T>::mergeSort);
                break;
            case 6:
                cout << "\nSorting using Quick Sort...\n";
                cout <<"Initial data: "; displayData();
                cout << endl;
                measureSortTime(&SortingSystem<T>::quickSort);
                break;
            case 7:
                if constexpr (is_same<T, int>::value){
                    cout << "\nSorting using Count Sort...\n";
                    cout <<"Initial data: "; displayData();
                    cout << endl;
                    measureSortTime(&SortingSystem<T>::countSort);
                    break;
                }else{
                    cout <<"Count sort only support INTEGERS!";
                    break;
                }
            case 8:
                if constexpr (is_same<T, int>::value){
                    cout << "\nSorting using Radix Sort...\n";
                    cout <<"Initial data: "; displayData();
                    cout << endl;
                    measureSortTime(&SortingSystem<T>::radixSort);
                    break;
                }else{
                    cout <<"Radix sort only support INTEGERS!";
                    break;
                }
            case 9:
                if constexpr (is_same<T, int>::value || is_same<T,double>::value){
                    cout << "\nSorting using Bucket Sort...\n";
                    cout <<"Initial data: "; displayData();
                    cout << endl;
                    measureSortTime(&SortingSystem<T>::bucketSort);
                    break;
                }else{
                    cout <<"Bucket sort only support INTEGERS or DOUBLE!";
                    break;
                }
            default:
                cout << "Invalid choice! Try again.\n";
        }
        cout << endl;
        cout << "Do you want to use another sorting algorithm? (y/n): ";
        cin >> repeat;
    } while (repeat == 'y' || repeat == 'Y');
    cout << "Thanks for using the Sorting System! Goodbye!\n";
    cout << "Exiting..." << endl;
}


#endif

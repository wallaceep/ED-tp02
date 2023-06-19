#include "Heapsort.hpp"

Heapsort::Heapsort(int _N){
    this->numReg = _N;
}

Heapsort::~Heapsort(){ }

void Heapsort::heapify(Registro *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left].key > arr[largest].key){
        metricas.numComparacoes++;
        largest = left;
        ESCREVEMEMLOG((long int) (&arr[i].key), sizeof(int), 0);
    }
      
    if (right < n && arr[right].key > arr[largest].key){
        metricas.numComparacoes++;
        largest = right;
        ESCREVEMEMLOG((long int) (&arr[i].key), sizeof(int), 0);
    }
      
    if (largest != i) {
      swap(arr[i], arr[largest]);
      metricas.numCopias++;
      heapify(arr, n, largest);
    }
}

void Heapsort::heapSort(Registro *A, int n){
    // Build max heap   
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(A, n, i);
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
      swap(A[0], A[i]);
      metricas.numCopias++;
      // Heapify root element to get highest element at root again
      heapify(A, i, 0);
    }
}

void Heapsort::print(Registro *arr){
    for (int i = 0; i < this->numReg; i++)
        cout << arr[i].key << " ";
    cout << endl;
}
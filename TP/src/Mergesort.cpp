#include "Mergesort.hpp"

Mergesort::Mergesort(int _N){
    this->numReg = _N;
}

Mergesort::~Mergesort(){ }

void Mergesort::merge(Registro *array, int const left, int const mid, int const right){
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
 
    Registro *leftArray = new Registro[subArrayOne],
         *rightArray = new Registro[subArrayTwo];
 
    for (auto i = 0; i < subArrayOne; i++){
        leftArray[i] = array[left + i];
        metricas.numCopias++;
    }
        
    for (auto j = 0; j < subArrayTwo; j++){
        rightArray[j] = array[mid + 1 + j];
        metricas.numCopias++;
    }
 
    auto indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0; 
    int indexOfMergedArray = left; 
 
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].key <= rightArray[indexOfSubArrayTwo].key) {
            metricas.numComparacoes++;
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            ESCREVEMEMLOG((long int) (&array[indexOfMergedArray].key), sizeof(int), 0);
            metricas.numCopias++;
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            metricas.numCopias++;
            ESCREVEMEMLOG((long int) (&array[indexOfMergedArray].key), sizeof(int), 0);  
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        metricas.numCopias++;
        ESCREVEMEMLOG((long int) (&array[indexOfMergedArray].key), sizeof(int), 0);
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        metricas.numCopias++;
        ESCREVEMEMLOG((long int) (&array[indexOfMergedArray].key), sizeof(int), 0);
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void Mergesort::mergeSort(Registro *array, int const begin, int const end){
    if (begin >= end)
        return;
 
    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void Mergesort::print(Registro *reg){
    for (int i = 0; i < this->numReg; i++)
        cout << reg[i].key << " ";
    cout << endl;
}
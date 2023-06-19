#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <iostream>
#include "Registro.hpp"
#include "memlog.h"
#include "Metricas.hpp"

class Heapsort{       
    public:
        int numReg = 0;

        Metricas metricas;
        Heapsort(int _Nx);
        ~Heapsort();
        void heapSort(Registro *registros, int n);
        void AlgHeapSort(Registro *arr, int N);
        void Constroi(Registro *A, int n);
        void heapify(Registro *arr, int n, int i);
        void print(Registro *arr);
};

#endif
#ifndef MERGESORT_H
#define MERGESORT_H

#include <iostream>
#include "Registro.hpp"
#include "Metricas.hpp"
#include "memlog.h"

class Mergesort{       
    public:
        int numReg = 0;

        Metricas metricas;
        Mergesort(int _N);
        ~Mergesort();
        void mergeSort(Registro *array, int const begin, int const end);
        void merge(Registro *array, int const left, int const mid, int const right);
        void algMerge();
        void print(Registro *reg);
};

#endif
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include "Registro.hpp"
#include "Metricas.hpp"
#include "memlog.h"

class Quicksort{       
    public:
        int numReg = 0;
        Metricas metricas;

        // Funções gerais
        Quicksort(int _N);
        ~Quicksort();
        void print(Registro *reg);
        void Particao(int Esq, int Dir, int *i, int *j, Registro *A);

        // Funções para o quicksort recursivo
        void QuickSortRecursivo(Registro *A, int n);
        void Ordena(int Esq, int Dir, Registro *A);

        // Funções para o quicksort mediana
        void ParticaoMediana(int k, int Esq, int Dir, int *i, int *j, Registro *A);
        Registro EscolheMediana(Registro *A, int n, int k);
        void OrdenaMediana(int k, int Esq, int Dir, Registro *A);
        void QuickSortMediana(Registro *A, int k, int n);

        // Funções para o quicksort seleção
        void OrdenaSelecao(Registro *A, int esq, int dir, int k);
        void Selecao(Registro *A, int n);
        void Troca(Registro *A, Registro *B);
        void QuickSortSelecao(Registro *A, int *n, int *m);

        // Funções para o quicksort não recursivo
        void QuickSortNaoRec(Registro* A, int n);
        void QuickSortIterativo(Registro* arr, int h);
        int particao(Registro* arr, int l, int h);
   
        // Funções para o quicksort empilha inteligente
        void QuickSortEmpilhaInteligente(Registro* A, int n);
};

#endif
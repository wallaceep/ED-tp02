#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>

#include "Registro.hpp"
#include "Quicksort.hpp"
#include "Mergesort.hpp"
#include "Heapsort.hpp"
#include "Metricas.hpp"
#include "msgassert.h"
#include "memlog.h"

extern char *optarg;

int main(int argc, char **argv){
  int N, op, versao, seed, k, m, numLinhas;
  std::string input, output="saida.txt", algoritmo;
  char logname[] = "log.out";
  bool log = false;
  Metricas metricas;

  algoritmo = argv[1];

    while ((op = getopt(argc, argv, ":v:s:i:o:k:m:l")) != EOF){
        switch(op){
          case 'v':
            versao = stoi(optarg);
            break;
          case 's':
            seed = stoi(optarg);
            break;
          case 'i':
            input = optarg;
            break;
          case 'o': 
            output = optarg;
            break;
          case 'k': 
            k = stoi(optarg);
            break;
          case 'm': 
            m = stoi(optarg);
            break;
          case 'l':
            iniciaMemLog(logname);
            ativaMemLog();
            log = true;
            break;

          default:
            desativaMemLog();
            exit(1);
      }
    }

  std::ifstream file(input);
  std::ofstream out(output);

  if(!file.is_open() || !out.is_open()) erroAssert(0, "Erro na abertura do arquivo!");

  file >> numLinhas;

  for(int i=0; i<numLinhas; i++){
      file >> N;
      Quicksort *quick = new Quicksort(N);
          
      srand(seed);
      Registro *reg = new Registro[N];

      for(int i=0; i<N; i++){
            int key = rand() % 500;
            Registro *registro = new Registro(key);
            reg[i] = *registro;
      }

    if(algoritmo=="quicksort"){
      switch (versao){
        case 1: // Quicksort recursivo
            quick->QuickSortRecursivo(reg, N);

            out << "Algoritmo: " << algoritmo << " | Tamanho: " << N << " | Tempo: "
            << metricas.tempoProc() << " | NumeroCopias: " << quick->metricas.getNumCopias()
            << " | NumeroComparacoes: " << quick->metricas.getNumComparacoes() << endl;
            // quick->print(reg);
            delete quick;
          break;
        
        case 2: // Quicksort mediana
            if(k <= 0 || k>=N) erroAssert(0, "Valor de k inválido!");

            quick->QuickSortMediana(reg, k, N);

            out << "Algoritmo: " << algoritmo << " | Tamanho: " << N << " | Tempo: "
            << metricas.tempoProc() << " | NumeroCopias: " << quick->metricas.getNumCopias()
            << " | NumeroComparacoes: " << quick->metricas.getNumComparacoes() << endl;
            // quick->print(reg);
            delete quick;
          break;

        case 3: // Quicksort seleção
            if(m <= 0 || m>=N) erroAssert(0, "Valor de m inválido!");

            quick->QuickSortSelecao(reg, &N, &m);

            out << "Algoritmo: " << algoritmo << " | Tamanho: " << N << " | Tempo: "
            << metricas.tempoProc() << " | NumeroCopias: " << quick->metricas.getNumCopias()
            << " | NumeroComparacoes: " << quick->metricas.getNumComparacoes() << endl;
            // quick->print(reg);
            delete quick;
          break;

        case 4: // Quicksort não recursivo
            quick->QuickSortIterativo(reg, N-1);
            // quick->print(reg);
            out << "Algoritmo: " << algoritmo << " | Tamanho: " << N << " | Tempo: "
            << metricas.tempoProc() << " | NumeroCopias: " << quick->metricas.getNumCopias()
            << " | NumeroComparacoes: " << quick->metricas.getNumComparacoes() << endl;
            delete quick;
          break;

        case 5: // Quicksort empilha inteligente
            quick->QuickSortEmpilhaInteligente(reg, N-1);
            // quick->print(reg);
            out << "Algoritmo: " << algoritmo << " | Tamanho: " << N << " | Tempo: "
            << metricas.tempoProc() << " | NumeroCopias: " << quick->metricas.getNumCopias()
            << " | NumeroComparacoes: " << quick->metricas.getNumComparacoes() << endl;
            delete quick;
          break;
      
        default:
          erroAssert(0, "Versão quicksort não disponível!");
          break;
      }
    }

    else if(algoritmo == "mergesort"){
          Mergesort *merge = new Mergesort(N);
          merge->mergeSort(reg, 0, N-1);
          // merge->print(reg);
            out << "Algoritmo: " << algoritmo << " | Tamanho: " << N << " | Tempo: "
            << metricas.tempoProc() << " | NumeroCopias: " << merge->metricas.getNumCopias()
            << " | NumeroComparacoes: " << merge->metricas.getNumComparacoes() << endl;
          delete merge;
    }

    else if(algoritmo == "heapsort"){
            Heapsort *heap = new Heapsort(N);
            heap->heapSort(reg, N);
            // heap->print(reg);
            out << "Algoritmo: " << algoritmo << " | Tamanho: " << N << " | Tempo: "
            << metricas.tempoProc() << " | NumeroCopias: " << heap->metricas.getNumCopias()
            << " | NumeroComparacoes: " << heap->metricas.getNumComparacoes() << endl;
            delete heap;
    } 

    else{
      erroAssert(0, "Algoritmo não disponível!");
    }

    delete[] reg;
}

  file.close();
  out.close();

  if(log)
    finalizaMemLog();

  return EXIT_SUCCESS;
}
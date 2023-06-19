#ifndef METRICAS_H
#define METRICAS_H

#include <iostream>
#include <stdio.h>
#include <sys/resource.h>

class Metricas{       
    public:
        int numComparacoes, numCopias;
        double tempo;
        
        Metricas();
        int getNumComparacoes();
        int getNumCopias();
        double tempoProc();
};

#endif
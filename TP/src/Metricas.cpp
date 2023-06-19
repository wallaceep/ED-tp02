#include "Metricas.hpp"

Metricas::Metricas(){
    this->numComparacoes = 0;
    this->numCopias = 0;
    this->tempo = 0;
}

double Metricas::tempoProc() {
    struct rusage resources;
    int rc;
    double utime, stime, total_time;
/* do some work here */
    if((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");

    utime = (double) resources.ru_utime.tv_sec + 1.e-6 * (double) resources.ru_utime.tv_usec;
    stime = (double) resources.ru_stime.tv_sec + 1.e-6 * (double) resources.ru_stime.tv_usec;
    total_time = utime+stime;

    //printf("Total Time %.3f\n", total_time);
    return total_time;
}

int Metricas::getNumComparacoes(){
    return this->numComparacoes;
}
    
int Metricas::getNumCopias(){
    return this->numCopias;
}
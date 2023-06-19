#include "Quicksort.hpp"

Quicksort::Quicksort(int _N){
    this->numReg = _N;
}

Quicksort::~Quicksort(){ }

/* Particiona o vetor em dois, tomando a mediana como pivô */
void Quicksort::Particao(int Esq, int Dir, int *i, int *j, Registro *A){
    Registro x, w;
    *i = Esq; *j = Dir;
    x = A[(*i + *j)/2]; /* obtem o pivo x */
    metricas.numCopias++;

    do{
        while (x.key > A[*i].key){
           (*i)++; 
           metricas.numComparacoes++;
        } 
        while (x.key < A[*j].key){
            (*j)--;
            metricas.numComparacoes++;
        } 
        if (*i <= *j){
            w = A[*i]; A[*i] = A[*j]; A[*j] = w;
             metricas.numCopias++;
            ESCREVEMEMLOG((long int) (&A[*i].key), sizeof(int),0);
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

/* Imprime o vetor de registros ordenado por chave */
void Quicksort::print(Registro *reg){
    for (int i = 0; i < this->numReg; i++)
        cout << reg[i].key << " ";
    cout << endl;
}
 
/* Ordena recursivamente o vetor de registros */
void Quicksort::Ordena(int Esq, int Dir, Registro *A){
    int i, j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j) Ordena(Esq, j, A);
    if (i < Dir) Ordena(i, Dir, A);
}

/* Chama a função que ordena recursivamente o vetor de registros */
void Quicksort::QuickSortRecursivo(Registro *A, int n){
    Ordena(0, n-1, A);
}

/*----------------------------------------- MEDIANA --------------------------------------------*/

/* Escolhe aleatoriamente k posições do vetor, tira a mediana delas e retorna o pivô */
Registro Quicksort::EscolheMediana(Registro *A, int n, int k){
    //posição no vetor
    int p = 0;
    
    for(int i=0; i<k; i++){
        p += rand()%n;
    }

    return A[p/k];
}

/* Particiona de acordo com a mediana escolhida na função EscolheMediana */
void Quicksort::ParticaoMediana(int k, int Esq, int Dir, int *i, int *j, Registro *A){
    Registro x, w;
    *i = Esq; *j = Dir;
    x = EscolheMediana(A, Dir, k); /* obtem o pivo x */
    metricas.numCopias++;

    do{
        while (x.key > A[*i].key){
            (*i)++;
            metricas.numComparacoes++;
        }
        while (x.key < A[*j].key){
           (*j)--; 
            metricas.numComparacoes++;
        } 
        if (*i <= *j){
            w = A[*i]; A[*i] = A[*j]; A[*j] = w;
            metricas.numCopias++;
            ESCREVEMEMLOG((long int) (&A[*i].key), sizeof(int),0);
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

/* Ordena recursivamente baseado na mediana escolhida de k posições aleatórias */
void Quicksort::OrdenaMediana(int k, int Esq, int Dir, Registro *A){
    int i, j;
    ParticaoMediana(k, Esq, Dir, &i, &j, A);
    if (Esq < j) Ordena(Esq, j, A);
    if (i < Dir) Ordena(i, Dir, A);
}

/* Chama a função de ordenar recursivamente com base na mediana */
void Quicksort::QuickSortMediana(Registro *A, int k, int n){
    OrdenaMediana(k, 0, n-1, A);
}

/*----------------------------------------- SELEÇÃO --------------------------------------------*/

/* Realiza a troca de registros com um registro auxiliar */
void Quicksort::Troca(Registro *A, Registro *B){
    ESCREVEMEMLOG((long int) (&A->key), sizeof(int),0);
    Registro c = *A; 
    *A = *B; 
    *B = c; 
    metricas.numCopias++;
}

/* Ordena por seleção */
void Quicksort::Selecao(Registro *A, int n){
    int i, j, Min;
    for (i = 0; i < n - 1; i++){
        Min = i;
        for (j = i + 1 ; j < n; j++){
            if (A[j].key < A[Min].key){
                Min = j;
                metricas.numComparacoes++;
            }  
        }
        Troca(&A[i], &A[Min]);
    }
}

/* Pariciona e ordena por quicksort, quando a partição for <= m ordena por seleção*/
void Quicksort::OrdenaSelecao(Registro *A, int esq, int dir, int m){
    int i, j;
    Particao(esq, dir, &i, &j, A);
    if(esq <= m)
        Selecao(A, esq);
    if(dir <= m)
        Selecao(A, dir);
    
    if (esq < j) OrdenaSelecao(A, esq, j, m);
    if (i < dir) OrdenaSelecao(A, i, dir, m);
}

/* Chama a função de ordenar por seleção */
void Quicksort::QuickSortSelecao(Registro *A, int *n, int *m){
    OrdenaSelecao(A, 0, *n-1, *m);
}

/*----------------------------------------- NAO RECURSIVO --------------------------------------------*/

/* Versão não recursiva do quicksort */
void Quicksort::QuickSortIterativo(Registro* arr, int h){   
    int l = 0;
    int stack[h - l + 1];
    int top = -1;
    int i, j;

    stack[++top] = l;
    stack[++top] = h;
 
    while (top >= 0) {
        h = stack[top--];
        l = stack[top--];
        
        Particao(l, h, &i, &j, arr);

        if (j > l) {
            stack[++top] = l;
            stack[++top] = i - 1;
        }

        if (i < h) {
            stack[++top] = j + 1;
            stack[++top] = h;
        }
    }
}

/*----------------------------------------- EMPILHA INTELIGENTE ---------------------------------------*/

void Quicksort::QuickSortEmpilhaInteligente(Registro* A, int n){
    int l = 0;
    int stack[n - l + 1];
    int top = -1;
    int i, j;

    stack[++top] = l;
    stack[++top] = n;
 
    while (top >= 0) {
        n = stack[top--];
        l = stack[top--];
        
        Particao(l, n, &i, &j, A);

        if (j > l) {
            stack[++top] = l;
            stack[++top] = i - 1;
        }

        if (i < n) {
            stack[++top] = j + 1;
            stack[++top] = n;
        }
    }
}
#include "Registro.hpp"

Registro::Registro(int _key){
    this->key = _key;
            
    // for(int i=0; i<15; i++) {
    //     if(i<10)
    //         this->numbers[i] = randomNumber();
    //     this->words[i] = randomString();
    // }
}

float Registro::randomNumber() {
    return rand();
}

string Registro::randomString() {
    char letter[200];
            
    for(int i=0; i<200; i++) {
        letter[i] = char(32+rand()%95);
    }
    return letter;
}
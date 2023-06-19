#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>

using namespace std;

class Registro {       
    public:
        int key;
        string words[15]; 
        float numbers[10];
        
        Registro(int _key=0);
        string randomString();
        float randomNumber();        
};

#endif
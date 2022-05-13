//
//  main.cpp
//  Lab03
//
//  Created by Emmanuel Solis on 9/9/20.
//  Carne: B97670.
//  Copyright © 2020 Emmanuel Solis. All rights reserved.
//

#include <iostream>
using namespace std;

void swap(int a, int b); //Ejercicio 1.
unsigned short length(const char*); //Ejercicio 2.a.
unsigned int copy(const char* hilera, char* arreglo, unsigned int size); //Ejercicio 2.b.
int compare(const char* hilera1, const char* hilera2); //Ejercicio 2.c.
int main(int argc, const char * argv[]) {
    //Prueba de Ejercicio 1.
    short valorA = 12;
    short valorB = 14;
    cout<<"Ejercicio 1.\n"<<valorA<<" y "<<valorB<<endl;
    swap(valorA, valorB);
    cout<<valorA<<" y "<<valorB<<endl;
    
    //Prueba de Ejercicio 2.a.
    cout<<"Ejercicio 2.a."<<endl;
    cout<<length("Hola mundo\0")<<endl;
    
    //Prueba de Ejercicio 2.b.
    cout<<"Ejercicio 2.b."<<endl;
    unsigned int diccionarioSize = 256;
    char* diccionario = new char[diccionarioSize];
    for(int i=0; i<diccionarioSize; i++){
        diccionario[i] = 0;
    }
    cout<<"El tamano de la frase es: "<<copy("Me gusta el helado.\0", diccionario, diccionarioSize)<<endl;
    for (int i=0; i<length("Me gusta el helado.\0"); i++) {
        cout<<diccionario[i];
    }
    cout<<endl;
    
    //Prueba de Ejercicio 2.c.
    const char* palabra1 = "Papaya\0";
    const char* palabra2 = "Melon\0";
    cout<<"Ejercicio 2.c.\nComparar dos palabras: "<<palabra1<<" y "<<palabra2<<endl;
    cout<<compare(palabra1, palabra2)<<endl;
    
    //Delete de elementos usados.
    delete [] diccionario; //Usando en el ejercicio 2.b.
    return 0;
}

//Hace un intercambio de los valores de ambas variables a nivel global.
void swap(int a, int b){
    int* valorA = &a; //Encuentro la ubicacion de 'a'.
    int* valorB = &b; //Encuentro la ubicacion de 'b'.
    int temp = 0; //Variable que me ayuda a hacer el intercambio.
    //Hago el intercambio.
    temp = a;
    *valorA = b;
    *valorB = temp;
}

//Encuentra el tamano de una hilera.
unsigned short length(const char* hilera){
    unsigned short size = 0; //Tamano del arreglo.
    do{
        size+=1;
    }while (hilera[size-1]!='\0'); //Dado que las hileras finalizan con un '0'.
    return size-1;
}

//Copia un texto dentro de otro arreglo.
unsigned int copy(const char* hilera, char* arreglo, unsigned int size){
    unsigned int i = 0; //Auxiliar que me permite contar por donde voy.
    unsigned int hileraSize = length(hilera);
    //Copio la hilera en el arreglo.
    do{
        arreglo[i] = hilera[i];
        i+=1;
    }while(i<hileraSize && i<size);
    return hileraSize;
}

//Compara dos hileras para ver si son iguales o como se comportan.
int compare(const char* hilera1, const char* hilera2){
    int sizeHilera1 = length(hilera1);
    int sizeHilera2 = length(hilera2);
    int valor = 0; //Es el valor a retornar una vez que se han comparado las hileras; este puede ser negativo, positivo, o cero.
    //Donde hilera1 es mas grande que hilera2.
    cout<<"Sus tamanos son: "<<sizeHilera1<<" y "<<sizeHilera2<<endl;
    if(sizeHilera1>sizeHilera2){
        for(int i=0; i<sizeHilera1; i++){
            //En caso que pudiera salirme del array.
            if(i>=sizeHilera2){
                valor += hilera1[i];
            } else {
                valor += hilera1[i] - hilera2[i];
            }
        }
    } else if (sizeHilera1<sizeHilera2){ //Donde hilera2 es mas grande que hilera1.
        for(int i=0; i<sizeHilera2; i++){
            //En caso que pudiera salirme del array.
            if(i>=sizeHilera1){
                valor -= hilera2[i];
            } else {
                valor -= hilera1[i] - hilera2[i];
            }
        }
    } else if (sizeHilera1==sizeHilera2){ //Donde ambas hileras son del mismo tamano.
        for (int i=0; i<sizeHilera1; i++) {
            valor += hilera1[i] - hilera2[i];
        }
    }
    return valor;
}

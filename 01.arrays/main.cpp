//  main.cpp
//  Lab01
//
//  Created by Emmanuel Solis on 8/20/20.
//  Copyright © 2020 Emmanuel Solis. All rights reserved.
#include <iostream> //Biblioteca de Entrada y Salida de datos.
#include <cstdlib> //Para generar numero aleatorios.
#include <time.h>
using namespace std;

int* primos(int array[], int size); //Ej 1.
int* fibo(int array[], int size); //Ej 2.
int* sortArray(int array[], int size); //Ej 3.
int nFibo(int n=1); //Funcion para averiguar cualquier numero Fibonacci.
int* randomArray(int array[], int n); //Crea un array con numero aleatorios [0,100].
void printArray(int array[], int size); //Imprime cualquier arreglo.

int main(int argc, const char * argv[]) {
    srand(time(0));
    unsigned short sizePrimos = 0;
    unsigned short sizeFibo = 0;
    unsigned short sizeSort = 0;
    
    cout<<"Ingrese el size del arreglo de numeros primos."<<endl;
    cin>>sizePrimos;
    int* arrayPrimos = new int[sizePrimos];
    printArray(primos(arrayPrimos, sizePrimos), sizePrimos);
    cout<<"\nIngrese el size del arreglo de numeros fibonacci."<<endl;
    cin>>sizeFibo;
    int* arrayFibo = new int[sizeFibo];
    printArray(fibo(arrayFibo, sizePrimos), sizePrimos);
    cout<<"\nIngrese el size del arreglo de numeros a ordenar."<<endl;
    cin>>sizeSort;
    int* arrayRandom = new int[sizeSort];
    printArray(sortArray(randomArray(arrayRandom, sizeSort), sizeSort), sizeSort);
    
    
    //Borro los valores por referencia.
    delete [] arrayPrimos;
    delete [] arrayFibo;
    delete [] arrayRandom;
    return 0;
}

int* primos(int array[], int size){
    int indice = 0;
    for (int nPrimo=1; indice<size; nPrimo++) {
        //Exepciones para los primeros numeros primos [1,9].
        if(nPrimo==2 || nPrimo==3 || nPrimo==5 || nPrimo==7){
            array[indice] = nPrimo;
            indice++;
        }
        //Comprobacion para numeros>9.
        if(nPrimo>9 && nPrimo%2!=0 && nPrimo%3!=0 && nPrimo%5!=0){
            array[indice] = nPrimo;
            indice++;
        }
    }
    return array;
}

int nFibo(int n){
    if(n==0){
        return 0;
    } else {
        if(n==1){
            return 1;
        } else{
            return nFibo(n-1)+nFibo(n-2);
        }
    }
}

int* fibo(int array[], int size){
    for(int i=0; i<size; i++){
        array[i] = nFibo(i);
    }
    return array;
}

int* sortArray(int array[], int size){
    int j=0;
    for(int i=1; i<size; i++){ //Para analizar cada posicion del array.
        j=1; //Uso de auxiliar.
        while(j<size){ //Para moverse por todo el array al ordenar posiciones.
            if(array[j-1]>array[j]){
                int temp = array[j-1];
                array[j-1] = array[j];
                array[j] = temp;
            }
            j++;
        }
    }
    return array;
}

int* randomArray(int array[], int n){
    unsigned short x = 0;
    for(int i=0; i<n; i++){
        x = (rand() % 101);
        array[i] = x;
    }
    return array;
}

void printArray(int* arreglo, int n){
    cout<<"[";
    for(int i=0; i<n-1; i++){
        cout<<arreglo[i]<<", ";
    }
    cout<<arreglo[n-1]<<"]";
}

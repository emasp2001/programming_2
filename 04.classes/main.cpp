//
//  main.cpp
//  Lab04
//
//  Created by Emmanuel Solis on 9/16/20.
//  Copyright © 2020 Emmanuel Solis. All rights reserved.
//

#include <iostream>
using namespace std;

class Primos{

public:
    static int *primo; //Arary de numeros primos.
    static int size; //Size del array.
    
    static int *getPrimo(){return primo;} //Se hace para obtener por referencia el arreglo de primos.
    static int getSize(){return size;}
    static void setSize(int sizeN){size = sizeN;}
    
    //Metodo para saber si un numero es primo o no.
    static bool esPrimo(unsigned int numero){
        bool serPrimo = true;
        //Si cumple con alguna de estas caracteristicas NO es primo.
        if(numero!=2 && numero!=3 && numero!=5 && numero!=7){
            if(numero%2==0 || numero%3==0 || numero%5==0){ //Significa que es divisible por otro numero.
                serPrimo = false;
            }
        }
        return serPrimo;
    }
    
    //Me permite llenar por referencia un array de size n con numeros primos.
    static int* llenarArray(int *array, int size){
        int numero = 2; //Numero con el que deseo llenarlo.
        int i = 0; //Indice que me ayuda a moverme en el array.
        array = new int[size]; //Sobreescribo el array.
        do {
            if(esPrimo(numero)==true){
                array[i]=numero; //Solo se pone si es primo.
                i+=1; //Para moverme a otra posicion.
            }
            numero+=1; //Siempre debo cambiar el numero.
        } while (i<size); //Hasta que llegue al final del arreglo.
        return array;
    }
    
    //Metodo que me permite calcular n numeros primos, solo si es un numero mayor del ya existente.
    static void cargar(int cantidadN){
        if(cantidadN>0){
            if(cantidadN>size){ //En caso de ser mas grande debo crear uno nuevo.
                primo = llenarArray(primo, cantidadN);
            }
            size = cantidadN;
        }
    }
    
    //Me imprime un array de enteros cualquiera.
    static void printArray(int* array, int size){
        for(int i=0; i<size; i++){
            cout<<array[i]<<", ";
        }
        cout<<endl;
    }
    
    //Obtiene el i-esimo numero primo.
    static int getPrime(unsigned int n){
        if(n>0){ //Cuido que no se me caiga el codigo.
            int* arreglo = new int[n];
            arreglo = llenarArray(arreglo, n); //Esto lo hago para averiguar dicho numero.
            return arreglo[n-1];
        } else {
            return 0;
        }
    }
    
};

class Compuesto{
private:
    long long int numero; //Se refiere al numero original que se va a solicitar descomponer.
    int cantidadFactores; //La cantidad de factores en que se tuvo que descomponer un numero, resulta ser la misma cantidad de exponentes.
    int *factores; //Vector donde voy a almacenar los factores primos en que se descompone un numero.
    int *exponentes; //Vector donde voy a almacenar los exponentes de los factores primos.
    
public:
    long long int getNumero(){return numero;}
    int *getFactores(){return factores;}
    int *getExponentes(){return exponentes;}
    
    //Constructor, debe descomponer el numero en sus primos y exponentes respectivos. Considerando que pueden ser numeros negativos, positivos, +-1 (no tiene factores primos), y 0.
    Compuesto(long long int number){
        this->numero = number; //Guardo el numero original.
        //Algoritmo en casos donde no son +-1 ni 0.
        if(number!=1 && number!=-1 && number!=0){
            long long int numeroDividido = number;
            int indicePrimo = 1; //Indice para saber que primo voy a necesitar
            int numeroPrimo = Primos::getPrime(indicePrimo); //Los numeros primos por los cuales los voy a dividir.
            int *factor = new int[20]; //Donde almaceno los facotres de forma momentanea.
            int indiceFactores = 0; //Para moverme en factor.
            int *exponente = new int[20];
            do {
                if(numeroDividido%numeroPrimo==0){
                    while(numeroDividido%numeroPrimo==0){
                        numeroDividido /= numeroPrimo;
                        factor[indiceFactores] = numeroPrimo;
                        exponente[indiceFactores] += 1;
                    }
                    indiceFactores += 1;
                } else {
                    indicePrimo+=1;
                    numeroPrimo = Primos::getPrime(indicePrimo);
                }
            } while (numeroDividido>1 || numeroDividido<-1);
            //Guardo la cantidad de factores y exponentes que use.
            this->cantidadFactores = indiceFactores;
            //Creo los factores y exponentes con el tamano que deben ser.
            factores = new int[cantidadFactores];
            exponentes = new int[cantidadFactores];
            //Necesito pasarlos a los vectores globales para exponentes y factores.
            for(int i=0; i<cantidadFactores; i++){
                factores[i] = factor[i];
                exponentes[i] = exponente[i];
            }
            //En caso de que el numero original fuese negativo.
            if(number<0){factores[0]*=-1;}
        } else { //Algoritmo en casos donde son +-1 o 0.
            cantidadFactores = 1;
            factores = new int[cantidadFactores];
            exponentes = new int[cantidadFactores];
            switch (number) {
                case 0:
                    factores[0]=0;
                    exponentes[0]=1;
                    break;
                case 1:
                    factores[0]=1;
                    exponentes[0]=1;
                    break;
                case -1:
                    factores[0]=-1;
                    exponentes[0]=1;
                    break;
                default:
                    break;
            }
        }
    }
    
    //Se encarga de imprimir el numero compuesto en su forma factor1^exponente1 * factor2^exponente2...
    void print(){
        cout<<"El numero "<<numero<<" se representa de la siguiente forma:"<<endl;
        cout<<numero<<" = ";
        //En caso donde solo este compuesto por un factor y un exponente.
        if(cantidadFactores==1){
            cout<<factores[0]<<"^"<<exponentes[0]<<endl;
        } else { //En caso donde este compuesto por mas de un factor y exponente.
            for(int i=0; i<cantidadFactores-1; i++){
                cout<<factores[i]<<"^"<<exponentes[i]<<" * ";
            }
            cout<<factores[cantidadFactores-1]<<"^"<<exponentes[cantidadFactores-1]<<endl; //Hago esto para que quede bien escrito.
        }
    }
};


int* Primos::primo = 0;
int Primos::size = 0;

int main(int argc, const char * argv[]) {
    //Ejercicio 1.a, 1.b, 1.c.
    cout<<"Ejercicios 1.a, 1.b, 1.c.\nAlmacenar 15 numeros primos."<<endl;
    Primos::cargar(15);
    Primos::printArray(Primos::getPrimo(), 15);
    
    //Ejercicio 1.d.
    cout<<"Ejercicio 1.d.\nObtener un n-esimo numero primo y la cantidad de numeros primos que cree."<<endl;
    cout<<"El size del array es: "<<Primos::getSize()<<endl;
    cout<<"El i-esimo primo 50 es: "<<Primos::getPrime(50)<<endl;
    
    //Ejercicio 2.
    cout<<"Ejercicios [2.a, 2.e]. Construir la clase con lo solicitado en el constructor."<<endl;
    Compuesto *obj1 = new Compuesto(988696);
    cout<<"Ejercicios 2.f.\nImprimir el compuesto en dicho formato."<<endl;
    obj1->print();
    
    //Borro las referencias que habia creado.
    delete [] obj1->getFactores();
    delete [] obj1->getExponentes();
    delete obj1;
    return 0;
}


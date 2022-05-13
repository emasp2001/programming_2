//
//  lista.cpp
//  Lab05
//
//  Created by Emmanuel Solis on 9/25/20.
/*
 Clase Lista
 ATRIBUTOS:
    cabeza
    cola
    tamano
 METODOS:
    constructor()
    ~destructor()
    push()
    pop()
    imprimir()
 */

#include <stdio.h>
#include "nodo.cpp"
#include <iostream>
using namespace std;

class Lista{
private:
    //Nodo *cabeza; //Nodo cabeza principal.
    int size; //Tamano de la lista.
    void insertar(const char *data, int prioridad); //Metodo privado que se encarga de acomodar un nuevo nodo en un lugar especifico, tomando en cuenta la prioridad de los nodos.
public:
    Nodo *cabeza; //Nodo cabeza principal.
    Lista(){ //Solo construye una lista sin necesidad de almacenar nada en ella.
        this->cabeza = 0;
        this->size = 0;
    }
    //Obtengo el tamano de la lista.
    unsigned int getSize(){return size;}
    //Agregar un nodo a la lista en la ultima posicion si no hay problemas de prioridad pero en caso de haberlas debe posicionarlo de forma correcta.
    void push(const char* data, int priority){
        //Es decir en caso que la lista este vacia.
        if(cabeza==0){
            cabeza = new Nodo(data, priority); //Agrego el primer elemento de la lista.
            cabeza->setNodoSiguiente(0); //El siguiente estaria vacio.
            cabeza->setNodoAnterior(0); //De igual forma el anterior.
        } else {
            //En caso que solo exista la cabeza.
            if(cabeza->getNodoSiguiente()==0){
                //Se da en caso que el nuevo tenga menos prioridad que la cabeza.
                if(cabeza->getPrioridad()<=priority){
                    cabeza->setNodoSiguiente(new Nodo(data, priority));
                    (cabeza->getNodoSiguiente())->setNodoAnterior(cabeza); //Le enlazo que la cabeza es el anterior.
                } else{ //Solo en caso que el nuevo tenga mas prioridad que la cabeza.
                    //Hago el intercambio.
                    Nodo *temp = cabeza;
                    cabeza = new Nodo(data, priority);
                    cabeza->setNodoSiguiente(temp);
                }
            } else{ //En caso de que la lista este compuesta por mas de 1 elemento se pasa al algoritmo insertar().
                
            }
        }
        size++; //Aumento el tamano de la lista.
    }
    //Metodo privado que se encarga de acomodar un nuevo nodo en un lugar especifico, tomando en cuenta la prioridad de los nodos.
    void insertar(const char *data, int priority, Nodo *actual){
        if(actual->getPrioridad()>priority){ //Si aun el nuevo tiene mas prioridad.
            if(actual->getNodoAnterior() == 0){ //Osea que estoy en la cabeza y aun debo acomodarlo.
                actual->setNodoAnterior(new Nodo(data, priority));
                actual->setNodoSiguiente(cabeza);
                cabeza = actual->getNodoAnterior();
            } else{ //En caso que no estoy en la cabeza y sigue siendo menor.
                insertar(data, priority, actual->getNodoAnterior()); //Hago una recursion hasta hallar el que corresponde.
            }
        } else{ //Una vez que ya halle el nodo al que debo enlazarlo.
            //Acomodo el nuevo nodo.
            Nodo *temp = actual->getNodoSiguiente();
            actual->setNodoSiguiente(new Nodo(data, priority));
            (actual->getNodoSiguiente())->setNodoSiguiente(temp); //Enlazo su referencia del que ya existia.
            (actual->getNodoSiguiente())->setNodoAnterior(actual);
        }
    }
    //Metodo pop que retorna el ultimo elemento y lo quita de la lista. Es un metodo recursivo que busca el ultimo desde la cabeza.
    const char *pop(Nodo *actual){
        const char *data;
        if(actual->getNodoSiguiente()==0){
            data = actual->getDato();
        } else {
            data = pop(actual->getNodoSiguiente());
        }
        delete [] actual;
        return data;
    }
    //Metodo para imprimir toda la lista.
    void print(Nodo *actual){
        if(actual->getNodoSiguiente()==0){
            cout<<"Fin de la lista"<<endl;
        } else {
            cout<<actual->getDato()<<endl;
        }
    }
};

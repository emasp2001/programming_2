//
//  nodo.cpp
//  Lab05
//  Created by Emmanuel Solis on 9/25/20.
/*
 Aqui pongo la clase Nodo.
 ATRIBUTOS:
    dato
    prioridad
    nodoSiguiente
    nodoAnterior
 METODOS:
    constructor(dato, prioridad)
    setNodoSiguiente(nodo)
    getDato()
    getPrioridad()
    getNodoAnterior()
    getNodoSiguiente()
 */

#include <stdio.h>

class Nodo{
private:
    const char *dato; //Nombre almacenar.
    int prioridad;
    Nodo *nodoSiguiente; //Por referencia se refiere al siguiente Nodo enlazado.
    Nodo *nodoAnterior; //Por referencia se refiere al anterior Nodo enlazado.
    
public:
    Nodo(const char *data, int priority){ //Constructor.
        this->dato = data;
        this->prioridad = priority;
        this->nodoAnterior = 0; //La referencia es nula a menos que se indique lo contrario con los demas metodos.
        this->nodoSiguiente = 0; //La referencia es nula a menos que se indique lo contrario con los demas metodos.
    }
    void setNodoSiguiente(Nodo *node){ this->nodoSiguiente = node; }
    void setNodoAnterior(Nodo *node){ this->nodoAnterior = node; }
    const char *getDato(){ return dato; }
    int getPrioridad(){ return prioridad; }
    Nodo *getNodoSiguiente(){ return nodoSiguiente; }
    Nodo *getNodoAnterior(){ return nodoAnterior; }
};

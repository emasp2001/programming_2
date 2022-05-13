//
//  LinearDataStructure.hpp
//  Lab07
//
//  Created by Emmanuel Solis on 11/20/20.
//

#ifndef LinearDataStructure_hpp
#define LinearDataStructure_hpp

#include <stdio.h>

template <class datos>
class LinearDataStructure {
    
public:
    //ATRIBUTOS
    int stock; //Numero que almacena la cantidad de objetos almacenados.
    
    //METODOS
    void setStock(int number);
    int getStock();
    virtual void push()=0; //Agrega un valor a la lista.
    virtual datos *pop()=0; //Retorna un elemento de la lista, a la vez que lo elimina.
};


#endif /* LinearDataStructure_hpp */

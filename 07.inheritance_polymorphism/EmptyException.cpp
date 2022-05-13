//
//  EmptyException.cpp
//  Lab07
//
//  Created by Emmanuel Solis on 11/21/20.
//

#include <stdio.h>
#include <exception>
using namespace::std;

class EmptyException : public exception {
public:
    const char *what () const throw (){
        return "Elemento de la lista/fila NO EXISTE.";
    }
};

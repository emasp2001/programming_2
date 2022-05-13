//
//  main.cpp
//  Lab05
//
//  Created by Emmanuel Solis on 9/25/20.
//

#include <iostream>
#include "lista.cpp"

int main(int argc, const char * argv[]) {
    Lista *lista = new Lista();
    lista->push("Pedro", 1);
    lista->push("Emmanuel", 3);
    lista->push("Majo", 2);
    std::cout<<lista->pop(lista->cabeza)<<endl;
    lista->push("Nacho", 3);
    lista->push("Fer", 7);
    std::cout<<"El size de la lista es "<<lista->getSize()<<endl;
    
    return 0;
}

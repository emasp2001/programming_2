//
//  LinearDataStructure.cpp
//  Lab07
//
//  Created by Emmanuel Solis on 11/20/20.
//

#include "LinearDataStructure.hpp"

template<> void LinearDataStructure<class datos>::setStock(int number){this->stock=number;}

template<> int LinearDataStructure<class datos>::getStock(){return stock;}

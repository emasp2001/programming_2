//
//  GeneticAlgorithm.cpp
//  HW02
//
//  Created by Emmanuel Solis on 11/4/20.
//

#include <stdio.h>
#include "GeneticAlgorithm.h"

//CONSTRUCTOR
GeneticAlgorithm::GeneticAlgorithm(int populationSize,float elitismRatio, float mutationRatio, float sporadicRatio){
    this->populationSize = populationSize;
    this->elitismRatio = elitismRatio;
    this->mutationRatio = mutationRatio;
    this->sporadicRatio = sporadicRatio;
}

//DESTRUCTOR
GeneticAlgorithm::~GeneticAlgorithm(){};

//Retornar el numero de la epoca actual.
unsigned int GeneticAlgorithm::getEpoch(){return currentEpoch;}

//Reinicia el algoritmo genético, regresando a la primera época y modificando los parámetros del algoritmo.
void GeneticAlgorithm::reset(int populationSize,float elitismRatio,float mutationRatio,float sporadicRatio){
    currentEpoch = 1;
    populationSize = populationSize;
    elitismRatio = elitismRatio;
    mutationRatio = mutationRatio;
    sporadicRatio = sporadicRatio;
}

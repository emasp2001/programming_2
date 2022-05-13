//
//  main.cpp
//  Lab02
//
//  Created by Emmanuel Solis on 8/31/20.
//  Carne: B97670.
//  Copyright © 2020 Emmanuel Solis. All rights reserved.
//

#include <iostream>
#include <cstdlib> //Para generar numero aleatorios.
#include <time.h>
#include <cmath> //Para operaciones matamaticas.
#include "Bitmap.cpp" //Codigo del profe.
using namespace std;

int** nCompuestos(int** matriz, int nFilas, int nColumnas); //Ejercicio 1.
int** lifeGame(int** matriz, int nFilas, int nColumnas); //Ejercicio 2.
unsigned char*** codificador(unsigned char*** matriz, int nFilas, int nColumans); //Ejercicio 3.
void printMatriz(int** matriz, int nFilas, int nColumnas); //Metodo privado para imprimir una matriz.

int main(int argc, const char * argv[]) {
    srand(time(0));
    //Primer Ejercicio.
    int** matrizEj1 = new int*[3];
    for(int i; i<3; i++){
        matrizEj1[i] = new int [4];
    }
    cout<<"Primer Ejercicio."<<endl;
    printMatriz(nCompuestos(matrizEj1, 3, 4), 3, 4);
    cout<<"\n"<<endl;
    
    //Segundo Ejercicio.
    int** matrizEj2 = new int*[12];
    for(int i=0; i<12; i++){
        matrizEj2[i] = new int[20];
    }
    for(int i=0; i<12; i++){
        for(int j=0; j<20; j++){
            matrizEj2[i][j] = (rand() % 2);
        }
    }
    cout<<"Segundo Ejercicio."<<endl;
    printMatriz(lifeGame(matrizEj2, 12, 20), 12, 20);
    
    //Tercer Ejercicio.
    int ancho = 1000;
    int largo = 1000;
    unsigned char*** imagen = new unsigned char**[ancho]; //Inicializo las filas.
    for(int i=0; i<ancho; i++){
        imagen[i] = new unsigned char*[largo]; //Inicializo las columnas.
    }
    for(int i=0; i<ancho; i++){
        for(int j=0; j<largo; j++){
            imagen[i][j] = new unsigned char[3]; //Inicializo el vector donde van los valores de colores.
        }
    }
    cout<<"\nTercer Ejercicio.\nSe creo usando el codigo del profesor que crea imagenes."<<endl;
    Bitmap::save_24bitmap("radial.bmp", codificador(imagen, ancho, largo), largo, ancho); //Creo la imagen usando codigo del profesor.
    
    //Delete de los punteros.
    //Puntero del Primer Ejercicio.
    for(int i; i<3; i++){
        delete[] matrizEj1[i];
    }
    delete[] matrizEj1;
    //Puntero del Segundo Ejercicio.
    for(int i=0; i<12; i++){
        delete[] matrizEj2[i];
    }
    delete[] matrizEj2;
    //Puntero del Tercer Ejercicio.
    for(int i=0; i<ancho; i++){
        for (int j=0; j<largo; j++){
            delete[] imagen[i][j];
        }
    }
    for(int i=0; i<ancho; i++){
        delete[] imagen[i];
    }
    delete[] imagen;
    return 0;
}

int** nCompuestos(int** matriz, int nFilas, int nColumnas){
    //Llenar matriz con numeros normales.
    int auxiliar=1; //Auxiliar para llenar con numeros normales.
    for(int i=0; i<nFilas; i++){
        for(int j=0; j<nColumnas; j++){
            matriz[i][j]=auxiliar;
            auxiliar++;
        }
    }
    //Cambiar por 0 y 1. Si es compuesto 0, si es primo 1.
    for(int i=0; i<nFilas; i++){
        for(int j=0; j<nColumnas; j++){
            if(matriz[i][j]==2 || matriz[i][j]==3 || matriz[i][j]==5 || matriz[i][j]==7){ //Compruebo que no sea uno de los primeros numeros primos.
                matriz[i][j] = 1;
            } else{
                if(matriz[i][j]%2!=0 && matriz[i][j]%3!=0 && matriz[i][j]%5!=0 && matriz[i][j]!=1){ //Comprueba si es un numero primo o compuesto.
                    matriz[i][j]=1;
                } else {
                    matriz[i][j]=0;
                }
            }
        }
    }
    return matriz;
}

int** lifeGame(int** matriz, int nFilas, int nColumnas){
    //Revisar toda la matriz
    for(int i=0; i<nFilas; i++){
        for(int j=0; j<nColumnas; j++){
            unsigned short celulasVivas = 0; //Contador de celulas vivas al lado de una celda.
            //Algoritmo para contar las 8 celdas alrededor.
            short coordenadaX = 0; //Coordenada para saber donde debo buscar el valor.
            short coordenadaY = 0; //Coordenada para saber donde debo buscar el valor.
            //Ver celda ARRIBA.
            coordenadaX = i-1;
            coordenadaY = j;
            if(coordenadaX<0){coordenadaX = nFilas-1;}
            if(matriz[coordenadaX][coordenadaY]==1){celulasVivas+=1;}
            //Ver celda DERECHA.
            coordenadaX = i;
            coordenadaY = j+1;
            if(coordenadaY>=nColumnas){coordenadaY = 0;}
            if(matriz[coordenadaX][coordenadaY]==1){celulasVivas+=1;}
            //Ver celda ABAJO.
            coordenadaX = i+1;
            coordenadaY = j;
            if(coordenadaX>=nFilas){coordenadaX = 0;}
            if(matriz[coordenadaX][coordenadaY]==1){celulasVivas+=1;}
            //Ver celda IZQUIERDA.
            coordenadaX = i;
            coordenadaY = j-1;
            if(coordenadaY<0){coordenadaY = nColumnas-1;}
            if(matriz[coordenadaX][coordenadaY]==1){celulasVivas+=1;}
            //Ver celda NORESTE.
            coordenadaX = i-1;
            coordenadaY = j+1;
            if(coordenadaX<0 && coordenadaY>=nColumnas){ //Si se sale por ambos lados
                coordenadaX = nFilas - 1;
                coordenadaY = 0;
            } else {
                if(coordenadaX<0 && coordenadaY<nColumnas){ //Si se sale solo por arriba.
                    coordenadaX=nFilas-1;
                } else{ //Si se sale solo por la derecha.
                    if(coordenadaX>=0 && coordenadaY>=nColumnas){coordenadaY = 0;}
                }
            }
            if(matriz[coordenadaX][coordenadaY]==1){celulasVivas+=1;}
            //Ver celda SURESTE.
            coordenadaX = i+1;
            coordenadaY = j+1;
            if(coordenadaX>=nFilas && coordenadaY>=nColumnas){ //Si se sale por ambos lados
                coordenadaX = 0;
                coordenadaY = 0;
            } else {
                if(coordenadaX>=nFilas && coordenadaY<nColumnas){ //Si se sale solo por abajo.
                    coordenadaX=0;
                } else{ //Si se sale solo por la derecha.
                    if(coordenadaX<nFilas && coordenadaY>=nColumnas){coordenadaY = 0;}
                }
            }
            if(matriz[coordenadaX][coordenadaY]==1){celulasVivas+=1;}
            //Ver celda SUROESTE.
            coordenadaX = i+1;
            coordenadaY = j-1;
            if(coordenadaX>=nFilas && coordenadaY<0){ //Si se sale por ambos lados
                coordenadaX = 0;
                coordenadaY = nColumnas-1;
            } else {
                if(coordenadaX>=nFilas && coordenadaY>=0){ //Si se sale solo por abajo.
                    coordenadaX=0;
                } else{ //Si se sale solo por la izquierda.
                    if(coordenadaX<nFilas && coordenadaY<0){coordenadaY = nColumnas-1;}
                }
            }
            if(matriz[coordenadaX][coordenadaY]==1){celulasVivas+=1;}
            //Ver celda NOROESTE.
            coordenadaX = i-1;
            coordenadaY = j-1;
            if(coordenadaX<0 && coordenadaY<0){ //Si se sale por ambos lados
                coordenadaX = nFilas-1;
                coordenadaY = nColumnas-1;
            } else {
                if(coordenadaX<0 && coordenadaY>=0){ //Si se sale solo por arriba.
                    coordenadaX=nFilas-1;
                } else{ //Si se sale solo por la izquierda.
                    if(coordenadaX>=0 && coordenadaY<0){coordenadaY = nColumnas-1;}
                }
            }
            if(matriz[coordenadaX][coordenadaY]==1){celulasVivas+=1;}
            //Una vez que tengo la cantidad de celulas que hay, tomo decisiones en base a eso.
            if(matriz[i][j]==0 && celulasVivas==3){ //En caso que este muerta y rodeada por 3 celulas vivas.
                matriz[i][j]=1; //Ahora esta viva por reproduccion.
            } else {
                if(matriz[i][j]==1 && celulasVivas>3){ //En caso que este viva y rodeada por mas de 3 celulas vivas.
                    matriz[i][j]=0; //Muere por sobrepoblacion.
                } else{
                    if(matriz[i][j]==1 && celulasVivas<2){ //En caso que este viva y rodeada por menos de 2 celulas vivas.
                        matriz[i][j]=0; //Muere por soledad.
                    }
                }
            }
        }
    }
    return matriz;
}

unsigned char*** codificador(unsigned char*** matriz, int nFilas, int nColumnas){
    unsigned char colorR = (rand() % 256);
    unsigned char colorG = (rand() % 256);
    unsigned char colorB = (rand() % 256);
    int xCentro = nFilas/2; //Coordenada X del centro.
    int yCentro = nColumnas/2; //Coordenada Y del centro.
    float distanciaDiagonal = sqrt((0-(nFilas-1)*(0-(nFilas-1)))+(0-(nColumnas-1)*(0-(nColumnas-1)))); //Formula para calcular la distancia de la diagonal.
    //Pintar la imagen.
    for(int i=0; i<nFilas; i++){ //Me muevo por el ancho de la imagen.
        for(int j=0; j<nColumnas; j++){ //Me muevo por el largo de la imagen.
            float distanciaPunto = sqrt((xCentro-i)*(xCentro-i)+(yCentro-j)*(yCentro-j)); //Formula de la distancia entre los puntos.
            float valorMultiplicar = 1 - (distanciaPunto*2/distanciaDiagonal); //Valor por el cual debo multiplicar entre el color para obtener la degradacion.
            matriz[i][j][0] = colorR*valorMultiplicar; //Degradacion en R.
            matriz[i][j][1] = colorG*valorMultiplicar; //Degradacion en G.
            matriz[i][j][2] = colorB*valorMultiplicar; //Degradacion en B.
        }
    }
    return matriz;
}

void printMatriz(int** matriz, int nFilas, int nColumnas){
    for(int i=0; i<nFilas; i++){
        cout<<"\n"<<endl;
        for(int j=0; j<nColumnas; j++){
            cout<<matriz[i][j]<<", ";
        }
    }
}

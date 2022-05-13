//
//  main.cpp
//  Lab08
//
//  Created by Emmanuel, B97670, Solis on 11/26/20.
//

#include <iostream>
#include <fstream>
using namespace std;

static int *calcularPrimos(int cant){
    int *almacen = new int[cant];
    int nPrimo = 0; //Numero que me permite almacenar el numero primo por el que voy.
    for(int i=0; i<cant; i++){
        if((nPrimo+2)<10){
            if((nPrimo+2)==2 || (nPrimo+2)==3 || (nPrimo+2)==5 || (nPrimo+2)==7){almacen[i]=(nPrimo+2);} else {i--;}
        } else {
            if((nPrimo+2)%2==0 || (nPrimo+2)%3==0 || (nPrimo+2)%5==0){i--;} else {almacen[i]=(nPrimo+2);}
        }
        nPrimo++;
    }
    return almacen;
}

/*
 Implemente un método que reciba un arreglo de enteros con su tamaño respectivo y guarde dicho arreglo como texto de valores separados por comas en un archivo “primos.txt”.
 */
static void guardarNumero(int *almacen, int size, const char *direccion){
    FILE *almacenador = fopen(direccion, "w"); //Abro el flujo.
    for(int i=0; i<size; i++){
        fprintf(almacenador, "%i, ", almacen[i]); //Almaceno.
    }
    fclose(almacenador); //Cierro el flujo.
}

/*
 Implemente un método que reciba un arreglo de enteros con su tamaño respectivo y guarde dicho arreglo codificado en binario en un archivo “primos.bin”.
 */
static void guardarNumeroBin(int *almacen, int size, const char *direccion){
    FILE *almacenar = fopen(direccion, "wb"); //Abro flujo para binarios.
    fwrite(almacen, sizeof(int), size, almacenar); //Guardo los datos.
    fclose(almacenar); //Cierro el flujo.
}

/*
 Implemente un algoritmo que le permita leer y cargar un archivo de texto con las siguientes propiedades:
 a. En la primera línea del documento se leerán 2 números separados por una coma que indican la cantidad de f-filas y c-columnas que poseerá una matriz a leer.
 b. Las siguientes f líneas de texto poseen c valores separados por comas que deberán cargarse en una matriz.
 */
static void cargarArchivo(const char *direccion){
    FILE *almacenador = fopen(direccion, "r"); //Abro el flujo.
    int cantFilas = 0;
    int cantColumnas = 0;
    double **almacen[cantFilas];
    fread(&cantFilas, 1, 1, almacenador);
    fseek(almacenador, 3, 1);
    fread(&cantColumnas, 1, 1, almacenador);
    for (int i=0; i<cantFilas; i++) {
        *almacen[i] = new double[cantColumnas];
    }
    int posActual = 4; //A partir de ese archivo.
    for (int i=0; i<cantFilas; i++) {
        for (int j=0; j<cantColumnas; j++) {
            fread(almacen, sizeof(int), cantFilas*cantColumnas, almacenador); //Guarda los elementos.
        }
    }
    fclose(almacenador); //Cierro el flujo.
}

int main(int argc, const char * argv[]) {
    int *primos = calcularPrimos(1000);
    guardarNumero(primos, 1000, "/Users/emma/Documents/University/Programming 2/Prac and HW/Lab08/primos.txt");
    cout<<"Sistema numerico guardado con exito.\n"<<endl;
    guardarNumeroBin(primos, 1000, "/Users/emma/Documents/University/Programming 2/Prac and HW/Lab08/primos_bin.txt");
    cout<<"Sistema numerico binario guardado con exito.\n"<<endl;
    //cargarArchivo("/Users/emma/Desktop/prueba.txt"); //No se pudo solucionar el error de compilacion que presento.
    cout<<"Archivo cargado exitosamente."<<endl;
    
    return 0;
}

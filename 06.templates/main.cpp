//
//  main.cpp
//  Lab06
//
//  Created by Emmanuel on 10/18/20.
//  Lab about Templates.

#include <iostream>
using namespace std;

//Funcion ​sort que utilice plantillas para recibir un arreglo de objetos, su tamaño y los ordene de menor a mayor.
template <typename T, typename S> void sort(T *array01, S size){
    int j=0;
    for(int i=1; i<size; i++){ //Para analizar cada posicion del array.
        j=1; //Uso de auxiliar.
        while(j<size){ //Para moverse por todo el array al ordenar posiciones.
            if(array01[j-1]>array01[j]){
                T temp = array01[j-1];
                array01[j-1] = array01[j];
                array01[j] = temp;
            }
            j++;
        }
    }
}

class String {
private:
    char *str;
public:
    //CONSTRUCTOR
    String(char *palabra){this->str = palabra;}
    //SETTERS
    void setString(char* palabra){this->str = palabra;}
    //GETTERS
    char *getString(){return str;}
    
    bool operator == (char *str2) {
        //FIRST STEP: find out the length of the words.
        unsigned int size1 = 0;
        while(str[size1]!='\0'){
            size1++;
        }
        unsigned int size2 = 0;
        while(str2[size2]!='\0'){
            size2++;
        }
        //SECOND STEP: see if they're the same word.
        bool condition = true; //The return value.
        if(size1!=size2){ //This means that are not going to be equal, used in order to be efficient.
            condition = false;
        } else { //Then I try to find if they're equal.
            for(int i=0; i<size1; i++){
                if(str[i]!=str2[i]){condition=false;}
            }
        }
        return true;
    }
};

int main(int argc, const char * argv[]) {
    unsigned size = 7;
    String **nombres;
    for(int i=0; i<size; i++){
        char *palabra;
        cout<<"Ingrese una palabra"<<endl;
        cin>>*palabra;
        nombres[i] = new String(palabra);
    }
    //First: Print the array.
    for(int i=0; i<size; i++){
        cout<<*nombres[i]->getString()<<endl;
    }
    //Second: Sort the array.
    sort(nombres, size);
    //Third: Print all over the array.
    for(int i=0; i<size; i++){
        cout<<*nombres[i]->getString()<<endl;
    }
    //Fourth: Delete the instances.
    for (int i=0; i<size; i++) {
        delete nombres[i];
    }
    delete [] nombres;
    //Finish.
    return 0;
}

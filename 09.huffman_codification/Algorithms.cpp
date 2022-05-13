//
//  Algoritmos.cpp
//  HW01
//
//  Created by Emmanuel Solis on 10/11/20.
//  In this file are located all the required classes and structures for solving the problem.
//

#include <iostream>
using namespace std; //For the input and output of data.

//5% Posee los siguientes atributos: un caracter ​symbol que almacena el caracter representado y un entero positivo ​count que permite contar cuantas veces aparece el símbolo.
struct Symbol {
private:
    char caracter;
    unsigned int count; //The times that appers the caracter.
public:
    Symbol(){
        this->caracter = 0;
        this->count = 0;
    }
    //SETTERS.
    void setCaracter(char carac){this->caracter = carac;}
    void setCount(unsigned int number){this->count = number;}
    //GETTERS.
    char getCaracter(){return caracter;}
    unsigned int getCount(){return count;}
};

//10% Debe permitir almacenar un caracter symbol,​ un entero positivo ​count y punteros a un hijo izquierdo ​left y un hijo derecho right.
struct BinaryNode {
private:
    Symbol *caracter;
    unsigned int count;
    BinaryNode *left; //Left son.
    BinaryNode *right; //Right son.
public:
    //CONSTRUCTOR
    BinaryNode(char carac, int number){
        this->caracter = new Symbol();
        caracter->setCaracter(carac);
        caracter->setCount(number);
        this->count = number;
        this->left = 0; //Means null.
        this->right = 0; //Means null.
    }
    //SETTERS
    void setCaracter(char carac, int number){
        caracter->setCaracter(carac);
        caracter->setCount(number);
    }
    void setCount(int number) {this->count = number;}
    void setLeft(char carac, int number){this->left = new BinaryNode(carac, number);}
    void setRight(char carac, int number) {this->right = new BinaryNode(carac, number);}
    //GETTERS
    Symbol *getSymbol() {return caracter;}
    int getCount() {return count;}
    BinaryNode *getLeft() {return left;}
    BinaryNode *getRight() {return right;}
};

//5% Estructura árbol que posee por raíz un puntero a un BinaryNode y posee los siguientes métodos para recorrer el árbol:
struct CodingTree{
private:
    BinaryNode *root; //Starting point of the tree, works by pointers.
public:
    //CONSTRUCTOR
    CodingTree(){
        root = 0; //Means that's null.
    }
    //SETTERS
    void setRoot(char carac, int number) {this->root = new BinaryNode(carac, number);}
    //GETTERS
    BinaryNode *getRoot(){return root;}
    //Used for insert new elements in the tree.
    void insert(char carac, int number){
        if(root){
            BinaryNode *tmp = root;
            while ((number < tmp->getCount() && tmp->getLeft()) || (number > tmp->getCount() && tmp->getRight())) {
                if(number < tmp->getCount()){
                    tmp = tmp->getLeft();
                } else {
                    tmp = tmp->getRight();
                }
            }
            if(number != tmp->getCount()){
                if(number < tmp->getCount()){
                    tmp->getLeft()->setCaracter(carac, number);
                } else {
                    tmp->getRight()->setCaracter(carac, number);
                }
            }
        } else{
            root = new BinaryNode(carac, number);
        }
    }
    //10% Calcula la codificación de 1’s y 0’s necesaria para alcanzar el nodo con caracter ​c y almacena dicha codificación como una hilera de ‘1’s y ‘0’s en el arreglo ​code.​ Retorna si se logró encontrar la codificación.
    bool encode(char *code, char carac) {
        BinaryNode *tmp = root; //Starting point for searching from here.
        char *codification = new char[10024]; //A temporal space to storage the codification for each letter.
        bool existCode; //Used in order to know if exists a codification for each letter.
        unsigned short currentPosition = 0; //Used to move around the codification array.
        //Try to find the codification. Stops if I find it or if the element does not exist.
        while (tmp != 0 || tmp->getSymbol()->getCaracter() != carac) {
            if(tmp->getSymbol()->getCaracter()>carac){ //Move to the left.
                tmp = tmp->getLeft();
                codification[currentPosition] = 0;
                currentPosition++;
            }
            if(tmp->getSymbol()->getCaracter()<carac){ //Move to the right.
                tmp = tmp->getRight();
                codification[currentPosition] = 1;
                currentPosition++;
            }
        }
        codification[currentPosition] = '\0';
        //I need to see if I get a valid codification or the letter actually does not exist.
        if(tmp==0){ //It means that the letter was not found.
            existCode = false;
        } else { //It means that the letter exist and I have to copy what I the codification.
            existCode = true;
            for (int i=0; i==currentPosition; i++) {
                code[i] = codification[i]; //Copy the codification.
            }
        }
        delete [] tmp;
        delete [] codification;
        return existCode;
    }
    
    //10% Recibe una hilera ​code con una secuencia de ‘1’s y ‘0’s y recorre el árbol para hasta alcanzar un nodo hoja y retorna el caracter asociado a la secuencia. En la variable ​read​ anota la cantidad de “bits” (caracteres) leídos del arreglo.
    char decode(const char *code, unsigned int &read){
        BinaryNode *tmp = root;
        int i = 0;
        //Start following the codification.
        while(code[i]!='\0'){
            if(code[i]==0){ //Move to the left.
                tmp = tmp->getLeft();
            }
            if(code[i]==1){ //Move to the right.
                tmp = tmp->getRight();
            }
            i++;
        }
        char carac = tmp->getSymbol()->getCaracter();
        *&read = tmp->getCount(); //Storage the information.
        delete [] tmp;
        return carac;
    }
    //Calcula la suma de los contadores de todos los nodos no-hoja (nodos que tienen hijos). Este valor es la cantidad de bits que ocupará el archivo codificado. O en el caso de una hilera de ‘1’s y ‘0’s es la cantidad de bytes que ocupará dicha hilera.
    unsigned int count(){
        //Code....
        return 0;
    }
};

//10% Estructura cola de prioridad que almacena punteros a BinaryNodes, la prioridad está dada por el conteo de cada BinaryNode, con prioridad a números menores. Debe poseer los métodos ​push​, ​pop​ y ​getSize​.
struct PriorityQueue {
    struct Node{
    private:
        BinaryNode **reference;
        Node *next;
    public:
        //CONSTRUCTOR
        Node(BinaryNode *ref){
            this->reference = &ref;
            this->next = 0; //Means null.
        }
        //SETTERS
        void setNext(BinaryNode *ref){this->next = new Node(ref);}
        //GETTERS
        BinaryNode *getReference(){return *reference;}
        Node *getNext(){return next;}
    };
private:
    Node *head; //Starting point of the list.
    int size; //Size of the list.
    Node *getLast(Node *tmp){ //Recursive method that search the last element of the list.
        if(tmp->getNext()!=0){
            return getLast(tmp->getNext()); //Recursive call.
        } else {
            return tmp;
        }
    }
public:
    //CONSTRUCTOR
    PriorityQueue(){
        this->head = 0; //Means null.
        size = 0;
    }
    //SETTERS
    void setHead(BinaryNode *ref){this->head = new Node(ref);}
    void setSize(int number){this->size = number;}
    //GETTERS
    Node *getHead(){return head;}
    int getSize(){return size;}
    //Other methods.
    void incrementSize(){size++;}
    void push(char carac, int number){ //Enter a value in the list. Put it in the last position available.
        Node *last = getLast(head);
        last->setNext(new BinaryNode(carac, number));
    }
    Node *pop(){ //Removes an element from the list. Remove the first element in get in.
        Node *tmp = head;
        if(head->getNext()!=0){ //Means that exist.
            head = head->getNext();
        } else {
            head = 0; //Leave the Queue empty.
        }
        return tmp;
    }
};

/*
 10% Recibe por parámetro un arreglo de punteros a objetos Symbol ​symbols y retorna un puntero a un objeto CodingTree con la codificación que se obtiene para dichos símbolos:
    a. Los objetos Symbol ya vienen con su caracter y conteo respectivos.
    b. Primero creará objetos BinaryNode de los objetos del arreglo ​symbols y los agregará a una cola de prioridad. Solo tome en cuenta a aquellos Symbol cuyo conteo sea mayor a 0.
    c. Luego utilizará la cola de prioridad para ejecutar el algoritmo de construcción del árbol de codificación (​CodingTree​).
    d. Retorne el árbol de codificación creado.
 */
CodingTree *createCode(Symbol **symbol){
    //First step: create BinaryCode's objets.
    PriorityQueue *list = new PriorityQueue();
    int i = 0; //Index for moving in the array.
    while(symbol[i]!=0){ //Means that it's a valid position.
        if(symbol[i]->getCount()>0){ //Just use the ones that have more tahn cero.
            list->push(symbol[i]->getCaracter(), symbol[i]->getCount());
        }
    }
    //Second step: create tree.
    CodingTree *tree = new CodingTree();
    PriorityQueue::Node *tmp = list->pop();
    while(tmp!=0){ //Means that exist.
        tree->insert(tmp->getReference()->getSymbol()->getCaracter(), tmp->getReference()->getCount());
        tmp = list->pop(); //Move to the next element of the list.
    }
    return tree;
}

/*
 15% Retorna un arreglo de caracteres con el resultado de la codificación de ​str.​ Además se almacena el tamaño del arreglo retornado en la variable ​lengthOutput​.
    a. Primero reiniciará el valor de los contadores de cada objeto en ​symbols​ a 0.
    b. Luego contará la cantidad de veces que aparece cada char en ​str​, actualizará el valor del contador del Símbolo en ​symbols ​correspondiente.
    c. Obtenga el árbol de codificación usando ​createEncoding(​symbols​);
    d. Cree un nuevo arreglo para almacenar el resultado de la transcripción. El tamaño de dicho arreglo se puede calcular utilizando el método count del árbol de codificación y se almacena en ​lengthOutput​.
    e. Utilizando el árbol de codificación generado se procederá a transcribir el arreglo de caracteres ​str​ en su versión codificada en el arreglo ​result.
 */
char *encode(const char* str, unsigned int length, Symbol** symbols, unsigned int &lengthOutput){
    //First step: reset the number of each Symbol.
    int i = 0;
    while(symbols[i]!=0){ //Means that exist.
        symbols[i]->setCount(0); //Reseting it.
        i++;
    }
    unsigned int *timesApper = new unsigned int[256];
    for(int i=0; i<256; i++){ //Set all of them in ceros.
        timesApper[i] = 0;
    }
    int j = 0; //Counter for moving into the str.
    while(str[j]!=0){ //Means that's empty.
        timesApper[str[j]] += 1;
    }
    i = 0;
    while (symbols[i]!=0){
        symbols[i]->setCount(timesApper[symbols[i]->getCaracter()]); //Get the times that this position appers.
    }
    delete [] timesApper;
    //Second step:
    CodingTree *tree = createCode(symbols); //Send the request for creating the tree.
    char *transcription = new char[tree->count()];
    *&lengthOutput = tree->count();
    while (symbols[i]!=0){ //Create the codification.
        tree->encode(transcription, symbols[i]->getCaracter()); //Set the parameters in order to be able to create the CORRECT codification.
    }
    //Fourth and final step:
    return transcription;
}

/*
 15% Recibe por parámetros un arreglo de caracteres ​encoded que se desea decodificar, un entero positivo ​length con el tamaño del código almacenado en ​encoded​, un arreglo de punteros a objetos Symbol ​symbols con la información de los conteos de caracteres y un arreglo ​str que se utilizará para almacenar el archivo decodificado.
 a. Primero obtenga el árbol de codificación usando
 createEncoding(​symbols​);
 b. Puntos extra y puntos de honor +10: Si realizó los puntos extra 6.f entonces
 el arreglo ​encoded no poseerá una hilera de ‘1’s y ‘0’s, sino que los datos vendrán verdaderamente comprimidos. Cree una nueva hilera con el resultado de “descomprimir” ​encode​ en una hilera de ‘1’s y ‘0’s.
 c. Utilice su árbol de codificación para decodificar la hilera de ‘1’s y ‘0’s, guarde los resultados de las decodificación en ​str.
 */
void decode(const char *encoded, unsigned int length, Symbol **symbols, char *str){
    //Firt step: get the codification.
    CodingTree *tree = createCode(symbols);
    //Second and Final step: decodificate the tree.
    BinaryNode *tmp = tree->getRoot();
    for(int i=0; i<length; i++){
        if(tmp->getLeft()!=0 && tmp->getRight()!=0){ //Means that exist.
            str[i] = tmp->getSymbol()->getCaracter(); //Storage the element.
            if(encoded[i]==0){ ///Moving throught the tree.
                tmp = tmp->getLeft();
            }else{
                tmp = tmp->getRight();
            }
        }
    }
}

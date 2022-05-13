//
//  main.cpp
//  HW01
//
//  Created by Emmanuel Solis on 10/11/20.
//

#include <iostream>
#include "Algorithms.cpp" //In order to test the code.

//5% Implemente un código ​main​ que deberá hacer lo siguiente:
int main(int argc, const char * argv[]) {
    const char t[] = “All the world's a stage, and all the men and women merely players.”;
    char *code = CodingTree::encode(t,67,symbols, compressedLength);
    char *res = new char[67];
    int j = 97;
    for(int i=0; i++; i<67){
        res[i] = j;
        j++; //In order to change the used letter.
    }
    
    //Delete the references.
    delete []t;
    delete []code;
    delete []res;
    return 0;
}

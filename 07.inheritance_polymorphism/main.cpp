//
//  main.cpp
//  Lab07
//
//  Created by Emmanuel Solis on 11/20/20.
//

#include <iostream>
#include "Stack.cpp"
#include "Queue.cpp"
using namespace std;

int main(int argc, const char * argv[]) {
    cout<<"Digite lo que desea implentar.\n1. Una fila.\n2. Una cola."<<endl;
    int opcion;
    cin>>opcion;
    
    if (opcion==1) {
        Stack<int> stack = new Stack<int>;
        stack.push(0);
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);
        stack.push(6);
        stack.push(7);
        stack.push(8);
        stack.push(9);
        stack.push(10);
        cout<<stack.pop()<<endl;
    }
    if (opcion==2) {
        Queue<int> queue = new Queue<int>;
        queue.push(0);
        queue.push(1);
        queue.push(2);
        queue.push(3);
        queue.push(4);
        queue.push(5);
        queue.push(6);
        queue.push(7);
        queue.push(8);
        queue.push(9);
        queue.push(10);
        cout<<queue.pop()<<endl;
    }
    
    return 0;
}

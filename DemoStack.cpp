#include <assert.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "containers/stack.h"
#include "variadic-util.h"

void DemoStack() {

    CStack<T1> pila;

    pila.push(5, 6);
    pila.push(6, 2);
    pila.push(1, 7);
    pila.push(2, 1);
    pila.push(23, 2);
    cout << pila;

    cout << "Ingresamos un elemento a la Pila 1 de forma ( value : ref ): ";
    cin >> pila;

    cout << pila;

    // Copy Constructor

    cout << "Movemos los datos de la pila 1 a la pila 2..." << endl ;
    cout << "Pila 2:" << endl;
    CStack<T1> pila2 = move(pila);
    cout << pila2;
    cout << "Pila 1:" << endl;
    cout << pila;

    cout << "Copiamos los datos de la pila 2 a la pila 3..." << endl;
    CStack<T1> pila3 = pila2;

    cout << "Haremos 2 pop de la pila 2.";
    pila2.pop();
    pila2.pop();

    cout << endl;
    cout << "Pila 3:" << endl;
    cout << pila3;
    cout << "Pila 2:" << endl;
    cout << pila2;
}
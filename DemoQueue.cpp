#include <assert.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "containers/queue.h"
#include "variadic-util.h"

void DemoQueue() {

    CQueue<T1> cola;

    cola.push(5, 6);
    cola.push(6, 2);
    cola.push(1, 7);
    cola.push(2, 1);
    cola.push(23, 2);
    cout << "Cola 1: " << endl << cola ;

    cout << "Ingresamos 3 nodos a la cola 1: " << endl;
    for (int i = 0; i < 3; ++i) {
    cin >> cola;
    }
    
    cout << endl << "Ahora Cola 1:" << endl;
    cout << cola;

    // Copy Constructor

    cout << "Movemos los datos de la cola 1 a la cola 2..." << endl ;
    cout << "Cola 2:" << endl;
    CQueue<T1> cola2 = move(cola);
    cout << cola2;
    cout << "Cola 1:" << endl;
    cout << cola;

    cout << "Copiamos los datos de la cola 2 a la cola 3..." << endl;
    CQueue<T1> cola3 = cola2;

    cout << "Haremos 2 pop de la cola 2.";
    cola2.pop();
    cola2.pop();

    cout << endl;
    cout << "Pila 3:" << endl;
    cout << cola3;
    cout << "Pila 2:" << endl;
    cout << cola2;
}
#include <iostream>
#include "containers/heap.h"

using namespace std;

void DemoHeap(){

    cout << "\n Demo MaxHeap " << endl;

    // MaxHeap
    CHeap<MaxHeap<int>> maxH;

    maxH.push(10);
    maxH.push(25);
    maxH.push(15);
    maxH.push(30);
    maxH.push(5);

    cout << "\nMaxHeap tras push (10, 25, 15, 30, 5):" << endl;
    cout << maxH;

    cout << endl;
    cout << "pop: " << maxH.pop() << endl;
    cout << "pop: " << maxH.pop() << endl;
    cout << "Despues de 2 pops:" << endl;
    cout << maxH;

    CHeap<MaxHeap<int>> maxCopy(maxH);
    cout << "Copy constructor:" << endl;
    cout << maxCopy;

    CHeap<MaxHeap<int>> maxMoved(move(maxH));
    cout << "Move constructor (tamaño del Heap original: " << maxH.getSize() << "):" << endl;
    cout << "Nuevo MaxHeap: ";
    cout << maxMoved;

    cout <<"Ingresa un numero para el nuevo MaxHeap:" << endl;
    cin >> maxMoved;

    cout << maxMoved;

    // MinHeap
    cout << "\n Demo MaxHeap " << endl;
    CHeap<MinHeap<int>> minH;

    minH.push(10);
    minH.push(3);
    minH.push(7);

    cout << "\nMinHeap tras push (10, 3, 7):" << endl;
    cout << minH;

    cout << endl;
    cout << "pop: " << minH.pop() << endl;
    cout << "Despues de 1 pop:" << endl;
    cout << minH;

    CHeap<MinHeap<int>> minCopy(minH);
    cout << "Copy constructor:" << endl;
    cout << minCopy;

    CHeap<MinHeap<int>> minMoved(move(minH));
    cout << "Move constructor (tamaño del Heap original: " << minH.getSize() << "):" << endl;
    cout << "Nuevo MinHeap: ";
    cout << minMoved;

    cout <<"Ingresa un numero para el nuevo MinHeap:" << endl;
    cin >> minMoved;
    cout << minMoved;

}


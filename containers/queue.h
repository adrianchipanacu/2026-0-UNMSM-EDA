#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <iostream>
#include <mutex>
#include <assert.h>
#include "../general/types.h"
#include "../util.h"
#include "linkedlist.h"

template<typename T>
struct QueueTrait {
    using value_type = T;
};

template <typename T>
class CNode : public NodeLinkedList< QueueTrait<T> > {
public:
    CNode(const T &value, ref_type ref) : NodeLinkedList< QueueTrait<T> >(value, ref) {};
    // override de la función GetNext para que obtengamos CNode* y no NodeLinkedList*
          CNode<T>* GetNext()       { return static_cast<      CNode<T>*>(NodeLinkedList< QueueTrait<T> >::GetNext()); }
    const CNode<T>* GetNext() const { return static_cast<const CNode<T>*>(NodeLinkedList< QueueTrait<T> >::GetNext()); }
    // esta versión es para objetos que sean constantes, como lo hacemos para copiar
};

template <typename T>
struct CQueue {

    // En este caso, rehusamos los Nodos de la lista enlazada,
    // tienen atributos y métodos necesarios para la CQueue
    using Node = CNode<T>;

    mutable mutex mtx;
    Node *QLast = nullptr;
    Node *QFirst = nullptr;
    size_t n_Elements = 0;

public:
    // Constructor normal
    CQueue() {}

    //Copy Constructor
    CQueue( const CQueue<T> &another ) {
        lock_guard<mutex> lock(another.mtx); 

        Node *iter = another.QFirst, *iterThis;
        for (size_t n = 0; n < another.n_Elements; ++n) {
            this->push(0, 0);
        }
        iter = another.QFirst; 
        iterThis = QFirst;
        for (size_t n = 0; n < another.n_Elements; ++n) {
            iterThis->GetValueRef() = iter->GetValue();
            iterThis->GetRefRef() = iter->GetRef();
            iterThis = iterThis->GetNext();
            iter = iter->GetNext();
        }
            
        n_Elements = another.n_Elements;
    }

    //Move constructor
    CQueue( CQueue<T> &&another) noexcept {
        lock_guard<mutex> lock(another.mtx);

        QLast = another.QLast;
        QFirst = another.QFirst;
        another.QLast = nullptr;
        another.QFirst = nullptr;
        n_Elements = another.n_Elements;
        another.n_Elements = 0;
    }

    virtual ~CQueue() {
        Node *temp;
        while(QFirst != nullptr) {
            temp = QFirst->GetNext();
            delete QFirst;
            QFirst = temp;
        }
    }

    void push(const T &value, ref_type ref);
    T pop();
    size_t getSize() { lock_guard<mutex> lock(mtx); return n_Elements; };
    // Uso de mutex en caso hagan un push antes de devolver n_Elements


    // Opertor <<, también se imprime en vertical para verlo mejor
    friend ostream &operator<<(ostream &os, CQueue<T> &container){
        Node *iter = container.QFirst;

        os << "CQueue: size = " << container.getSize() << endl<<endl;
        os << "Inicio de la cola (Aqui desencolamos)" << endl;
        for (size_t i = 0; i < container.getSize(); ++i){
             os << "\t(" << iter->GetValue() << ", " << iter->GetRef() << ")" << endl;
             iter = iter->GetNext();
        }
        os << "Final de la cola" << endl;;
        os << endl;
        return os;
    }

    friend istream &operator>>(istream &is, CQueue<T> &container) {
        T val;
        ref_type ref;
        char symbol;

        if (!(is >> symbol) || symbol != '(')
            return is;

        if (!(is >> val >> symbol) || symbol != ':')
            return is;

        if (!(is >> ref >> symbol) || symbol != ')')
            return is;

        container.push(val, ref);
        return is;
    }

};

template <typename T>
void CQueue<T>::push(const T &value, ref_type ref) {
    lock_guard<mutex> lock(mtx);

    Node *lastNode = new Node(value, ref);
    if (QLast == nullptr)
        QFirst = lastNode;
    else
        QLast->GetNextRef() = lastNode; 
    QLast = lastNode;
    ++n_Elements;
}

template <typename T>
T CQueue<T>::pop() {
    lock_guard<mutex> lock(mtx);
    assert(QLast != nullptr);

    T value = QFirst->GetValue();
    Node *temp = QFirst;
    QFirst = QFirst->GetNext();
    delete temp;
    --n_Elements;

    return value;
}

void DemoQueue();

#endif // __QUEUE_H__
#ifndef __HEAP_H__
#define __HEAP_H__

#include <iostream>
#include <vector>
#include <mutex>
#include <assert.h>
#include <iostream>
#include "../general/types.h"
#include "../util.h"

using namespace std;

template <typename T>
struct MaxHeap {
    using value_type = T;
    using Func = greater<T>;
};

template <typename T>
struct MinHeap {
    using value_type = T;
    using Func = less<T>;
};

template <typename Traits>
class CHeap{
    using value_type = typename Traits::value_type;
    using comp = typename Traits::Func;

    vector<value_type> m_Data;
    mutable mutex mtx;

    size_t parent (size_t index) { return (index - 1) >> 1; }
    size_t left   (size_t index) { return (index << 1) + 1; }
    size_t right  (size_t index) { return (index << 1) + 2; }

    void heapifyUp   (size_t index);
    void heapifyDown (size_t index);

public:
    // Constructor
    CHeap(){};

    // Copy Constructor
    CHeap(const CHeap &another) {
        lock_guard<mutex> lock(another.mtx);
        m_Data = another.m_Data;
    };

    // Move Constructor
    CHeap(CHeap &&another) noexcept {
        lock_guard<mutex> lock(another.mtx);
        m_Data = move(another.m_Data);
    }

    virtual ~CHeap(){
        lock_guard<mutex> lock(mtx);
        vector<value_type>().swap(m_Data);
    }
    

    size_t getSize() const { return m_Data.size(); }
    void push(value_type value);
    value_type pop();

    template <typename Tr>
    friend ostream &operator<<(ostream &os, const CHeap<Tr> &heap);
    template <typename Tr>
    friend istream &operator>>(istream &is, const CHeap<Tr> &heap);

};

template <typename Traits>
void CHeap<Traits>::heapifyUp (size_t index) {
    while (index) {
        if (comp()( m_Data[index], m_Data[parent( index )] )) {
            swap(m_Data[index], m_Data[parent( index )] );
            index = parent( index );
        }
        else
            break;
    }
}

template <typename Traits>
void CHeap<Traits>::heapifyDown (size_t index) {
    auto smallest = index;
    auto size = m_Data.size();  

    while ( true ) {
        auto leftTemp  = left  ( index );
        auto rightTemp = right ( index );

        if ( leftTemp < size && comp()( m_Data[leftTemp], m_Data[smallest] )) {
            smallest = leftTemp;
        }
        if ( rightTemp < size && comp()( m_Data[rightTemp], m_Data[smallest] )) {
            smallest = rightTemp;
        }
        if ( smallest == index) {
            break;
        }
        swap( m_Data[index], m_Data[smallest] );
        index = smallest;
    }
}

template <typename Traits>
void CHeap<Traits>::push(value_type value) {
    lock_guard<mutex> lock(mtx);

    m_Data.push_back(value);
    heapifyUp(m_Data.size() - 1);
}

template <typename Traits>
typename CHeap<Traits>::value_type CHeap<   Traits>::pop() {
    lock_guard<mutex> lock(mtx);

    assert(m_Data.size() > 0);

    value_type value = m_Data[0];
    swap( m_Data[0], m_Data[m_Data.size() - 1] );
    m_Data.pop_back();
    heapifyDown(0);

    return value;
}

template <typename Traits>
ostream &operator<<(ostream &os, const CHeap<Traits> &heap) {
    lock_guard<mutex> lock(heap.mtx);

    os << endl;
    os << "CHeap size: " << heap.m_Data.size() << endl << endl;
    size_t level = 1;
    for(size_t i = 0; i < heap.m_Data.size(); ++i) {
        if ((i + 1) >> level == 1 ) {
            os << endl;
            ++level;
        }
        os << heap.m_Data[i] << " ";
    }
    os << endl;
    return os;
}
template <typename Traits>
istream &operator>>(istream &is, CHeap<Traits> &heap) {
    typename Traits::value_type value;
    is >> value;
    heap.push(value);

    return is;
}

void DemoHeap();
#endif // __HEAP_H__
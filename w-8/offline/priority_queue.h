#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "fibonacci_heap_node.h"
using namespace fibonacci_heap_node;

#include "fibonacci_heap.h"
using namespace fibonacci_heap;

#include <cassert>

template <class T, class Compare = Compare<T>>
class PriorityQueue : protected FibonacciHeap<T, Compare>
{
public:
    PriorityQueue();
    T top();
    bool empty();
    int size();
    void push(T);
    void pop();
};

template <class T, class Compare>
PriorityQueue<T, Compare>::PriorityQueue()
{
}

template <class T, class Compare>
T PriorityQueue<T, Compare>::top()
{
    assert(this->getNodeCount() > 0);
    return *(this->getHead()->getKey());
}

template <class T, class Compare>
bool PriorityQueue<T, Compare>::empty()
{
    return this->size() == 0;
}

template <class T, class Compare>
int PriorityQueue<T, Compare>::size()
{
    return this->getNodeCount();
}

template <class T, class Compare>
void PriorityQueue<T, Compare>::push(T value)
{
    this->insert(new Node<T>(new T(value)));
}

template <class T, class Compare>
void PriorityQueue<T, Compare>::pop()
{
    this->extractMin();
}

#endif

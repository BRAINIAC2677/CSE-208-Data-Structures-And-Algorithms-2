/*
Author: Asif Azad
Date: 08.01.2022

Binary heap for any key values.
- one indexed arraycontainer.
Priority queue is implemented using binary heap.
*/

#ifndef BINARY_HEAP
#define BINARY_HEAP

#include <vector>
#include <cassert>
using namespace std;

namespace binary_heap
{
#define DEFAULT_MAX_SIZE 100000

    template <class T>
    class Compare
    {
    public:
        bool operator()(T a, T b)
        {
            // a has more priority than b
            return a < b;
        }
    };

    template <class T, class Compare = Compare<T>>
    class BinaryHeap
    {
        T *arrayContainer;
        int maxSize;
        void reallocate();
        void percolate(int index, bool up = true);

    protected:
        int heapSize;

    public:
        BinaryHeap();
        BinaryHeap(int);
        BinaryHeap(vector<T> inp);
        void heapRun(int);
        ~BinaryHeap();
        void insert(T);
        T getMax();
        T deleteMax();
    };

    //======================== private helper functions ===========================
    template <class T, class Compare>
    void BinaryHeap<T, Compare>::reallocate()
    {
        int tempMaxSize = this->maxSize * 2;
        T *tempArrayContainer = new T[tempMaxSize];
        for (int i = 1; i <= this->heapSize; i++)
        {
            tempArrayContainer[i] = this->arrayContainer[i];
        }
        delete[] this->arrayContainer;
        this->maxSize = tempMaxSize;
        this->arrayContainer = tempArrayContainer;
    }

    template <class T, class Compare>
    void BinaryHeap<T, Compare>::percolate(int index, bool up)
    {
        if (up)
        {
            if (index == 1)
            {
                return;
            }
            if (Compare()(this->arrayContainer[index], this->arrayContainer[index / 2]))
            {
                T temp = this->arrayContainer[index];
                this->arrayContainer[index] = this->arrayContainer[index / 2];
                this->arrayContainer[index / 2] = temp;
                this->percolate(index / 2, up);
            }
        }
        else
        {
            if (index > this->heapSize / 2)
            {
                return;
            }
            int largestInd = index;
            if (2 * index <= this->heapSize && Compare()(this->arrayContainer[2 * index], this->arrayContainer[largestInd]))
            {
                largestInd = 2 * index;
            }
            if (2 * index + 1 <= this->heapSize && Compare()(this->arrayContainer[2 * index + 1], this->arrayContainer[largestInd]))
            {
                largestInd = 2 * index + 1;
            }
            if (largestInd != index)
            {
                T temp = this->arrayContainer[index];
                this->arrayContainer[index] = this->arrayContainer[largestInd];
                this->arrayContainer[largestInd] = temp;
                this->percolate(largestInd, up);
            }
        }
    }
    //======================== end of private helper functions ====================

    //======================= member functions ====================================
    template <class T, class Compare>
    BinaryHeap<T, Compare>::BinaryHeap()
    {
        this->heapSize = 0;
        this->maxSize = DEFAULT_MAX_SIZE;
        this->arrayContainer = new T[this->maxSize];
    }

    template <class T, class Compare>
    BinaryHeap<T, Compare>::BinaryHeap(int max_size)
    {
        this->heapSize = 0;
        this->maxSize = max_size;
        this->arrayContainer = new T[this->maxSize];
    }

    template <class T, class Compare>
    BinaryHeap<T, Compare>::BinaryHeap(vector<T> inp)
    {
        this->heapSize = 0;
        this->maxSize = inp.size() + 1;
        this->arrayContainer = new T[this->maxSize];
        for (T element : inp)
        {
            this->insert(element);
        }
    }

    template <class T, class Compare>
    BinaryHeap<T, Compare>::~BinaryHeap()
    {
        delete[] this->arrayContainer;
    }

    template <class T, class Compare>
    void BinaryHeap<T, Compare>::insert(T element)
    {
        heapRun(9);
        if (this->heapSize >= this->maxSize - 1)
        {
            this->reallocate();
        }
        this->heapSize++;
        this->arrayContainer[this->heapSize] = element;
        this->percolate(this->heapSize);
    }

    template <class T, class Compare>
    T BinaryHeap<T, Compare>::getMax()
    {
        assert(this->heapSize > 0);
        return this->arrayContainer[1];
    }

    template <class T, class Compare>
    void BinaryHeap<T, Compare>::heapRun(int n)
    {
        if (n == 0)
        {
            return;
        }
        this->heapRun(n - 1);
        this->heapRun(n - 1);
    }

    template <class T, class Compare>
    T BinaryHeap<T, Compare>::deleteMax()
    {
        assert(this->heapSize > 0);
        T ret = this->arrayContainer[1];
        this->arrayContainer[1] = this->arrayContainer[this->heapSize];
        this->heapSize--;
        this->percolate(1, false);
        return ret;
    }

    template <class T, class Compare = Compare<T>>
    class PriorityQueue : protected BinaryHeap<T, Compare>
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
    PriorityQueue<T, Compare>::PriorityQueue() : BinaryHeap<T, Compare>()
    {
    }

    template <class T, class Compare>
    T PriorityQueue<T, Compare>::top()
    {
        return this->getMax();
    }

    template <class T, class Compare>
    bool PriorityQueue<T, Compare>::empty()
    {
        return this->size() == 0;
    }

    template <class T, class Compare>
    int PriorityQueue<T, Compare>::size()
    {
        return this->heapSize;
    }

    template <class T, class Compare>
    void PriorityQueue<T, Compare>::push(T value)
    {
        this->insert(value);
    }

    template <class T, class Compare>
    void PriorityQueue<T, Compare>::pop()
    {
        this->deleteMax();
    }
}

#endif
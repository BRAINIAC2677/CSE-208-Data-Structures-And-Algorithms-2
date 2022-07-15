#include "fibonacci_heap_node.h"
using namespace fibonacci_heap_node;

#include "fibonacci_heap.h"
using namespace fibonacci_heap;

#include "priority_queue.h"

#include <bits/stdc++.h>
#include <experimental/random>
using namespace std;

template <class T = int>
void printFibHeap(Node<T> *head)
{
    if (head == nullptr)
    {
        return;
    }
    Node<T> *curr = head;
    while (true)
    {
        // print the info that you want
        cout << *(curr->getKey());
        if (curr->getParent() != nullptr)
        {
            cout << "(" << *(curr->getParent()->getKey()) << ")";
        }
        else
        {
            cout << "(r)";
        }
        cout << "(" << curr->getMark() << ") ";
        // print the info that you want
        curr = curr->getRightSibling();
        if (curr == head)
        {
            break;
        }
    }
    cout << "\n";
    curr = head;
    while (true)
    {
        printFibHeap(curr->getChild());
        curr = curr->getRightSibling();
        if (curr == head)
        {
            break;
        }
    }
}

// assumes that the heap is empty
template <class T>
bool testExtractMin(FibonacciHeap<T> *fh, int iterations = 1000)
{
    vector<int> tc;
    for (int i = 0; i < iterations; i++)
    {
        tc.push_back(experimental::randint(0, iterations));
        fh->insert(new Node<T>(new T(tc[i])));
    }
    sort(tc.rbegin(), tc.rend());
    for (int i = 0; i < iterations; i++)
    {
        if (*(fh->extractMin()->getKey()) != tc[i])
        {
            return false;
        }
    }
    return true;
}

template <class T>
bool searchHeap(Node<T> *head, Node<T> *target)
{
    if (head == nullptr)
    {
        return target == nullptr;
    }
    Node<T> *curr = head;
    while (true)
    {
        if (curr == target)
        {
            return true;
        }
        curr = curr->getRightSibling();
        if (curr == head)
        {
            break;
        }
    }
    curr = head;
    bool found = false;
    while (true)
    {
        found |= searchHeap(curr->getChild(), target);
        curr = curr->getRightSibling();
        if (curr == head)
        {
            break;
        }
    }
    return found;
}

template <class T = int>
bool testDelete(FibonacciHeap<T> *fh, int iterations = 1000, T lowest = INT_MIN)
{
    vector<Node<T> *> randomNodes;
    for (int i = 0; i < iterations; i++)
    {
        randomNodes.push_back(new Node<T>(new T(experimental::randint(lowest, INT_MAX))));
        fh->insert(randomNodes[i]);
    }
    for (int i = 0; i < iterations; i++)
    {
        cout << "Deleting " << *(randomNodes[i]->getKey()) << endl;
        fh->deleteKey(randomNodes[i], lowest);
        if (searchHeap(fh->getHead(), randomNodes[i]))
        {
            printFibHeap(fh->getHead());
            cout << "Failed to delete node " << *(randomNodes[i]->getKey()) << endl;
            return false;
        }
    }
    return true;
}

int main()
{
    PriorityQueue<pair<int, int>> pq;
    pq.push({1, 1});
    pq.push({-1, 3});
    while (!pq.empty())
    {
        cout << pq.top().first << " " << pq.top().second << endl;
        pq.pop();
    }
    return 0;
}
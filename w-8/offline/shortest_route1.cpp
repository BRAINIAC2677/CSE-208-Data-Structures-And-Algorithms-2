#include <bits/stdc++.h>
using namespace std;

namespace fibonacci_heap
{
    /*=========================== start: Compare Class ===========================*/
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
    /*=========================== end: Compare Class ===========================*/

    /*=========================== start: Node Class ===========================*/
    template <class T>
    class Node
    {
        bool mark;
        int degree;
        Node *parent, *child, *left_sibling, *right_sibling;
        T *key;

    public:
        Node(T *key = nullptr);
        void setMark(bool);
        void setDegree(int);
        void setParent(Node *);
        void setChild(Node *);
        void setLeftSibling(Node *);
        void setRightSibling(Node *);
        void setKey(T *);
        bool getMark();
        int getDegree();
        Node *getParent();
        Node *getChild();
        Node *getLeftSibling();
        Node *getRightSibling();
        T *getKey();
    };

    template <class T>
    Node<T>::Node(T *key)
    {
        this->mark = false;
        this->degree = 0;
        this->parent = nullptr;
        this->child = nullptr;
        this->left_sibling = nullptr;
        this->right_sibling = nullptr;
        this->key = key;
    }

    // Node class setter functions
    template <class T>
    void Node<T>::setMark(bool mark)
    {
        this->mark = mark;
    }
    template <class T>
    void Node<T>::setDegree(int degree)
    {
        this->degree = degree;
    }
    template <class T>
    void Node<T>::setParent(Node *parent)
    {
        this->parent = parent;
    }
    template <class T>
    void Node<T>::setChild(Node *child)
    {
        this->child = child;
    }
    template <class T>
    void Node<T>::setLeftSibling(Node *left_sibling)
    {
        this->left_sibling = left_sibling;
    }
    template <class T>
    void Node<T>::setRightSibling(Node *right_sibling)
    {
        this->right_sibling = right_sibling;
    }
    template <class T>
    void Node<T>::setKey(T *key)
    {
        this->key = key;
    }

    // Node class getter functions
    template <class T>
    bool Node<T>::getMark()
    {
        return this->mark;
    }
    template <class T>
    int Node<T>::getDegree()
    {
        return this->degree;
    }
    template <class T>
    Node<T> *Node<T>::getParent()
    {
        return this->parent;
    }
    template <class T>
    Node<T> *Node<T>::getChild()
    {
        return this->child;
    }
    template <class T>
    Node<T> *Node<T>::getLeftSibling()
    {
        return this->left_sibling;
    }
    template <class T>
    Node<T> *Node<T>::getRightSibling()
    {
        return this->right_sibling;
    }
    template <class T>
    T *Node<T>::getKey()
    {
        return this->key;
    }
    /*=========================== end: Node Class ===========================*/

    /*=========================== start: FibonacciHeap Class ===========================*/
    template <class T, class Compare = Compare<T>>
    class FibonacciHeap
    {

        int node_count;
        Node<T> *head; // head is also the node with most priority

        // private helper function
        void link(Node<T> *, Node<T> *);
        void addToRootList(Node<T> *);
        void removeFromList(Node<T> *);
        void consolidate();
        void cut(Node<T> *, Node<T> *);
        void cascadingCut(Node<T> *);

    public:
        int getNodeCount();
        Node<T> *getHead();

        FibonacciHeap();
        void insert(Node<T> *);
        FibonacciHeap<T, Compare> *merge(FibonacciHeap<T, Compare> *);
        Node<T> *extractMin();
        void decreaseKey(Node<T> *, T);
        void deleteKey(Node<T> *, T);
    };

    template <class T, class Compare>
    void FibonacciHeap<T, Compare>::link(Node<T> *c, Node<T> *p)
    {
        // removing c from the root list of the heap
        this->removeFromList(c);

        // adding c to the child list of p
        c->setParent(p);
        if (p->getChild() == nullptr)
        {
            p->setChild(c);
            c->setLeftSibling(c);
            c->setRightSibling(c);
        }
        else
        {
            c->setLeftSibling(p->getChild());
            c->setRightSibling(p->getChild()->getRightSibling());
            p->getChild()->setRightSibling(c);
            c->getRightSibling()->setLeftSibling(c);
        }
        p->setDegree(p->getDegree() + 1);
        c->setMark(false);
    }

    template <class T, class Compare>
    void FibonacciHeap<T, Compare>::addToRootList(Node<T> *node)
    {
        node->setParent(nullptr);
        if (this->head == nullptr)
        {
            node->setLeftSibling(node);
            node->setRightSibling(node);
            this->head = node;
        }
        else
        {
            node->setLeftSibling(this->head);
            node->setRightSibling(this->head->getRightSibling());
            this->head->setRightSibling(node);
            (node->getRightSibling())->setLeftSibling(node);
        }
        if (Compare()(*(node->getKey()), *(this->head->getKey())))
        {
            this->head = node;
        }
    }

    // remove node from the root list/child list of its parent
    template <class T, class Compare>
    void FibonacciHeap<T, Compare>::removeFromList(Node<T> *node)
    {
        (node->getLeftSibling())->setRightSibling(node->getRightSibling());
        (node->getRightSibling())->setLeftSibling(node->getLeftSibling());
    }

    template <class T, class Compare>
    void FibonacciHeap<T, Compare>::consolidate()
    {
        int max_degree = (int)log2(this->node_count) + 1; // upperbound on the degree of the root list

        // initialzing the array of degree lists
        Node<T> **aux_array = new Node<T> *[max_degree + 1];
        for (int i = 0; i <= max_degree; i++)
        {
            aux_array[i] = nullptr;
        }

        // preserving a copy of the root list as the main root list will be modified
        vector<Node<T> *> root_list = {this->head};
        for (Node<T> *ptr = this->head->getRightSibling(); ptr != this->head; ptr = ptr->getRightSibling())
        {
            root_list.push_back(ptr);
        }

        aux_array[this->head->getDegree()] = root_list[0];
        for (int i = 1; i < root_list.size(); i++)
        {
            Node<T> *y = root_list[i];
            int d = y->getDegree();
            while (aux_array[d] != nullptr)
            {
                Node<T> *x = aux_array[d];
                if (Compare()(*(x->getKey()), *(y->getKey())))
                {
                    Node<T> *temp = y;
                    y = x;
                    x = temp;
                }
                this->link(x, y);
                aux_array[d] = nullptr;
                d++;
            }
            aux_array[d] = y;
        }

        this->head = nullptr;
        for (int i = 0; i <= max_degree; i++)
        {
            if (aux_array[i] != nullptr)
            {
                this->addToRootList(aux_array[i]);
            }
        }
    }

    template <class T, class Compare>
    void FibonacciHeap<T, Compare>::cut(Node<T> *c, Node<T> *p)
    {
        p->setDegree(p->getDegree() - 1);
        if (p->getDegree() == 0)
        {
            p->setChild(nullptr);
        }
        else
        {
            c->getLeftSibling()->setRightSibling(c->getRightSibling());
            c->getRightSibling()->setLeftSibling(c->getLeftSibling());
            if (c == p->getChild())
            {
                p->setChild(c->getRightSibling());
            }
        }
        this->addToRootList(c);
        c->setMark(false);
    }

    template <class T, class Compare>
    void FibonacciHeap<T, Compare>::cascadingCut(Node<T> *node)
    {
        Node<T> *p = node->getParent();
        if (p != nullptr)
        {
            if (node->getMark() == false)
            {
                node->setMark(true);
            }
            else
            {
                this->cut(node, p);
                this->cascadingCut(p);
            }
        }
    }

    template <class T, class Compare>
    int FibonacciHeap<T, Compare>::getNodeCount()
    {
        return this->node_count;
    }

    template <class T, class Compare>
    Node<T> *FibonacciHeap<T, Compare>::getHead()
    {
        return this->head;
    }

    template <class T, class Compare>
    FibonacciHeap<T, Compare>::FibonacciHeap()
    {
        this->node_count = 0;
        this->head = nullptr;
    }

    template <class T, class Compare>
    void FibonacciHeap<T, Compare>::insert(Node<T> *new_node)
    {
        this->addToRootList(new_node);
        this->node_count++;
    }

    template <class T, class Compare>
    FibonacciHeap<T, Compare> *FibonacciHeap<T, Compare>::merge(FibonacciHeap<T, Compare> *other)
    {
        Node<T> h1 = this->getHead();
        Node<T> h2 = other->getHead();
        if (h1 == nullptr)
        {
            this->head = h2;
            this->node_count = other->getNodeCount();
        }
        else if (h2 != nullptr)
        {
            (h1->getRightSibling())->setLeftSibling(h2->getLeftSibling());
            (h2->getLeftSibling())->setRightSibling(h1->getRightSibling());
            h1->setRightSibling(h2);
            h2->setLeftSibling(h1);
            this->node_count += other->getNodeCount();
        }
        return this;
    }

    template <class T, class Compare>
    Node<T> *FibonacciHeap<T, Compare>::extractMin()
    {
        Node<T> *min = this->head;
        if (min != nullptr)
        {
            Node<T> *ptr = min->getChild();
            if (ptr != nullptr)
            {
                // adding children of min to root list
                while (true)
                {
                    Node<T> *temp = ptr;
                    ptr = ptr->getRightSibling();
                    this->addToRootList(temp);
                    if (ptr == min->getChild())
                    {
                        break;
                    }
                }
            }
            this->removeFromList(min);
            if (min == min->getRightSibling())
            {
                this->head = nullptr;
            }
            else
            {
                this->head = min->getRightSibling();
                this->consolidate();
            }
        }
        if (this->node_count > 0)
        {
            this->node_count--;
        }
        return min;
    }

    template <class T, class Compare>
    void FibonacciHeap<T, Compare>::decreaseKey(Node<T> *node, T new_key)
    {
        T *kptr = &(new_key);
        if (Compare()(*kptr, *(node->getKey())))
        {
            node->setKey(kptr);
            Node<T> *p = node->getParent();
            if (p != nullptr && Compare()(*(node->getKey()), *(p->getKey())))
            {
                this->cut(node, p);
                this->cascadingCut(p);
            }
            if (Compare()(*(node->getKey()), *(this->head->getKey())))
            {
                this->head = node;
            }
        }
    }

    template <class T, class Compare>
    void FibonacciHeap<T, Compare>::deleteKey(Node<T> *node, T lowest)
    {
        this->decreaseKey(node, lowest);
        this->extractMin();
    }
    /*========================== end: FibonacciHeap class ========================*/

    /*========================== start: PriorityQueue class ========================*/
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
    /*========================== end: PriorityQueue class ========================*/
}

int n, m;
const long long int inf = 1000000000000000000;
vector<vector<pair<long long int, int>>> adj;
vector<long long int> path_cost, path_len;
vector<int> par;

void fibDjikstra(int root)
{
    path_cost.assign(n + 1, inf);
    path_len.assign(n + 1, inf);
    par.assign(n + 1, -1);
    path_cost[root] = 0;
    path_len[root] = 0;
    fibonacci_heap::PriorityQueue<pair<long long int, int>> pq;
    pq.push({path_cost[root], root});
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        int u = cur.second;
        if (cur.first != path_cost[u])
        {
            continue;
        }
        for (auto next : adj[u])
        {
            int v = next.second;
            long long int w = next.first;
            if (path_cost[u] + w < path_cost[v])
            {
                path_cost[v] = path_cost[u] + w;
                path_len[v] = path_len[u] + 1;
                par[v] = u;
                pq.push({path_cost[v], v});
            }
        }
    }
}

// problem link: https://cses.fi/problemset/task/1671/
int main()
{
    cin >> n >> m;
    adj.assign(n + 1, vector<pair<long long int, int>>());
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long int w;
        cin >> u >> v >> w;
        u--;
        v--;
        // directed graph
        adj[u].push_back({w, v});
    }
    fibDjikstra(0);
    for (int i = 0; i < n; i++)
    {
        cout << path_cost[i] << " \n"[i == n - 1];
    }
    return 0;
}
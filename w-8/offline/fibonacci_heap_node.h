#ifndef FIBONACCI_HEAP_NODE
#define FIBONACCI_HEAP_NODE

namespace fibonacci_heap_node
{
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

    // all setters defined
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

    // all getters defined
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
}
#endif
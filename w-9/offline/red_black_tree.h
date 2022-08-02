#include <cstddef>
#include <cassert>
using namespace std;

#ifndef RBT
#define RBT

const int RED = 0;
const int BLACK = 1;

namespace rbt
{
    template <class K>
    class Node
    {
        K key;
        int color, left_subtree_size;
        Node<K> *left, *right, *parent;

    public:
        Node(K key, Node<K> *sentinel = nullptr);
        K getKey();
        int getColor();
        int getLeftSubtreeSize();
        Node<K> *getLeft();
        Node<K> *getRight();
        Node<K> *getParent();
        void setKey(K key);
        void setColor(int color);
        void setLeftSubtreeSize(int subtree_size);
        void setLeft(Node<K> *left);
        void setRight(Node<K> *right);
        void setParent(Node<K> *parent);
    };

    template <class K>
    Node<K>::Node(K key, Node<K> *sentinel)
    {
        this->key = key;
        this->color = RED;
        this->left_subtree_size = 1;
        this->left = sentinel;
        this->right = sentinel;
        this->parent = sentinel;
    }

    template <class K>
    K Node<K>::getKey()
    {
        return this->key;
    }

    template <class K>
    int Node<K>::getColor()
    {
        return this->color;
    }

    template <class K>
    int Node<K>::getLeftSubtreeSize()
    {
        return this->left_subtree_size;
    }

    template <class K>
    Node<K> *Node<K>::getLeft()
    {
        return this->left;
    }

    template <class K>
    Node<K> *Node<K>::getRight()
    {
        return this->right;
    }

    template <class K>
    Node<K> *Node<K>::getParent()
    {
        return this->parent;
    }

    template <class K>
    void Node<K>::setKey(K key)
    {
        this->key = key;
    }

    template <class K>
    void Node<K>::setColor(int color)
    {
        this->color = color;
    }

    template <class K>
    void Node<K>::setLeftSubtreeSize(int left_subtree_size)
    {
        this->left_subtree_size = left_subtree_size;
    }

    template <class K>
    void Node<K>::setLeft(Node<K> *left)
    {
        this->left = left;
    }

    template <class K>
    void Node<K>::setRight(Node<K> *right)
    {
        this->right = right;
    }

    template <class K>
    void Node<K>::setParent(Node<K> *parent)
    {
        this->parent = parent;
    }

    /*========================== RBT class ===============================*/

    template <class K>
    class RedBlackTree
    {
        Node<K> *root, *sentinel;
        void rotateLeft(Node<K> *x);
        void rotateRight(Node<K> *x);
        void insertFixup(Node<K> *x);
        void removeFixup(Node<K> *x);
        Node<K> *successor(Node<K> *x);
        void leftSubtreeSizeIncrement(Node<K> *x);
        void leftSubtreeSizeDecrement(Node<K> *x);

    public:
        RedBlackTree(K);
        void insert(K key);
        Node<K> *remove(K key);
        Node<K> *search(K key);
        int noOfKeysLessThan(K key);
    };

    template <class K>
    RedBlackTree<K>::RedBlackTree(K sentinel_key)
    {
        this->sentinel = new Node<K>(sentinel_key);
        this->sentinel->setLeftSubtreeSize(0);
        assert(this->sentinel != nullptr);
        this->sentinel->setColor(BLACK);
        this->root = this->sentinel;
    }

    template <class K>
    void RedBlackTree<K>::rotateLeft(Node<K> *x)
    {
        Node<K> *y = x->getRight();
        x->setRight(y->getLeft());
        y->getLeft()->setParent(x);
        y->setParent(x->getParent());
        if (x->getParent() == this->sentinel)
        {
            this->root = y;
        }
        else if (x == x->getParent()->getLeft())
        {
            x->getParent()->setLeft(y);
        }
        else
        {
            x->getParent()->setRight(y);
        }
        y->setLeft(x);
        x->setParent(y);
        x->setLeftSubtreeSize(x->getLeft() == this->sentinel ? 1 : x->getLeft()->getLeftSubtreeSize() + 1);
        y->setLeftSubtreeSize(y->getLeft() == this->sentinel ? 1 : y->getLeft()->getLeftSubtreeSize() + 1);
    }

    template <class K>
    void RedBlackTree<K>::rotateRight(Node<K> *x)
    {
        Node<K> *y = x->getLeft();
        x->setLeft(y->getRight());
        y->getRight()->setParent(x);
        y->setParent(x->getParent());
        if (x->getParent() == this->sentinel)
        {
            this->root = y;
        }
        else if (x == x->getParent()->getRight())
        {
            x->getParent()->setRight(y);
        }
        else
        {
            x->getParent()->setLeft(y);
        }
        y->setRight(x);
        x->setParent(y);
        x->setLeftSubtreeSize(x->getLeft() == this->sentinel ? 1 : x->getLeft()->getLeftSubtreeSize() + 1);
        y->setLeftSubtreeSize(y->getLeft() == this->sentinel ? 1 : y->getLeft()->getLeftSubtreeSize() + 1);
    }

    template <class K>
    void RedBlackTree<K>::leftSubtreeSizeIncrement(Node<K> *x)
    {
        if (x != this->sentinel)
        {
            x->setLeftSubtreeSize(x->getLeftSubtreeSize() + 1);
            leftSubtreeSizeIncrement(x->getParent());
        }
    }

    template <class K>
    void RedBlackTree<K>::leftSubtreeSizeDecrement(Node<K> *x)
    {
        if (x != this->sentinel)
        {
            x->setLeftSubtreeSize(x->getLeftSubtreeSize() - 1);
            leftSubtreeSizeDecrement(x->getParent());
        }
    }

    template <class K>
    void RedBlackTree<K>::insertFixup(Node<K> *x)
    {
        while (x->getParent()->getColor() == RED)
        {
            if (x->getParent() == x->getParent()->getParent()->getLeft())
            {
                Node<K> *y = x->getParent()->getParent()->getRight();
                assert(y != nullptr);
                if (y->getColor() == RED)
                {
                    assert(x->getParent() != nullptr);
                    x->getParent()->setColor(BLACK);
                    assert(y != nullptr);
                    y->setColor(BLACK);
                    x->getParent()->getParent()->setColor(RED);
                    x = x->getParent()->getParent();
                }
                else
                {
                    if (x == x->getParent()->getRight())
                    {
                        x = x->getParent();
                        rotateLeft(x);
                    }

                    assert(x->getParent() != nullptr);
                    x->getParent()->setColor(BLACK);
                    x->getParent()->getParent()->setColor(RED);
                    rotateRight(x->getParent()->getParent());
                }
            }
            else
            {
                Node<K> *y = x->getParent()->getParent()->getLeft();
                assert(y != nullptr);
                if (y->getColor() == RED)
                {
                    assert(x->getParent() != nullptr);
                    x->getParent()->setColor(BLACK);
                    assert(y != nullptr);
                    y->setColor(BLACK);
                    x->getParent()->getParent()->setColor(RED);
                    x = x->getParent()->getParent();
                }
                else
                {
                    if (x == x->getParent()->getLeft())
                    {
                        x = x->getParent();
                        rotateRight(x);
                    }

                    assert(x->getParent() != nullptr);
                    x->getParent()->setColor(BLACK);
                    x->getParent()->getParent()->setColor(RED);
                    rotateLeft(x->getParent()->getParent());
                }
            }
        }
        assert(this->root != nullptr);
        this->root->setColor(BLACK);
    }

    template <class K>
    void RedBlackTree<K>::insert(K key)
    {
        Node<K> *x = new Node<K>(key, this->sentinel);
        Node<K> *y = this->sentinel;
        Node<K> *z = this->root;
        while (z != this->sentinel)
        {
            y = z;
            if (x->getKey() < z->getKey())
                z = z->getLeft();
            else
                z = z->getRight();
        }
        x->setParent(y);
        if (y == this->sentinel)
        {
            this->root = x;
        }
        else if (x->getKey() < y->getKey())
        {
            y->setLeft(x);
            this->leftSubtreeSizeIncrement(x->getParent());
        }
        else
        {
            y->setRight(x);
        }
        x->setLeft(this->sentinel);
        x->setRight(this->sentinel);
        x->setColor(RED);
        insertFixup(x);
    }

    template <class K>
    Node<K> *RedBlackTree<K>::successor(Node<K> *x)
    {
        if (x->getRight() != this->sentinel)
        {
            Node<K> *y = x->getRight();
            while (y->getLeft() != this->sentinel)
                y = y->getLeft();
            return y;
        }
        else
        {
            Node<K> *y = x->getParent();
            while (y != this->sentinel && x == y->getRight())
            {
                x = y;
                y = y->getParent();
            }
            return y;
        }
    }

    template <class K>
    void RedBlackTree<K>::removeFixup(Node<K> *x)
    {
        while (x != this->root && x->getColor() == BLACK)
        {
            if (x == x->getParent()->getLeft())
            {
                Node<K> *w = x->getParent()->getRight();
                assert(w != nullptr);
                if (w->getColor() == RED)
                {
                    assert(w != nullptr);
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    rotateLeft(x->getParent());
                    w = x->getParent()->getRight();
                }
                assert(w != this->sentinel);
                assert(w->getLeft() != nullptr);
                assert(w->getRight() != nullptr);
                if (w->getLeft()->getColor() == BLACK && w->getRight()->getColor() == BLACK)
                {
                    w->setColor(RED);
                    x = x->getParent();
                }
                else
                {
                    assert(w->getRight() != nullptr);
                    if (w->getRight()->getColor() == BLACK)
                    {
                        assert(w->getLeft() != nullptr);
                        w->getLeft()->setColor(BLACK);
                        w->setColor(RED);
                        rotateRight(w);
                        w = x->getParent()->getRight();
                    }

                    assert(w != nullptr);
                    assert(x->getParent() != nullptr);
                    w->setColor(x->getParent()->getColor());
                    assert(x->getParent() != nullptr);
                    x->getParent()->setColor(BLACK);
                    assert(w != this->sentinel);
                    assert(w->getRight() != nullptr);
                    w->getRight()->setColor(BLACK);
                    rotateLeft(x->getParent());
                    x = this->root;
                }
            }
            else
            {
                Node<K> *w = x->getParent()->getLeft();
                assert(w != nullptr);
                if (w->getColor() == RED)
                {
                    assert(w != nullptr);
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    rotateRight(x->getParent());
                    w = x->getParent()->getLeft();
                }
                assert(w->getLeft() != nullptr);
                assert(w->getRight() != nullptr);
                if (w->getRight()->getColor() == BLACK && w->getLeft()->getColor() == BLACK)
                {
                    w->setColor(RED);
                    x = x->getParent();
                }
                else
                {
                    assert(w->getLeft() != nullptr);
                    if (w->getLeft()->getColor() == BLACK)
                    {
                        assert(w->getRight() != nullptr);
                        w->getRight()->setColor(BLACK);
                        w->setColor(RED);
                        rotateLeft(w);
                        w = x->getParent()->getLeft();
                    }

                    assert(w != nullptr);
                    assert(x->getParent() != nullptr);
                    w->setColor(x->getParent()->getColor());
                    assert(x->getParent() != nullptr);
                    x->getParent()->setColor(BLACK);
                    assert(w->getLeft() != nullptr);
                    w->getLeft()->setColor(BLACK);
                    rotateRight(x->getParent());
                    x = this->root;
                }
            }
        }
        assert(x != nullptr);
        x->setColor(BLACK);
    }

    template <class K>
    Node<K> *RedBlackTree<K>::remove(K key)
    {
        Node<K> *z = search(key);
        if (z == nullptr)
            return nullptr;
        Node<K> *y, *x;
        if (z->getLeft() == this->sentinel || z->getRight() == this->sentinel)
        {
            y = z;
        }
        else
        {
            y = successor(z);
        }
        if (y->getParent() != this->sentinel && y->getParent()->getLeft() == y)
        {
            // have another unhandled case here
            this->leftSubtreeSizeDecrement(y->getParent());
        }
        if (y->getLeft() != this->sentinel)
        {
            x = y->getLeft();
        }
        else
        {
            x = y->getRight();
        }
        x->setParent(y->getParent());
        if (y->getParent() == this->sentinel)
        {
            this->root = x;
        }
        else if (y == y->getParent()->getLeft())
        {
            y->getParent()->setLeft(x);
        }
        else
        {
            y->getParent()->setRight(x);
        }
        if (y != z)
        {
            z->setKey(y->getKey());
        }
        assert(y != nullptr);
        if (y->getColor() == BLACK)
        {
            assert(x != this->sentinel);
            removeFixup(x);
        }
        return y;
    }

    template <class K>
    int RedBlackTree<K>::noOfKeysLessThan(K key)
    {
        Node<K> *x = this->root;
        int count = 0;
        while (x != this->sentinel)
        {
            if (x->getKey() < key)
            {
                count += x->getLeftSubtreeSize();
                x = x->getRight();
            }
            else
            {
                x = x->getLeft();
            }
        }
        return count;
    }

    template <class K>
    Node<K> *RedBlackTree<K>::search(K key)
    {
        Node<K> *x = this->root;
        while (x != this->sentinel)
        {
            if (x->getKey() == key)
                return x;
            else if (x->getKey() < key)
                x = x->getRight();
            else
                x = x->getLeft();
        }
        return nullptr;
    }
}

#endif
#ifndef HASH
#define HASH

#include <bits/stdc++.h>
using namespace std;

#define DELETED -1

enum probingType
{
    LINEAR = 0,
    QUADRATIC = 1,
    DOUBLE = 2,
};

class Node
{
    string key;
    int value;
    Node *next;

public:
    Node()
    {
        this->key = "";
        this->value = NULL;
        this->next = nullptr;
    }
    Node(string key, int value)
    {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }

    string getKey()
    {
        return key;
    }

    int getValue()
    {
        return value;
    }

    Node *getNext()
    {
        return next;
    }

    void setNext(Node *next)
    {
        this->next = next;
    }

    void setValue(int value)
    {
        this->value = value;
    }

    void setKey(string key)
    {
        this->key = key;
    }
};

Node nullNode = Node("", NULL);
Node deletedNode = Node("", DELETED);

class Hash
{
protected:
    int max_size, current_size;

public:
    virtual void insert(string key, int value) = 0;
    virtual int search(string key) = 0;
    virtual void remove(string key) = 0;
    double getLoadFactor();
    long long int polynomialHash(string key, long long int a, long long int mod);
};

double Hash::getLoadFactor()
{
    return (double)current_size / max_size;
}

long long int Hash::polynomialHash(string key, long long int a, long long int mod)
{
    long long int hash = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hash = (hash * a + key[i]) % mod;
    }
    return hash;
}

class OpenHash : public Hash
{
    int no_of_last_probes;
    int total_insertion_probe_count;
    int total_insertion_operation;
    const long long int hash_constant1 = 37, hash_constant2 = 41, quadratic_constant1 = 7, quadratic_constant2 = 11;
    probingType probing_type;
    Node *hash_table;

public:
    OpenHash(int max_size, probingType probing_type);
    ~OpenHash();
    void rehashDouble(int max_size);
    void insert(string key, int value);
    int search(string key);
    void remove(string key);
    void setProbingType(probingType probing_type);
    long long int auxillaryHash1(string key);
    long long int auxillaryHash2(string key);
    long long int linearProbedHash(string key, long long int i);
    long long int quadraticProbedHash(string key, long long int i);
    long long int doubleHash(string key, long long int i);
    int getNoOfLastProbes();
};

void OpenHash::rehashDouble(int flag)
{
    int max_size;
    if (flag == 0)
    {
        max_size = this->max_size / 2;
    }
    else if (flag == 1)
    {
        max_size = this->max_size * 2;
    }
    Node *new_hash_table = new Node[max_size];
    for (int i = 0; i < this->max_size; i++)
    {
        if (this->hash_table[i].getKey() != "")
        {
            int i = 0;
            long long int h = doubleHash(this->hash_table[i].getKey(), i);
            while (new_hash_table[h].getKey() != nullNode.getKey())
            {
                i++;
                h = doubleHash(this->hash_table[i].getKey(), i);
            }
            new_hash_table[h] = this->hash_table[i];
        }
    }
    this->hash_table = new_hash_table;
    this->max_size = max_size;
    this->total_insertion_operation = 0;
    this->total_insertion_probe_count = 0;
}

OpenHash::OpenHash(int max_size, probingType probing_type)
{
    this->max_size = max_size;
    this->probing_type = probing_type;
    this->current_size = 0;
    this->no_of_last_probes = 0;
    this->hash_table = new Node[max_size];
    this->total_insertion_operation = 0;
    this->total_insertion_probe_count = 0;
}

OpenHash::~OpenHash()
{
    delete[] hash_table;
}

void OpenHash::insert(string key, int value)
{
    if (this->current_size < this->max_size)
    {
        int i = 0;
        if (this->probing_type == LINEAR)
        {
            int h = this->linearProbedHash(key, i);
            while (this->hash_table[h].getKey() != nullNode.getKey() && this->hash_table[h].getKey() != deletedNode.getKey())
            {
                if (this->hash_table[h].getKey() == key)
                {
                    this->hash_table[h].setValue(value);
                    return;
                }
                i++;
                h = this->linearProbedHash(key, i);
            }
            this->hash_table[h] = Node(key, value);
        }
        else if (this->probing_type == QUADRATIC)
        {
            int h = this->quadraticProbedHash(key, i);
            while (this->hash_table[h].getKey() != nullNode.getKey() && this->hash_table[h].getKey() != deletedNode.getKey())
            {
                if (this->hash_table[h].getKey() == key)
                {
                    this->hash_table[h].setValue(value);
                    return;
                }
                i++;
                h = this->quadraticProbedHash(key, i);
            }
            this->hash_table[h] = Node(key, value);
        }
        else if (this->probing_type == DOUBLE)
        {
            int h = this->doubleHash(key, i);
            while (this->hash_table[h].getKey() != nullNode.getKey() && this->hash_table[h].getKey() != deletedNode.getKey())
            {
                if (this->hash_table[h].getKey() == key)
                {
                    this->hash_table[h].setValue(value);
                    return;
                }
                i++;
                h = this->doubleHash(key, i);
            }
            this->hash_table[h] = Node(key, value);
        }
        this->current_size++;
    }
}

int OpenHash::search(string key)
{
    int i = 0;
    if (this->probing_type == LINEAR)
    {
        while (this->hash_table[this->linearProbedHash(key, i)].getKey() != nullNode.getKey() && i < this->max_size)
        {
            if (this->hash_table[this->linearProbedHash(key, i)].getKey() == key)
            {
                this->no_of_last_probes = i + 1;
                return this->hash_table[this->linearProbedHash(key, i)].getValue();
            }
            i++;
        }
    }
    else if (this->probing_type == QUADRATIC)
    {
        while (this->hash_table[this->quadraticProbedHash(key, i)].getKey() != nullNode.getKey() && i < this->max_size)
        {
            if (this->hash_table[this->quadraticProbedHash(key, i)].getKey() == key)
            {
                this->no_of_last_probes = i + 1;
                return this->hash_table[this->quadraticProbedHash(key, i)].getValue();
            }
            i++;
        }
    }
    else if (this->probing_type == DOUBLE)
    {
        while (this->hash_table[this->doubleHash(key, i)].getKey() != nullNode.getKey() && i < this->max_size)
        {
            if (this->hash_table[this->doubleHash(key, i)].getKey() == key)
            {
                this->no_of_last_probes = i + 1;
                return this->hash_table[this->doubleHash(key, i)].getValue();
            }
            i++;
        }
    }
    this->no_of_last_probes = i;
    return nullNode.getValue();
}

void OpenHash::remove(string key)
{
    int i = 0;
    if (this->probing_type == LINEAR)
    {
        while (this->hash_table[this->linearProbedHash(key, i)].getKey() != nullNode.getKey() && i < this->max_size)
        {
            if (this->hash_table[this->linearProbedHash(key, i)].getKey() == key)
            {
                this->hash_table[this->linearProbedHash(key, i)] = deletedNode;
                this->current_size--;
                return;
            }
            i++;
        }
    }
    else if (this->probing_type == QUADRATIC)
    {
        while (this->hash_table[this->quadraticProbedHash(key, i)].getKey() != nullNode.getKey() && i < this->max_size)
        {
            if (this->hash_table[this->quadraticProbedHash(key, i)].getKey() == key)
            {
                this->hash_table[this->quadraticProbedHash(key, i)] = deletedNode;
                this->current_size--;
                return;
            }
            i++;
        }
    }
    else if (this->probing_type == DOUBLE)
    {
        while (this->hash_table[this->doubleHash(key, i)].getKey() != nullNode.getKey() && i < this->max_size)
        {
            if (this->hash_table[this->doubleHash(key, i)].getKey() == key)
            {
                this->hash_table[this->doubleHash(key, i)] = deletedNode;
                this->current_size--;
                return;
            }
            i++;
        }
    }
}

void OpenHash::setProbingType(probingType type)
{
    this->probing_type = type;
}

long long int OpenHash::auxillaryHash1(string key)
{
    return this->polynomialHash(key, this->hash_constant1, this->max_size);
}

long long int OpenHash::auxillaryHash2(string key)
{
    return this->polynomialHash(key, this->hash_constant2, this->max_size - 1) + 1;
}

long long int OpenHash::linearProbedHash(string key, long long int i)
{
    return (auxillaryHash1(key) + i) % this->max_size;
}

long long int OpenHash::quadraticProbedHash(string key, long long int i)
{
    return (auxillaryHash1(key) + quadratic_constant1 * i + quadratic_constant2 * i * i) % this->max_size;
}

long long int OpenHash::doubleHash(string key, long long int i)
{
    return (auxillaryHash1(key) + i * auxillaryHash2(key)) % this->max_size;
}

// returns the number of probes required to find the key in the hash table(only for search)
int OpenHash::getNoOfLastProbes()
{
    return this->no_of_last_probes;
}

class ChainedHash : public Hash
{
    const long long int hash_constant = 41;
    Node **hash_table;

public:
    ChainedHash(int max_size);
    ~ChainedHash();
    void insert(string key, int value);
    int search(string key);
    void remove(string key);
};

ChainedHash::ChainedHash(int max_size)
{
    this->max_size = max_size;
    this->current_size = 0;
    this->hash_table = new Node *[max_size];
    for (int i = 0; i < this->max_size; i++)
    {
        this->hash_table[i] = nullptr;
    }
}

ChainedHash::~ChainedHash()
{
    delete[] hash_table;
}

void ChainedHash::insert(string key, int value)
{
    int i = this->polynomialHash(key, this->hash_constant, this->max_size);
    if (this->hash_table[i] == nullptr)
    {
        this->hash_table[i] = new Node(key, value);
    }
    else
    {
        Node *temp = this->hash_table[i];
        while (temp->getNext() != nullptr)
        {
            if (temp->getKey() == key)
            {
                temp->setValue(value);
                return;
            }
            temp = temp->getNext();
        }
        if (temp->getKey() == key)
        {
            temp->setValue(value);
            return;
        }
        temp->setNext(new Node(key, value));
    }
    this->current_size++;
}

int ChainedHash::search(string key)
{
    int i = this->polynomialHash(key, this->hash_constant, this->max_size);
    if (this->hash_table[i] == nullptr)
    {
        return nullNode.getValue();
    }
    else
    {
        Node *temp = this->hash_table[i];
        while (true)
        {
            if (temp->getKey() == key)
            {
                return temp->getValue();
            }
            if (temp->getNext() == nullptr)
            {
                return nullNode.getValue();
            }
            temp = temp->getNext();
        }
    }
}

void ChainedHash::remove(string key)
{
    int i = this->polynomialHash(key, this->hash_constant, this->max_size);
    if (this->hash_table[i] == nullptr)
    {
        return;
    }
    else
    {
        Node *temp = this->hash_table[i];
        if (temp->getKey() == key)
        {
            this->hash_table[i] = temp->getNext();
            delete temp;
            this->current_size--;
            return;
        }
        while (temp->getNext() != nullptr)
        {
            if (temp->getNext()->getKey() == key)
            {
                Node *temp2 = temp->getNext();
                temp->setNext(temp->getNext()->getNext());
                delete temp2;
                this->current_size--;
                return;
            }
            temp = temp->getNext();
        }
    }
}

#endif
#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <utility>
#include <map>    
#include <algorithm>

using namespace std;

class vertex
{
public:
    string value;
    int id;
    int capactity;
    int val;
    vertex(string value, int id)
    {
        this->value = value;
        this->id = id;
    }
};

class edge
{
public:
    int weight;
    int id;
    vertex *from;
    vertex *to;
    int capacity;
    int flow;
    edge(int w, vertex *f, vertex *t)
    {
        this->weight = w;
        this->from = f;
        this->to = t;
    }
};

class SNode // nodes used in stacks and queues
{
public:
    vertex *val; // store nodes used in trees as values, which in turn have string values
    SNode *next;
    SNode *prev;
    SNode(vertex *val)
    {
        this->val = val;
        this->next = NULL;
    }
};

class Queue
{
private:
    struct SNode
    {
        vertex *val;
        SNode *next;
        SNode *prev;

        SNode(vertex *value) : val(value), next(nullptr), prev(nullptr) {}
    };

    SNode *front;
    SNode *back;
    bool empty;

public:
    Queue() : front(nullptr), back(nullptr), empty(true) {}

    bool isEmpty() const
    {
        return empty;
    }

    void enqueue(vertex *value)
    {
        SNode *newNode = new SNode(value);
        if (isEmpty())
        {
            front = back = newNode;
            empty = false;
        }
        else
        {
            newNode->next = back;
            back->prev = newNode;
            back = newNode;
        }
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << endl
                 << "Error: Dequeueing empty queue" << endl;
            return;
        }

        SNode *temp = front;
        front = front->prev;

        if (front == nullptr)
        {
            back = nullptr;
            empty = true;
        }
        else
        {
            front->next = nullptr;
        }

        delete temp;
    }

    vertex *peek()
    {
        if (isEmpty())
        {
            cout << endl
                 << "Error: Peeking empty queue" << endl;
            return nullptr;
        }
        return front->val;
    }

    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }
};

class Stack
{
private:
    int max_size = 10;
    SNode *head = NULL; // treat head as top of StringStack and prepends

public:
    Stack(int size)
    {
        this->max_size = size;
        this->head = NULL;
    }

    bool isEmpty()
    {

        return this->head == NULL;
    }
    void pop()
    {
        if (this->isEmpty())
        {
            cout << endl
                 << "error popping from empty StringStack" << endl;
            return;
        }
        SNode *oldHead = this->head;
        if (oldHead->next != NULL)
        {
            SNode *newHead = this->head->next;
            this->head = newHead;
        }
        else
        {
            this->head = NULL;
        }
        delete[] oldHead;

        return;
    }
    ~Stack()
    {
        while (!isEmpty())
        {
            this->pop();
        }
        delete[] this;
    }

    void push(vertex *value) // basically a prepend?
    {

        SNode *newDNode = new SNode(value);
        newDNode->next = this->head;
        this->head = newDNode;
        return;
    }

    vertex *peek()
    {
        if (this->isEmpty())
        {
            cout << endl
                 << "error peeking empty StringStack" << endl;
            return NULL;
        }
        return this->head->val;
    }
};
#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <limits>


using namespace std;

#include <random>
class INode
{
public:
    int val;
    INode *next;
    INode *prev;
    INode(int val)
    {
        this->val = val;
        this->next = NULL;
    }
};



class Queue
{
private:
    DNode *front;
    DNode *back;

public:
    Queue()
    {
        this->front = NULL;
        this->back = NULL;
    }

    bool isEmpty()
    {
        return this->front == NULL;
    }

    void enqueue(int value)
    {
        if (isEmpty())
        {
            front = new DNode(value);
        }
        else
        {
            DNode *newDNode = new DNode(value);
            if (back == NULL)
            { // back doesnt exist
                this->front->prev = newDNode;
                newDNode->next = this->front;
            }
            else
            { // back exists
                this->back->prev = newDNode;
                newDNode->next = this->back;
            }
            this->back = newDNode;
        }
    }

    int dequeue()
    {
        if (isEmpty())
        {
            cout << endl
                 << "error dequeueing empty queue" << endl;
            return INT64_MAX;
        }
        else
        {
            int val = this->front->val;
            if (this->back != NULL)
            {
                this->front = this->front->prev;
                delete[] this->front->next;
                this->front->next = NULL;
            }
            else
            {
                delete[] this->front;
                this->front = NULL;
            }
            return val;
        }
    }

    int peek()
    {
        if (this->isEmpty())
        {
            cout << endl
                 << "error peeking empty queue" << endl;
            return INT64_MAX;
        }
        return this->front->val;
    }

    ~Queue()
    {

        while (!this->isEmpty())
        {
            DNode *k = this->front;
            this->dequeue();
            delete[] k;
        }

        delete[] this;
    }
};
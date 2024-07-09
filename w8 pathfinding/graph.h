#include <list>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <utility>
#include <map>
#include <algorithm>
#include <random>
#include <iostream>
#include "dataStructures.h"

using namespace std;

// Modified
int getRandomNumber(int lower, int upper)
{
    // from C++11 - more reliable than the older C-style srand() function:
    random_device rd;                                         // obtain a random seed from the hardware
    mt19937 eng(rd());                                        // Standard Mersenne Twister engine seeded with rd()
    uniform_int_distribution<int> distribution(lower, upper); // distribution from lower to upper bound that are passed in

    int randomNumber = distribution(eng); // generate random number

    return randomNumber;
}


class pNode{
    public:
    vertex*v;
    pNode*p;

    pNode(vertex*v){
        this->v = v;
    }
};

class graph
{
public:
    int maxVertexAmount;
    int lastVertexIndex = -1;
    vertex **vertices;
    edge ***edges;

    graph(int n)
    {
        this->maxVertexAmount = n;

        this->vertices = (vertex **)malloc(sizeof(vertex *) * this->maxVertexAmount);

        this->edges = (edge ***)malloc(sizeof(edge **) * this->maxVertexAmount);
        for (int i = 0; i < this->maxVertexAmount; i++)
        {
            this->edges[i] = (edge **)malloc(sizeof(edge *) * this->maxVertexAmount);

            for (int j = 0; j < this->maxVertexAmount; j++)
            {
                this->edges[i][j] = NULL;
            }
        }
    }

    bool isVisited(vector<string> *visited, vertex *v)
    {
        return count(visited->begin(), visited->end(), v->value) != 0;
    }

    // returns where the vertex is in the array of vertices using vertex id
    int VI(int id)
    {

        if (this->lastVertexIndex > -1)
        {
            for (int i = 0; i <= this->lastVertexIndex; i++)
            {
                if (this->vertices[i]->id == id)
                {
                    return i;
                }
            }
            return -1; // as an error value
        }
    }

    void insertVertex(string value)
    {

        if (this->lastVertexIndex < (this->maxVertexAmount - 1))
        {
            this->lastVertexIndex++;
            int id = getRandomNumber(1000000, 9999999); // almost 1 in a billion chance of id collision is acceptable
            vertex *v = new vertex(value, id);

            this->vertices[this->lastVertexIndex] = v;
            this->edges[lastVertexIndex][lastVertexIndex] = NULL;
        }
    }

    void connectVertices(vertex *v1, vertex *v2, bool direction, int length)
    {

        if (v1 != NULL && v2 != NULL)
        {
            // direction true means 1->2 direction false means 2->1

            int index1 = this->VI(v1->id);
            int index2 = this->VI(v2->id);

            edge *e;

            if (direction)
            {
                e = new edge(length, v1, v2);

                this->edges[index1][index2] = e;
            }
            else
            {
                e = new edge(length, v2, v1);
                this->edges[index2][index1] = e;
            }
        }
    }

    void displayAdjacency()
    {
        int i = 0, j = 0, k = 0;
        cout << endl
             << "  ";
        for (k; k <= this->lastVertexIndex; k++)
        {
            cout << this->vertices[k]->value << " ";
        }
        for (i; i <= this->lastVertexIndex; i++)
        {
            cout << endl
                 << this->vertices[i]->value << " ";
            j = 0;
            for (j; j <= this->lastVertexIndex; j++)
            {
                if (this->edges[i][j] != NULL)
                {
                    cout << (this->edges[i][j]->weight) << " ";
                }
                else
                {
                    cout << "  ";
                }
            }
        }
    }

    vertex *getVertexByValue(string val)
    {
        if (this->lastVertexIndex > -1)
        {
            for (int i = 0; i <= this->lastVertexIndex; i++)
            {
                if (this->vertices[i]->value == val)
                {
                    return this->vertices[i];
                }
            }
            return NULL; // as an error value
        }
    }

    vector<vertex *> getChildren(vertex *v)
    {
        int index = this->VI(v->id);

        vector<vertex *> vec;
        bool allNull = true;
        for (int i = 0; i <= this->lastVertexIndex; i++)
        {
            if (this->edges[index][i] != NULL)
            {
                vec.push_back(this->vertices[i]);
            }
        }

        return vec;
    }

    void DFS(vertex *start)
    {

        if (start != NULL)
        {
            Stack *s = new Stack(this->maxVertexAmount);

            vector<string> visited;
            cout << endl;
            s->push(start);
            visited.push_back(start->value);

            while (s->isEmpty() == false)
            {
                vertex *n = s->peek();
                cout << n->value << "->";
                s->pop();

                vector<vertex *> children = this->getChildren(n);
                if (children.empty() == false)
                {

                    for (vertex *v : children)
                    {
                        if (!isVisited(&visited, v))
                        {
                            s->push(v);
                            visited.push_back(v->value);
                        }
                    }
                }
            }
        }
    }

    void BFS(vertex *start)
    {

        if (start != NULL)
        {
            Queue *q = new Queue();
            vector<string> visited;
            cout << endl;

            q->enqueue(start);

            visited.push_back(start->value);

            while (q->isEmpty() == false)
            {
                vertex *n = q->peek();
                cout << n->value << "->";
                q->dequeue();

                vector<vertex *> children = this->getChildren(n);

                if (children.empty() == false)
                {
                    for (vertex *v : children)
                    {
                        if (!isVisited(&visited, v))
                        {
                            q->enqueue(v);
                            visited.push_back(v->value);
                        }
                    }
                }
            }
        }
    }


    pNode*findAugmentedPath(vertex*start, vertex*sink){


        if (start != NULL && sink!=NULL)
        {
            Queue *q = new Queue();
            vector<string> visited;

            q->enqueue(start);
            pNode*en = new pNode(start);
            pNode*ex = en;
            visited.push_back(start->value);

            while (q->isEmpty() == false)
            {
                vertex *n = q->peek();
                pNode* a = new pNode(n);
                ex->p = a;
                ex = a;
                cout << n->value << "->";
                if(n->val == sink->val){
                    return ex;
                }
                q->dequeue();

                vector<vertex *> children = this->getChildren(n);

                if (children.empty() == false)
                {
                    for (vertex *v : children)
                    {
                        if (!isVisited(&visited, v))
                        {
                            q->enqueue(v);
                            visited.push_back(v->value);
                        }
                    }
                }
            }

            return en;
        }



    }

    bool BFS_AugmentedPath(vertex *start, vertex*end, int parent[])
    {

        if (start != NULL)
        {
            Queue *q = new Queue();
            vector<string> visited;
            cout << endl;

            q->enqueue(start);

            visited.push_back(start->value);

            while (q->isEmpty() == false)
            {
                vertex *n = q->peek();
                cout << n->value << "->";
                q->dequeue();

                vector<vertex *> children = this->getChildren(n);

                if (children.empty() == false)
                {
                    for (vertex *v : children)
                    {
                        if (!isVisited(&visited, v))
                        {
                            q->enqueue(v);
                            visited.push_back(v->value);
                        }
                    }
                }
            }
        }
    }

    void recursiveTopologicalSort(vertex *n, vector<string> *visited, Stack *s)
    {
        visited->push_back(n->value);
        vector<vertex *> children = this->getChildren(n);

        for (vertex *v : children)
        {
            if (!isVisited(visited, v))
            {
                recursiveTopologicalSort(v, visited, s);
            }
        }
        s->push(n);
    }

    void topologicalSort()
    {
        Stack *s = new Stack(500);

        vector<string> visited;
        int i = 0;
        for (i; i <= this->lastVertexIndex; i++)
        {
            vertex *v = this->vertices[i];
            if (!isVisited(&visited, v))
            {
                recursiveTopologicalSort(this->vertices[i], &visited, s);
            }
        }
        while (s->isEmpty() == false)
        {
            cout << s->peek()->value << "->";
            s->pop();
        }
    }
};

class refVertex
{
public:
    string val;
    int id;
    vector<int> followingIds;

    refVertex(string val, int id)
    {
        this->val = val;
        this->id = id;
    }

    void linkVertex(int newId)
    {
        this->followingIds.push_back(newId);
    }
};
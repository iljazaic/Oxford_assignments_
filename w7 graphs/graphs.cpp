#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <utility> // For std::pair
#include <map>     // for dictionary like behaviour
#include <algorithm>

/* README
 *  In this week, we'll look at Graphs: directed and undirected, weighted and unweighted.
 *  We'll also apply the BFS and DFS algorithms and make adaptions.
 *  We'll set up classes to represent these using indexed structures and referenced structures.
 *
 */

using namespace std;

#include <random>

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

class vertex
{
public:
    string value;
    int id;
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

    bool isVisited(vector<string>*visited, vertex*v){
        return count(visited->begin(), visited->end(), v->value)!=0;
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

    void recursiveTopologicalSort(vertex*n, vector<string>* visited, Stack *s)
    {
        visited->push_back(n->value);
        vector<vertex *> children = this->getChildren(n);

        for(vertex*v : children){
            if(!isVisited(visited, v)){
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
        while(s->isEmpty()==false){
            cout<<s->peek()->value<<"->";
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

class refGraph
{
public:
    int maxVertexAmount;
    int lastVertexIndex = -1;
    refVertex **vertices;

    refGraph(int n)
    {
        this->maxVertexAmount = n;

        this->vertices = (refVertex **)malloc(sizeof(refVertex *) * n);
    }

    void insertVertex(string value)
    {
        if (this->lastVertexIndex < (this->maxVertexAmount - 1))
        {
            this->lastVertexIndex++;
            int id = getRandomNumber(1000000, 9999999); // almost 1 in a billion chance of id collision is acceptable
            refVertex *v = new refVertex(value, id);

            this->vertices[this->lastVertexIndex] = v;
        }
    }

    // returns where the vertex is in the array of vertices using vertex id so same names dont cause issues
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

    void connectVertices(refVertex *v1, refVertex *v2, bool direction)
    {

        int index1 = this->VI(v1->id);
        int index2 = this->VI(v2->id);

        if (direction == true)
        {
            this->vertices[index1]->linkVertex(v2->id);
        }
        if (direction == false)
        {
            this->vertices[index2]->linkVertex(v1->id);
        }
    }

    void displayAdjList()
    {

        int i = 0, j = 0;

        for (i = 0; i <= this->lastVertexIndex; i++)
        {
            cout << endl
                 << this->vertices[i]->val << "-->";
            for (int id : this->vertices[i]->followingIds)
            {
                cout << this->vertices[this->VI(id)]->val << "->";
            }
            cout << ";";
        }
    }

    refVertex *getVertexByValue(string value)
    {
        for (int i = 0; i <= this->lastVertexIndex; i++)
        {
            if (this->vertices[i]->val == value)
            {
                return this->vertices[i];
            }
        }
    }
};

int main()
{
    cout << "C++ DS&A Graphs\n"
         << endl;

    // Ex 1 - Set up a Graph and connect vertices together with a matrix and add edges
    cout << "Exercise 1: Complete the Graph class with a indexed structure" << endl;

    graph *g = new graph(10);

    g->insertVertex("A");
    g->insertVertex("B");
    g->insertVertex("C");
    g->insertVertex("D");
    g->insertVertex("E");
    g->insertVertex("F");
    g->insertVertex("G");

    g->connectVertices(g->getVertexByValue("A"), g->getVertexByValue("B"), true, getRandomNumber(1, 9));
    g->connectVertices(g->getVertexByValue("E"), g->getVertexByValue("G"), true, getRandomNumber(1, 9));
    g->connectVertices(g->getVertexByValue("D"), g->getVertexByValue("A"), true, getRandomNumber(1, 9));
    g->connectVertices(g->getVertexByValue("F"), g->getVertexByValue("C"), true, getRandomNumber(1, 9));
    g->connectVertices(g->getVertexByValue("E"), g->getVertexByValue("C"), true, getRandomNumber(1, 9));
    g->connectVertices(g->getVertexByValue("B"), g->getVertexByValue("F"), true, getRandomNumber(1, 9));

    cout << endl
         << "Adjacency matrix for indexed graph: " << endl;
    g->displayAdjacency();

    cout << endl
         << "ENTER TO CONTINUE";
    getchar();
    // Ex 2 - Set up a Graph and connect vertcies (nodes) together with a referenced structure
    cout << "Exercise 2: Complete the Graph class with a referenced structure" << endl;

    refGraph *rg = new refGraph(10);

    rg->insertVertex("A");
    rg->insertVertex("B");
    rg->insertVertex("C");
    rg->insertVertex("D");
    rg->insertVertex("E");
    rg->insertVertex("F");
    rg->insertVertex("G");

    rg->connectVertices(rg->getVertexByValue("A"), rg->getVertexByValue("B"), false);
    rg->connectVertices(rg->getVertexByValue("E"), rg->getVertexByValue("G"), true);
    rg->connectVertices(rg->getVertexByValue("D"), rg->getVertexByValue("A"), true);
    rg->connectVertices(rg->getVertexByValue("F"), rg->getVertexByValue("C"), true);
    rg->connectVertices(rg->getVertexByValue("E"), rg->getVertexByValue("C"), true);
    rg->connectVertices(rg->getVertexByValue("B"), rg->getVertexByValue("F"), true);

    rg->displayAdjList();
    cout << endl
         << "ENTER TO CONTINUE";
    getchar();
    // Ex 3 - DFS.
    cout << "\nExercise 3: Depth-First Search of a Graph" << endl;
    // Refactor your DFS function from 06 Trees (if previously completed)

    cout << endl
         << "performing DFS on graph used in ex. 1" << endl;

    g->DFS(g->getVertexByValue("A"));
    cout << endl
         << "ENTER TO CONTINUE";
    getchar();
    // Ex 4 - BFS
    cout << "\nExercise 4: Breadth-First Search of a Graph " << endl;

    cout << "performing BFS on graph used in ex. 1";

    g->BFS(g->getVertexByValue("A"));

    cout << endl
         << "ENTER TO CONTINUE";

    getchar();
    // Refactor your BFS function from 06 Trees (if previously completed)

    // Ex 5 - Topological Sort
    cout << "\nExercise 5: Topological Sort" << endl;
    cout<<endl<<"performing topological sort on graph used in ex. 1"<<endl;
    g->topologicalSort();

    getchar();

    return 0;
}

/*
 * Exercise 1: Implement a Graph class with a indexed structure
 * Create a Graph class and model the adjacent vertices as a matrix (e.g. a 2D array).
 * This matrix should hold the weights (the edges) for the connections between vertices.
 * In main, instantiate a Graph object, add vertices, and connect these together with edges.
 *
 * Write a print/display method and check that you can visualise the adjacency matrix.
 * Below is a sample output to give you an example of the vertices (A-E) and their edge connections:
 *
 *   A B C D E
 * A 0 1 0 0 7
 * B 0 4 0 7 0
 * C 2 0 5 0 0
 * D 0 0 0 9 0
 * E 0 4 0 8 0
 *
 */

/*
 * Exercise 2: Implement a Graph with a referenced structure
 * Now implement a Graph that uses an adjacency list, rather than a matrix.
 * You could model the connections from each vertex as individual lists.
 * You could build the edge weights into the nodes of each list, as these would individual to each connection.
 * You could use your LinkedList class from previous exercises
 * or select an appropriate STL structure - a pair, list, map or other.
 *
 * Set up a new Graph, with vertices and edges and check these are stored correctly in the adjacency list.
 * Create a print / display method to check.
 *
 */

/*
 * Exercise 3: DFS using a Stack
 *
 * Either refactor the DFS function you used for your 06 Tree exercise sheet,
 * or write a DFS function that will search the depth of the connections
 * from a starting node/vertex in the graph.
 *
 * Extension 1: If you already have a working DFS using your user-defined Stack class
 *               from previous weeks, why not refactor this to use the STL's stack?
 * Extension 2: Can you use DFS to detect whether there is a cycle in the graph?
 */

/*
 * Exercise 4: BFS using a Queue
 *
 * Either refactor the BFS function you used for your 06 Tree exercise sheet,
 * or write a BFS function that will search the breadth of the connections
 * from a starting node/vertex in the graph.
 *
 * Note: In 08 Path Finding, we will use BFS in Dijkstra's algorithm for unweighted graphs.
 *       Therefore, it's helpful to check this functions works ahead of then.
 *
 */

/*
 * Exercise 5: Topological Sort
 * Topological Sort orders vertices so that each node/vertex appears only after all the nodes pointing to it have appeared.
 * Apply your DFS algorithm, in combination with a structure to print nodes of graph by these rules.
 * This could be done via a vector or a hash table / unordered_map.
 *
 * Example: For a graph with 4 nodes and these relations: a->b, a->c, b->d, c->d,
 *          there are two acceptable topological sorts: a, b, c, d and a, c, b, d.
 *
 * Note: Topological Sort is not feasible in graphs that have a cycle.
 *       Therefore, it is helpful to first detect whether a graph has a cycle.
 *       If you've already completed the extension for exercise 3 (DFS), feel free to reuse this here.
 *
 */

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include "graph.h"

#define INF numeric_limits<int>::max()

/* README
 *  This week we continue with Graphs and explore path finding algorithms.
 *  We explore Dijkstra's algorithm, Bellman-Ford's algorithm, the A* algorithm
 *  as well as algorihms such as Ford-Fulkerson and Edmonds-Karp that can be applied to Network Flow problems.
 *
 *  I've written the exercise descriptions for you to implement how you choose.
 *
 */

using namespace std;
#include <random>

bool emptyArray(vertex **a, int l)
{
    for (int i = 0; i <= l; i++)
    {

        if (a[i]->id != -1)
        {
            return false;
        }
    }
    return true;
}

int getIndexOfMin(int *d, int l)
{
    int minVal = INF;
    int minIndex = -1;

    for (int i = 0; i < l; i++)
    {
        if (minVal > d[i])
        {
            minIndex = i;
        }
    }

    return minIndex;
}

void dijkstra(graph *g, vertex *start, vertex *end)
{
    unordered_map<int, int> dist;
    unordered_map<int, vertex *> prev;
    priority_queue<pair<int, vertex *>, vector<pair<int, vertex *>>, greater<pair<int, vertex *>>> pq;

    for (int i = 0; i <= g->lastVertexIndex; i++)
    {
        dist[g->vertices[i]->id] = numeric_limits<int>::max();
        prev[g->vertices[i]->id] = nullptr;
    }

    dist[start->id] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        vertex *u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (u == end)
            break;

        if (d > dist[u->id])
            continue;

        int uIndex = g->VI(u->id);
        for (int i = 0; i <= g->lastVertexIndex; i++)
        {
            if (g->edges[uIndex][i] != nullptr)
            {
                vertex *v = g->vertices[i];
                int weight = g->edges[uIndex][i]->weight;
                int newDist = dist[u->id] + weight;

                if (newDist < dist[v->id])
                {
                    dist[v->id] = newDist;
                    prev[v->id] = u;
                    pq.push({newDist, v});
                }
            }
        }
    }

    if (prev[end->id] == nullptr)
    {
        cout << "No path exists from " << start->value << " to " << end->value << endl;
        return;
    }

    vector<vertex *> path;
    for (vertex *v = end; v != nullptr; v = prev[v->id])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << "Shortest path from " << start->value << " to " << end->value << ":" << endl;
    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i]->value;
        if (i < path.size() - 1)
            cout << " -> ";
    }
    cout << "\nTotal distance: " << dist[end->id] << endl;
}

void dijkstraMap(graph *g, vertex *start)
{
    unordered_map<int, int> dist;
    priority_queue<pair<int, vertex *>, vector<pair<int, vertex *>>, greater<pair<int, vertex *>>> pq;

    for (int i = 0; i <= g->lastVertexIndex; i++)
    {
        dist[g->vertices[i]->id] = numeric_limits<int>::max();
    }

    dist[start->id] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        vertex *u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u->id])
            continue; // Skip if we've found a better path

        int uIndex = g->VI(u->id);
        for (int i = 0; i <= g->lastVertexIndex; i++)
        {
            if (g->edges[uIndex][i] != nullptr)
            {
                vertex *v = g->vertices[i];
                int weight = g->edges[uIndex][i]->weight;
                int newDist = dist[u->id] + weight;

                if (newDist < dist[v->id])
                {
                    dist[v->id] = newDist;
                    pq.push({newDist, v});
                }
            }
        }
    }
    cout << "Shortest paths from " << start->value << ":" << endl;
    for (int i = 0; i <= g->lastVertexIndex; i++)
    {
        vertex *v = g->vertices[i];
        cout << v->value << " : ";
        if (dist[v->id] == numeric_limits<int>::max())
        {
            cout << "Infinity";
        }
        else
        {
            cout << dist[v->id];
        }
        cout << endl;
    }
}

void bellmanFord(graph *g, vertex *start)
{
    vector<int> dist(g->maxVertexAmount, numeric_limits<int>::max());
    vector<vertex *> prev(g->maxVertexAmount, nullptr);

    int startIndex = g->VI(start->id);
    dist[startIndex] = 0;

    // Relax edges |V| - 1 times
    for (int i = 0; i < g->lastVertexIndex; i++)
    {
        for (int u = 0; u <= g->lastVertexIndex; u++)
        {
            for (int v = 0; v <= g->lastVertexIndex; v++)
            {
                if (g->edges[u][v] != nullptr)
                {
                    int weight = g->edges[u][v]->weight;
                    if (dist[u] != numeric_limits<int>::max() &&
                        dist[u] + weight < dist[v])
                    {
                        dist[v] = dist[u] + weight;
                        prev[v] = g->vertices[u];
                    }
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u <= g->lastVertexIndex; u++)
    {
        for (int v = 0; v <= g->lastVertexIndex; v++)
        {
            if (g->edges[u][v] != nullptr)
            {
                int weight = g->edges[u][v]->weight;
                if (dist[u] != numeric_limits<int>::max() &&
                    dist[u] + weight < dist[v])
                {
                    cout << "Graph contains a negative-weight cycle" << endl;
                    return;
                }
            }
        }
    }

    // Print the results
    cout << "Shortest distances from " << start->value << ":" << endl;
    for (int i = 0; i <= g->lastVertexIndex; i++)
    {
        cout << g->vertices[i]->value << " : ";
        if (dist[i] == numeric_limits<int>::max())
        {
            cout << "Infinity";
        }
        else
        {
            cout << dist[i];
        }
        cout << endl;
    }

    // Optionally, print paths
    cout << "\nShortest paths:" << endl;
    for (int i = 0; i <= g->lastVertexIndex; i++)
    {
        if (i != startIndex)
        {
            vector<vertex *> path;
            for (vertex *v = g->vertices[i]; v != nullptr; v = prev[g->VI(v->id)])
            {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());

            cout << start->value << " to " << g->vertices[i]->value << ": ";
            if (path[0] != start)
            {
                cout << "No path" << endl;
            }
            else
            {
                for (size_t j = 0; j < path.size(); j++)
                {
                    cout << path[j]->value;
                    if (j < path.size() - 1)
                        cout << " -> ";
                }
                cout << endl;
            }
        }
    }
}

class node
{
public:
    int x;
    int y;
    int g = 0;
    int f = 999;
    int h = 0;
    node *parent = nullptr;

    node(int x, int y) : x(x), y(y) {}

    bool operator==(const node &other) const
    {
        return x == other.x && y == other.y;
    }
};

node *minfInQ(vector<node *> &v)
{
    if (v.empty())
        return nullptr;

    return *min_element(v.begin(), v.end(), [](const node *a, const node *b)
                        { return a->f < b->f; });
}

vector<node *> getNeighborsOfNode(node *n, int mapx, int mapy)
{
    vector<node *> tr;
    if (n->x > 0)
        tr.push_back(new node(n->x - 1, n->y));
    if (n->x < mapx)
        tr.push_back(new node(n->x + 1, n->y));
    if (n->y > 0)
        tr.push_back(new node(n->x, n->y - 1));
    if (n->y < mapy)
        tr.push_back(new node(n->x, n->y + 1));
    return tr;
}

int euclideanDistance(const node *n1, const node *n2)
{
    return sqrt(pow(n2->x - n1->x, 2) + pow(n2->y - n1->y, 2));
}

void reconstructPath(node *n)
{
    while (n != nullptr)
    {
        cout << "(" << n->x << " ; " << n->y << ")<-";
        n = n->parent;
    }
}

void aStar(int **map, int startX, int startY, int endX, int endY, int mapsize)
{
    vector<node *> open_list;
    vector<node *> closed_list;
    node *start = new node(startX, startY);
    node *end = new node(endX, endY);
    start->g = 0;
    start->h = euclideanDistance(start, end);
    start->f = start->g + start->h;
    open_list.push_back(start);

    while (!open_list.empty())
    {
        node *current = minfInQ(open_list);
        if (*current == *end)
        {
            reconstructPath(current);
            for (auto n : open_list)
            {
                delete n;
            }
            for (auto n : closed_list)
            {
                delete n;
            };
            return;
        }

        open_list.erase(remove(open_list.begin(), open_list.end(), current), open_list.end());
        closed_list.push_back(current);

        vector<node *> neighbors = getNeighborsOfNode(current, mapsize - 1, mapsize - 1);
        for (node *neighbor : neighbors)
        {
            if (map[neighbor->y][neighbor->x] == 1 || find_if(closed_list.begin(), closed_list.end(), [&](const node *n){ return *n == *neighbor; }) != closed_list.end())//borrowed from https://en.cppreference.com/w/cpp/algorithm/find
            {
                delete neighbor;
                continue;
            }
            int tentative_g = current->g + 1;

            auto it = find_if(open_list.begin(), open_list.end(), [&](const node *n){ return *n == *neighbor; });
            if (it == open_list.end() || tentative_g < neighbor->g)
            {
                neighbor->parent = current;
                neighbor->g = tentative_g;
                neighbor->h = euclideanDistance(neighbor, end);
                neighbor->f = neighbor->g + neighbor->h;

                if (it == open_list.end())
                {
                    open_list.push_back(neighbor);
                }
            }
            else
            {
                delete neighbor;
            }
        }
    }

    cout << "NO PATH FOUND" << endl;
    for (auto n : open_list)
    {
        delete n;
    }
    for (auto n : closed_list)
    {
        delete n;
    }
}




vector<vertex*> findAugmentingPath(graph* residualGraph, vertex* source, vertex* sink) {
    int V = residualGraph->maxVertexAmount;
    vector<vertex*> parent(V, nullptr);
    vector<bool> visited(V, false);

    queue<vertex*> q;
    q.push(source);
    visited[residualGraph->VI(source->id)] = true;

    cout << "Starting BFS from source " << source->value << endl;

    while (!q.empty()) {
        vertex* u = q.front();
        q.pop();

        cout << "Visiting vertex " << u->value << endl;

        for (int v = 0; v <= residualGraph->lastVertexIndex; v++) {
            if (!visited[v] && residualGraph->edges[residualGraph->VI(u->id)][v] != nullptr) {
                int residualCapacity = residualGraph->edges[residualGraph->VI(u->id)][v]->weight - 
                                       residualGraph->edges[residualGraph->VI(u->id)][v]->flow;
                
                cout << "  Checking edge " << u->value << " -> " << residualGraph->vertices[v]->value 
                     << " (capacity: " << residualGraph->edges[residualGraph->VI(u->id)][v]->weight 
                     << ", flow: " << residualGraph->edges[residualGraph->VI(u->id)][v]->flow 
                     << ", residual: " << residualCapacity << ")" << endl;

                if (residualCapacity > 0) {
                    q.push(residualGraph->vertices[v]);
                    parent[v] = u;
                    visited[v] = true;

                    cout << "    Added " << residualGraph->vertices[v]->value << " to queue" << endl;

                    if (residualGraph->vertices[v] == sink) {
                        cout << "Found path to sink!" << endl;
                        // Construct the path
                        vector<vertex*> path;
                        for (vertex* v = sink; v != nullptr; v = parent[residualGraph->VI(v->id)]) {
                            path.push_back(v);
                        }
                        reverse(path.begin(), path.end());
                        return path;
                    }
                }
            }
        }
    }

    cout << "No augmenting path found from " << source->value << " to " << sink->value << endl;
    return vector<vertex*>(); // Return empty path if no augmenting path found
}

int minCapacityAlongPath(graph* residualGraph, const vector<vertex*>& path) {
    int minCapacity = numeric_limits<int>::max();
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = residualGraph->VI(path[i]->id);
        int v = residualGraph->VI(path[i+1]->id);
        int residualCapacity = residualGraph->edges[u][v]->weight - residualGraph->edges[u][v]->flow;
        minCapacity = min(minCapacity, residualCapacity);
    }
    return minCapacity;
}
graph* createResidualGraph(graph* g) {
    graph* residual = new graph(g->maxVertexAmount);
    
    for (int i = 0; i <= g->lastVertexIndex; i++) {
        residual->insertVertex(g->vertices[i]->value);
        residual->vertices[i]->id = g->vertices[i]->id;
    }
    residual->lastVertexIndex = g->lastVertexIndex;

    for (int i = 0; i <= g->lastVertexIndex; i++) {
        for (int j = 0; j <= g->lastVertexIndex; j++) {
            if (g->edges[i][j] != NULL) {
                vertex* v1 = residual->vertices[i];
                vertex* v2 = residual->vertices[j];
                residual->connectVertices(v1, v2, true, g->edges[i][j]->weight);
                residual->edges[i][j]->flow = g->edges[i][j]->flow;
            }
        }
    }

    return residual;
}

void augmentFlow(graph* residualGraph, const vector<vertex*>& path, int bottleneckCapacity) {
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = residualGraph->VI(path[i]->id);
        int v = residualGraph->VI(path[i+1]->id);
        residualGraph->edges[u][v]->flow += bottleneckCapacity;
        if (residualGraph->edges[v][u] == nullptr) {
            residualGraph->connectVertices(residualGraph->vertices[v], residualGraph->vertices[u], true, 0);
        }
        residualGraph->edges[v][u]->flow -= bottleneckCapacity;
    }
}

int FordFulkerson(graph* g, vertex* source, vertex* sink) {
    // Initialize flow on all edges to 0
    for (int i = 0; i <= g->lastVertexIndex; i++) {
        for (int j = 0; j <= g->lastVertexIndex; j++) {
            if (g->edges[i][j] != nullptr) {
                g->edges[i][j]->flow = 0;
            }
        }
    }

    // Initialize residual graph with capacities equal to original capacities
    graph* residualGraph = createResidualGraph(g);

    // Debug: Print initial residual graph
    cout << "Initial Residual Graph:" << endl;
    residualGraph->displayAdjacency();
    cout << endl;

    // Initialize total flow to 0
    int totalFlow = 0;

    // Repeat until no augmenting path exists from source to sink
    int iteration = 0;
    while (true) {
        // Find augmenting path
        vector<vertex*> augmentingPath = findAugmentingPath(residualGraph, source, sink);
        if (augmentingPath.empty()) break;  // No augmenting path found

        // Debug: Print augmenting path
        cout << "Iteration " << ++iteration << " - Augmenting Path: ";
        for (vertex* v : augmentingPath) {
            cout << v->value << " ";
        }
        cout << endl;

        // Find the bottleneck capacity along the augmenting path
        int bottleneckCapacity = minCapacityAlongPath(residualGraph, augmentingPath);

        // Debug: Print bottleneck capacity
        cout << "Bottleneck Capacity: " << bottleneckCapacity << endl;

        // Augment the flow along the augmenting path
        augmentFlow(residualGraph, augmentingPath, bottleneckCapacity);

        // Update total flow
        totalFlow += bottleneckCapacity;

        // Debug: Print current flow
        cout << "Current Total Flow: " << totalFlow << endl << endl;
    }

    // Copy the final flow values back to the original graph
    for (int i = 0; i <= g->lastVertexIndex; i++) {
        for (int j = 0; j <= g->lastVertexIndex; j++) {
            if (g->edges[i][j] != nullptr) {
                g->edges[i][j]->flow = residualGraph->edges[i][j]->flow;
            }
        }
    }

    // Debug: Print final residual graph
    cout << "Final Residual Graph:" << endl;
    residualGraph->displayAdjacency();
    cout << endl;

    // Clean up
    delete residualGraph;

    // Return the maximum flow
    return totalFlow;
}



int main()
{
    cout << "C++ DS&A Graphs - Path Finding\n"
         << endl;

    graph *g = new graph(6);

    g->insertVertex("A");
    g->insertVertex("B");
    g->insertVertex("C");
    g->insertVertex("D");
    g->insertVertex("E");
    g->insertVertex("F");

    g->connectVertices(g->getVertexByValue("A"), g->getVertexByValue("B"), true, 2);
    g->connectVertices(g->getVertexByValue("A"), g->getVertexByValue("C"), true, 4);
    g->connectVertices(g->getVertexByValue("B"), g->getVertexByValue("C"), true, 1);
    g->connectVertices(g->getVertexByValue("B"), g->getVertexByValue("D"), true, 4);
    g->connectVertices(g->getVertexByValue("B"), g->getVertexByValue("E"), true, 2);
    g->connectVertices(g->getVertexByValue("C"), g->getVertexByValue("E"), true, 3);
    g->connectVertices(g->getVertexByValue("D"), g->getVertexByValue("F"), true, 2);
    g->connectVertices(g->getVertexByValue("E"), g->getVertexByValue("D"), true, 3);
    g->connectVertices(g->getVertexByValue("E"), g->getVertexByValue("F"), true, 2);

    // Ex 1 - Dijkstra's algorithm - shortest path between two nodes
    cout << "Exercise 1: Dijkstra's algorithm" << endl;
    g->displayAdjacency();
    cout << endl;
    vertex *start = g->getVertexByValue("A");
    vertex *end = g->getVertexByValue("F");
    dijkstra(g, start, end);

    getchar();

    // Ex 2 - Dijkstra's map of shortest paths
    cout << "\nExercise 2: Dijkstra's algorithm - map of shortest paths" << endl;

    dijkstraMap(g, start);
    getchar();
    // Ex 3 - Bellman-Ford algorithm for negative weights & unweighted graphs
    cout << "\nExercise 3: Bellman-Ford algorithm - negative weights & unweighted graphs" << endl;

    bellmanFord(g, g->getVertexByValue("A"));
    getchar();

    // Ex 4 - A* Algorithm
    cout << "\nExercise 4: A* Algorithm - heuristics " << endl;

    const int MAPSIZE = 5;

    int **map = (int **)malloc(sizeof(int *) * MAPSIZE);
    for (int i = 0; i < MAPSIZE; i++)
    {
        map[i] = (int *)malloc(sizeof(int) * MAPSIZE);
    }

    map[0][0];

    map[1][1] = 1;
    map[1][2] = 1;
    map[3][0] = 1;
    map[3][3] = 1;
    map[3][4] = 1;

    aStar(map, 0, 0, MAPSIZE - 1, MAPSIZE - 1, MAPSIZE);

    // Ex 5 - Network Flow
    cout << "\nExercise 5: Maximum Network flow - Ford-Fulkerson vs Edmonds-Karp" << endl;

    int maxFLow = FordFulkerson(g, g->getVertexByValue("A"), g->getVertexByValue("F"));

    cout<<endl<<"max flow: "<<maxFLow;
    getchar();

    return 0;
}





/*
 * Exercise 1: Dijkstra's Algorithm
 * Either with the graph provided above (or with your Graph implementation from last week),
 * create a graph with the edges as described below:
 *
 *        B -  D
 *      / | \  | \
 *    A   |  \ |  F
 *      \ |   \| /
 *        C -  E
 *
 * Edge weights are:
 *
 * A->B = 2
 * A->C = 4
 *
 * B->C = 1
 * B->D = 4
 * B->E = 2
 *
 * C->E = 3
 *
 * D->F = 2
 *
 * E->D = 3
 * E->F = 2
 *
 *
 * Implement Dijkstra's algorithm to find the shortest path between node A and F in the above graph.
 * Output the path to screen to confirm.
 * If implemented correctly you should see: A->B->D->F
 *
 * Extension 1: If you haven't already, apply priority queues in Dijkstra's algorithm utilise min-heaps (priority queues).
 * Extension 2: If you had to draw the Graph in a terminal view, how would you format your display method?
 *
 * Question: What would happen if you were to add a connection from C->A with a non-negative weight and re-run Dijkstra's algorithm?
 * Question: What would happen if you were to modify the edge from A->B with the weight -2 and re-run Dijkstra's algorithm?
 *
 */

// Below is a simplified pseudocode of Dijkstra's algorithm to get you started:

/*
   Dijkstra(G, s):
    distances <- list of length equal to the number of nodes of the graph, initially it has all its elements equal to infinite
    distances[s] = 0
    queue = the set of vertices of G
    while queue is not empty:
          u <- vertex in queue with min distances[u]
          remove u from queue
          for each neighbor v of u:
              temp = distances[u] + value(u,v)
              if temp < distances[v]:
                   distances[v] = temp
     return distances
*/

/*
 * Exercise 2: Dijkstra return map of shortest path values
 * Now modify your implementation of Dijkstra's algorithm to return
 * a map of shortest paths to all nodes in graph (not just A to F).
 *
 * For example,
 * The map/dictionary returned would have corresponding shortest path value to each node in the graph:
 *
 * A : 0
 * B : 2
 * C : 3
 * D : 6
 * E : 4
 * F : 6
 *
 */

/*
 * Exercise 3: Bellman-Ford Algorithm
 * The Bellman-Ford (Richard Bellman and Lester Ford Jr, 1958) algorithm
 * can be used to compute shortest paths on graphs that include negative edge weights.
 * Start by translating the pseudocode below, adapting this to work with your implementation.
 *
 * Question: How does the performance of this algorithm compare with Dijkstra's algorithm?
 * Question: Could Dijkstra's be modified to work with negative edge weights?
 *
 * Extension: Also check that your Bellman-Ford implementation works on an unweighted graph.
 *            e.g. set all the edge weights to 1 for all connections in your graph.
 */

// Here's some pseudocode to get you started:

/*
function BellmanFord(Graph, source):
    // Step 1: Initialization
    distances = array of size |V| initialized with infinity
    distances[source] = 0

    // Step 2: Relax edges repeatedly
    for i from 1 to |V| - 1:
        for each edge (u, v, weight) in Graph:
            if distances[u] + weight < distances[v]:
                distances[v] = distances[u] + weight

    // Step 3: Check for negative cycles
    for each edge (u, v, weight) in Graph:
        if distances[u] + weight < distances[v]:
            return "Graph contains a negative cycle"

    return distances
*/

/*
 * Exercise 4: A* Algorithm algorithm
 * The A* algorithm introduces a heuristic (a strategy/prior knowledge of context) to find a path between two vertices/nodes in an environment.
 * You are welcome to define your own environment to test this algorithm. Here is a simple matrix to get you started:
 *
 *   {S, 0, 0, 0, 0},
 *   {0, 1, 1, 0, 0},
 *   {0, 0, 0, 0, 0},
 *   {1, 0, 0, 1, 1},
 *   {0, 0, 0, 0, E}
 *
 * Above, S represents the starting position, and E the finish position. 0s are navigable spaces, whereas 1s represent obstacles which you cannot pass through.
 *
 * It would be advisable to use a priority queue to explore the nodes with the lowest total cost
 * (sum of the cost from the start node to the current node and the heuristic estimate from the current node to the goal).
 * Start with a Euclidean heuristic (straight line/as the crow flies).
 * Some pseudocode has been provided below for you to modify to your implementation.
 *
 * Extension: Now apply the Manhattan heuristic (Grid approach/equal distances between blocks) to this algorithm.
 * Question: Which of the two heuristics are more effective for this problem? What are your observations here?
 *
 */

// Pseudocode for A*

/*
function AStarWithEuclideanDistance(start, goal):
    // Initialize open and closed lists
    open_list = priority queue initialized with start node
    closed_list = empty set

    // Set g score of start node to 0
    start.g = 0

    while open_list is not empty:
        // Get node with lowest f score from open list
        current = node with lowest f score in open_list

        // Check if current node is the goal
        if current is goal:
            return reconstructPath(current)

        // Move current node from open to closed list
        remove current from open_list
        add current to closed_list

        // Expand current node's neighbors
        for each neighbor of current:
            if neighbor is not traversable or neighbor is in closed_list:
                continue

            // Calculate tentative g score for neighbor
            tentative_g = current.g + distance(current, neighbor)

            if neighbor is not in open_list or tentative_g < neighbor.g:
                // Update neighbor's parent and g score
                neighbor.parent = current
                neighbor.g = tentative_g

                // Calculate Euclidean distance heuristic from neighbor to goal
                neighbor.h = euclideanDistance(neighbor, goal)

                // Add neighbor to open list (or update priority if already in open list)
                if neighbor is not in open_list:
                    add neighbor to open_list with priority f = g + h
                else:
                    update priority of neighbor in open_list to f = g + h

    // No path found
    return "No path found"

function reconstructPath(node):
    path = empty list
    while node is not null:
        prepend node to path
        node = node.parent
    return path
*/

/*
 * Exercise 5: Network Flow Problems
 *
 * Each edge in the network (graph) has a capacity, which represents the maximum amount of flow
 * that can pass through that edge. The flow along each edge must not exceed its capacity.
 * The total amount of flow entering the node must equal the total amount of flow leaving the node.
 * This principle is known as conservation of flow and ensures that resources are maintained in the network/graph.
 * The goal of Maximum-Flow algorithms is to determine the maximum amount of flow that can be sent
 * from the source to the destination (sink) while respecting the capacity constraints and satisfying the conservation of flow at each node.
 *
 * This has applications in engineering, transport, digital infrastructure etc.
 *
 * The key difference here in this application is that our edge weights will refer to the CAPACITY, rather than the distance.
 * Either reuse a previous graph or create a suitable new graph which has multiple pathways from source to destination (sink).
 *
 * Start by applying the Ford-Fulkerson algorithm (which here utilises BFS) with the pseudocode below.
 * In many cases, large maximum flow values are considered desirable because they indicate that the network can efficiently accommodate a high volume of resource flow from the source to the sink.
 *
 * Extension: Implement the Edmonds-Karp algorithm on the same graph and evaluate the differences in performance.
 * Question:  Which is more effective for maximum-flow: DFS or BFS?
 */

// Here is some pseudocode for the Ford-Fulkerson method:

/*
function FordFulkerson(Graph, source, sink):
    // Initialize flow on all edges to 0
    for each edge in Graph:
        edge.flow = 0

    // Initialize residual graph with capacities equal to original capacities
    residualGraph = copy of Graph

    // Initialize total flow to 0
    totalFlow = 0

    // Repeat until no augmenting path exists from source to sink
    while there exists an augmenting path from source to sink in residualGraph:
        // Find augmenting path using any suitable method (e.g., BFS)
        augmentingPath = findAugmentingPath(residualGraph, source, sink)

        // Find the bottleneck capacity along the augmenting path
        bottleneckCapacity = minCapacityAlongPath(augmentingPath)

        // Augment the flow along the augmenting path
        augmentFlow(residualGraph, augmentingPath, bottleneckCapacity)

        // Update total flow
        totalFlow += bottleneckCapacity

    // Return the maximum flow
    return totalFlow

function findAugmentingPath(residualGraph, source, sink):
    // Use BFS to find a path from source to sink in residualGraph
    // Return the path if found, otherwise return null

function minCapacityAlongPath(path):
    // Find the minimum capacity along the given path
    // Return the minimum capacity

function augmentFlow(residualGraph, path, bottleneckCapacity):
    // Update the flow along the given path in residualGraph by adding bottleneckCapacity to forward edges
    // and subtracting bottleneckCapacity from backward edges
*/

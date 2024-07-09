#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <limits.h>
#include <chrono>


//#include "opt/homebrew/Cellar/boost/1.85.0/include/boost/graph/adjacency_list.hpp"
//#include <boost/1.85.0/include/boost/graph/graph_utility.hpp>
// #include <boost/graph/dijkstra_shortest_paths.hpp>
// #include <boost/graph/floyd_warshall_shortest.hpp>

// ND:   /opt/homebrew/Cellar/boost/1.85.0/include/boost/fusion/include/

// g++ -std=c++11 -I /path/to/boost_1_76_0/ simple_boost_graph.cpp -o simple_boost_graph
// g++ -std=c++11 -I /path/to/boost_1_76_0/ floyd_warshall.cpp -o floyd_warshall

// to compile:
// clang++ -std=c++11 -I /opt/homebrew/Cellar/boost/1.85.0/include  "09 C++ LIVE DEMO.cpp" -o 09_dp_LD

// to run:
// ./09_dp_LD

/* README
 *  In this week, we'll explore some dynamic programming techniques.
 *  We'll set up classes to represent these using arrays, vectors and linked lists.
 *
 */

using namespace std;
using namespace chrono;
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

long long fibonacci(int n, vector<unsigned long long int> &vec)
{
    if (n <= 1)
    {
        return n;
    }
    if (vec[n] != 0)
    {
        return vec[n];
    }
    vec[n] = fibonacci(n - 1, vec) + fibonacci(n - 2, vec);
    return vec[n];
}

int _fib(int n)
{
    vector<unsigned long long int> v(n + 1, 0); // Initialize with zeros
    int f = fibonacci(n, v);
    return f;
}

using namespace std;

int lcs_rec(const string &s1, const string &s2, int m, int n, vector<vector<int>> &vec)
{
    if (m == 0 || n == 0)
    {
        return 0;
    }
    if (vec[m][n] != -1)
        return vec[m][n];
    if (s1[m - 1] == s2[n - 1])
    {
        vec[m][n] = 1 + lcs_rec(s1, s2, m - 1, n - 1, vec);
    }
    else
    {
        vec[m][n] = max(lcs_rec(s1, s2, m - 1, n, vec), lcs_rec(s1, s2, m, n - 1, vec));
    }
    return vec[m][n];
}

int lcs(string s1, string s2)
{
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> v(m + 1, vector<int>(n + 1, -1));
    return lcs_rec(s1, s2, m, n, v);
}

/*
int* knapsack(int*values, int*weights, int n, int cap){


    int i,j;
    int**result = (int**)malloc(sizeof(int**)*(n+1));
    for(i =0; i<=n; i++){
        result[i] = (int*)malloc(sizeof(int)*(cap+1));
    }

    for(i=0; i<cap; i++){
        result[0][i]=0;
    }
    for(i=0; i<=n; i++){
        result[i][0]=0;
    }
    for (i=1; i<=n; i++){
        for(j=1; j<=cap; j++){
            if(weights[i]>j){
                result[i][j] = result[i-1][j];
            }else{
                result[i][j] = max(result[i-1][j], result[i-1][j-weights[i]]+values[i]);
            }
        }
    }
}*/

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int *knapsack(int *values, int *weights, int n, int cap)
{
    int i, w;
    int **Knap = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++)
    {
        Knap[i] = (int *)malloc((cap + 1) * sizeof(int));
    }

    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= cap; w++)
        {
            if (i == 0 || w == 0)
                Knap[i][w] = 0;
            else if (weights[i - 1] <= w)
                Knap[i][w] = max(values[i - 1] + Knap[i - 1][w - weights[i - 1]], Knap[i - 1][w]);
            else
                Knap[i][w] = Knap[i - 1][w];
        }
    }

    int result = Knap[n][cap];

    int *selected = (int *)calloc(n, sizeof(int));
    w = cap;
    for (i = n; i > 0 && result > 0; i--)
    {
        if (result != Knap[i - 1][w])
        {
            selected[i - 1] = 1;
            result -= values[i - 1];
            w -= weights[i - 1];
        }
    }

    for (i = 0; i <= n; i++)
    {
        free(Knap[i]);
    }
    free(Knap);//memry maanagment may be unnecessary

    return selected;
}

#define INF INT_MAX
#define V 4  // Number of vertices in the graph

void floydWarshall(int graph[V][V]) {
    int dist[V][V];
    int i, j, k;
    //step 2
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }
        for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    //step 3
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout<<" INF";
            else
                cout<<"   "<<dist[i][j];
        }
        cout<<endl;
    }
}




int main()
{
    cout << "C++ DS&A Dynamic Programming\n"
         << endl;

    // Ex 1 - Fibonnaci - from recursion to vector cache
    cout << "Exercise 1: Fibonnaci numbers with Recursion/vecization" << endl;

    auto start = high_resolution_clock::now();
    for (int i = 10; i <= 25; i++)
    {
        cout << endl
             << _fib(i) << endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << "ms";
    getchar();

    // Ex 2 - LCS
    cout << "\nExercise 2: Longest Common Subsequence (LCS)" << endl;

    string X = "AGGTAB";
    string Y = "GXTXAYB";

    cout << lcs(X, Y);
    getchar();

    // Ex 3 - Knapsack (Rucksack) Problem
    cout << "\nExercise 3: Knapsack (Rucksack) Problem" << endl;

    int n = 15;
    int cap = 6;
    int *values = (int *)malloc(sizeof(int) * n);
    int *weights = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        values[i] = getRandomNumber(1, 10);
        weights[i] = getRandomNumber(1, 10);
    }

    int *k = knapsack(values, weights, n, cap);
    int totalValue, totalWeight;
    for (int i = 0; i < n; i++)
    {
        if (k[i] == 1)
        {
            totalValue += values[i];
            totalWeight += weights[i];
            cout << endl
                 << "\x1b[32m" << k[i] << " with value " << values[i] << " and weight: " << weights[i]<<"\x1b[0m";
        }
        else
        {
            cout << endl
                 << k[i] << " with value " << values[i] << " and weight: " << weights[i];
        }
    }

    cout << endl
         << "\x1b[32m total weight: \x1b[0m " << totalWeight << "\x1b[32m  total value: \x1b[0m  " << totalValue;
    getchar();

    // Ex 4 - Floyd-Warshall algorithm - all-pairs shortest paths
    cout << "\nExercise 4: Floyd Warshall algorithm - all-pairs shortest paths" << endl;
    int x,y;
    int graph[y][x] = {
        {0,   5,  INF, 10},
        {9,   0,   3, INF},
        {4, 7,    0,   1},
        {INF, 3, 4, 0}
    };

    floydWarshall(graph);
    getchar();
    // Ex 5 - Graphs with Boost
    cout << "\nExercise 5: Graph using Boost's Adjacency List and Dijkstra's algorithm" << endl;
    cout<<"i couldnt connect the boost library i was working from a computer i dont have admin permissions on";







    return 0;
}

/*
 * Exercise 1: Fibonacci numbers
 * Let's warm up by writing a recursive fibonacci function.
 * Remember to add a base case so you can exit the recursive method calls.
 * Now add vecrization, which caches fibonacci numbers as they are calculated.
 *
 * Extension: Create an alternative fib function which is iterative and stores computations in a table (bottom-up approach)
 * Question: What are performance differences between iterative/tabulatation approach and the recursive/vecrization approach?
 *
 */

/*
 * Exercise 2: Longest Common Subsequence (LCS)
 *
 * Given two sequences, find the length of the longest subsequence present in both of them.
 *
 * Step 1. Define a 2D dynamic programming table
 * Step 2. Initialise the base cases.
 * Step 3. Fill the table using the recurrence relation:
 *               If the characters of both sequences match:
 *                   dp[i][j] = dp[i-1][j-1] + 1
 *               else
 *                   dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 * Step 4. The length of the LCS is in dp[m][n] where m and n are the lengths of the two sequences.
 *
 */

/*
 * Exercise 3: Rucksack (knapsack) problem
 * Given a maximum weight that a rucksack (knapsack) can hold, write a function which will
 * determine the most valuable subset of items that can be included in the rucksack without exceeding its weight limit.
 *
 * Inputs will be:
 *   W (the max weight the rucksack can hold)
 *   n (number of items)
 *   The weights and values of the items
 *
 * To go about this problem, start by defining a table where rows represent items
 * and columns represent possible weight capacities.
 */

/*
 * Exercise 4: Floyd Warshall algorithm - all-pairs shortest paths
 * This is a dynamic programming approach to build up the solution for the shortest paths step by step.
 * It considers each pair of vertices and iteratively improves the path between them by considering each possible intermediate vertex.
 *
 * Step 1. Initialization:
 *   Create a 2D array dist where dist[i][j] represents the shortest distance from vertex i to vertex j.
 *   Initialize dist[i][j] to the weight of the edge from i to j if it exists, otherwise to infinity.
 *   Set dist[i][i] = 0 for all vertices i.
 *
 * Step 2. Dynamic Programming:
 *   Update the distance array dist by considering each vertex as an intermediate vertex and
 *   updating the shortest paths accordingly. For each pair of vertices (i, j), update dist[i][j].
 *
 * Step 3. Result:
 *   After considering all vertices as intermediate vertices, the dist array contains the
 *   shortest paths between all pairs of vertices.
 *
 *
 */

/*
 * Exercise 5: Graph Boost
 * Start by checking you have access to the C++ Boost library
 * Create a graph with Boost's adjacency_list function
 * Then apply Boost's Dijkstra's algorithm to work out the shortest path to all vertices.
 * Also apply Boost's Floyd Warshall's all-pairs shortest path algorithm.
 *
 * Question: what are the differences between your implementation
 *   and Boost's implementation of the Floyd Warshall's algorithm?
 *
 */

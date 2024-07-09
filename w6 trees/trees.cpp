#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include "tree.h"//everything is sorted into these things
#include "binary_tree.h"

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


inline bool isInteger(string s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char *p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

int main()
{
    cout << "C++ DS&A Trees\n"
         << endl;

    // Ex 1 - Set up the Tree class
    cout << "Exercise 1: Setting up a Tree" << endl;

    // nodes
    Node *F = new Node("F"), *B = new Node("B"), *G = new Node("G"), *A = new Node("A"), *D = new Node("D"), *C = new Node("C"), *J = new Node("J");
    /*

        F
     /   \
    B     G
   / \     \
  A   D     J
     /
    C


    */

    Tree *t = new Tree(F);
    t->insertNode(B, t->root);
    t->insertNode(G, t->root);

    t->insertNode(A, B);

    t->insertNode(D, B);
    t->insertNode(C, D);
    t->insertNode(J, G);

    // Create a tree of strings and check the three types of traversal

    // Ex 2 - Set up a BST class
    cout << "\nExercise 2: Binary Search Tree" << endl;


    //inserts random numbers into the BST
    BST *bt = new BST(new BNode(1));

    const int SIZE_OF_BINARY_TREE = 50;

    for (int i = 0; i < SIZE_OF_BINARY_TREE; i++)
    {
        bt->insert(new BNode(getRandomNumber(-150, 150)));
    }

    bt->display();

    // Ex 3 - DFS
    cout << "\nExercise 3: Depth-First Search using a Stack" << endl;

    cout << "using tree from ex. 1";

    t->DFS(t->root);
    getchar();

    // Ex 4 - BFS
    cout << "\nExercise 4: Breadth-First Search using a Queue " << endl;

    t->BFS(t->root);
    getchar();
    cout<<"aaaa";

    // reuse your Queue class from 05 Stacks and Queues

    // Ex 5 - AVL tree
    cout << "\nExercise 5: AVL Tree which balances itself" << endl;


    
    ANode * n = new ANode(3);

    AVL_Tree * at = new AVL_Tree(n);
    int c = 0;

    for (int i = 0; i < SIZE_OF_BINARY_TREE; i++)
    {
        int c = getRandomNumber(-150, 150);
        cout<<"ins"<<endl;
        cout<<c;
        getchar();


        at->display();
        

        try
        {
            n = at->insertNode(n, c);
        }
        catch(const std::exception& e)
        {
            cout<<"couldnt insert";
        }
        
        


    }
    getchar();

    at->display();  
    getchar();


    return 0;
}

/*
 * Exercise 1: Arranging Nodes in a Tree structure
 * Let's start by creating a Tree class, which enables users to add Nodes/Links in layers.
 * You could add Node objects which represent either string data or integer data.
 * For now, there is no limit to how many 'children' each layer can have. The user would have to indicate which layer the node sits in.
 *
 * Create traversal methods for 'in-order', 'pre-order' and 'post-order'. Test these work and observe the differences in output.
 *
 * Reminder:
 * In-order traversal visits nodes in the left subtree, then the root node, and finally nodes in the right subtree.
 * Pre-order traversal visits the root node first, then nodes in the left subtree, and finally nodes in the right subtree.
 * Post-order traversal visits nodes in the left subtree first, then nodes in the right subtree, and finally the root node.
 *
 *
 * Extension: Represent a file directory of folders and the files they contain, as a tree.
 * Question:  Which traversal method would maintain the structure of the file directory?
 *
 * Feel free to make up the directory (or use your file directory), but here's an example :
 *       /usr
 *           /nick
 *               /Documents
 *                   /Teaching Materials
 *                   /Research
 *                   /GitHub
 *                       /C++ DSA
 *                       /Python
 *                       /Java
 *
 */

/*
 * Exercise 2: Binary Search Tree class
 * Now create a BST class which will enforce these rules of insertion:
 * Maximum of two children per layer.
 * The left child's value must be less than the root.
 * The right child's value must be greater than the root.
 *
 * First add test data (integers or strings) and print out the BST to confirm the items are arranged in correct order, according to the rules.
 * Then run your Binary Search algorithm (W2) to check that you can efficiently search and return a value in logarithmic time.
 *
 * If you've implemented this with integer values, now sort strings by alphabetical order. Or vice versa if you started with strings, sort integers in order.
 *
 * Extension 1: Now code a delete function, which should manage pointers when a node is deleted from the BST.
 * Extension 2: If you're using pointers to connect the Nodes together, modify the BST to use an array?
 *
 */

/*
 * Exercise 3: DFS
 * Implement a Depth-First Search function, utilising either your Stack class from last week, or the STL's stack.
 * Test this works on a tree with digits.
 *
 * Extension: If you implemented the extension on the file directory, check that you can locate a file (represented as a 'string') via DFS
 *            and print the full path of this file (with preceeding folders).
 *
 */

/*
 * Exercise 4: BFS
 * Implement a Breadth-First Search function, utilising either your Queue class from last week, or the STL's queue.
 * Test this works on a tree with digits.
 *
 *
 */

/*
 * Exercise 5: AVL Tree
 * Challenge! Can you now extend your BST to balance itself when new nodes are added (or deleted).
 * The idea is to maintain the rules of a BST (left < root, right > root) but to strive for symmetry where new inserts (or deletions) make the tree too 'one-sided'.
 * This was popularised by George Adelson-Velsky and Evgenii Landis - known as an AVL tree.
 *
 * To break this problem down into manageable steps, focus on testing left rotations and right rotations.
 * I'm happy for you to use either digits or letters as values sorted and arranged.
 *
 * If you can get this working for insertions, check that the tree also re-balances itself for when you delete a given node from a tree.
 */

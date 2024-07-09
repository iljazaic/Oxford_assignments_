#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

// this is the normal tree type (not binary)

using namespace std;


//used in normal binary tree
class BNode
{
public:
    BNode *LHS = NULL;
    BNode *RHS = NULL;
    int val;
    BNode *Parent;

    BNode(int val)
    {
        this->val = val;
    }

    void insertNode(BNode *newNode)
    {
        if (newNode->val > this->val && this->RHS == NULL)
        {
            this->RHS = newNode;
            newNode->Parent = this;
            return;
        }
        if (newNode->val < this->val && this->LHS == NULL)
        {
            this->LHS = newNode;
            newNode->Parent = this;
            return;
        }
        cout << "error cannot insert node into tree as condition is not met;";
    }
};


//used in AVL tree
class ANode
{
public:
    ANode *LHS = NULL;
    ANode *RHS = NULL;
    ANode*Parent;
    int val;
    int height = 0;

public:
    ANode(int k)
    {
        this->val = k;
    }

    void insertNode(ANode *newNode)
    {
        if (newNode->val > this->val && this->RHS == NULL)
        {
            this->RHS = newNode;
            newNode->Parent = this;
            return;
        }
        if (newNode->val < this->val && this->LHS == NULL)
        {
            this->LHS = newNode;
            newNode->Parent = this;
            return;
        }
        cout << "error cannot insert node into tree as condition is not met;";
    }
};

class BST
{
public:
    BNode *root;
    bool isEmpty;
    BST()
    {
        this->isEmpty = true;
    }

    BST(BNode *root)
    {
        this->root = root;
        this->isEmpty = false;
    }

    void recursiveInsert(BNode *node, BNode *newNode)
    {
        int v = newNode->val;

        if (v > node->val)
        {
            if (node->RHS != NULL)
            {
                recursiveInsert(node->RHS, newNode);
            }
            else
            {
                node->insertNode(newNode);
            }
        }
        if (v < node->val)
        {
            if (node->LHS != NULL)
            {
                recursiveInsert(node->LHS, newNode);
            }
            else
            {
                node->insertNode(newNode);
            }
        }
        this->isEmpty = false;
    }
    void insert(BNode *newNode)
    {
        this->recursiveInsert(this->root, newNode);
    }

    void printNode(int depth, int val)
    {
        string s = "";
        for (int i = 0; i <= depth; i++)
        {
            s += "    ";
        }
        cout << s << val << endl;
    }

    void recursiveDisplay(BNode *node, int depth)
    {

        if (this->isEmpty == false)
        {

            BNode *L = node->LHS;
            BNode *R = node->RHS;

            if (R != NULL)
            {
                recursiveDisplay(R, depth + 1);
            }

            this->printNode(depth, node->val);

            if (L != NULL)
            {
                recursiveDisplay(L, depth + 1);
            }
        }
    }

    void display()
    {
        this->recursiveDisplay(this->root, 1);
    }

    bool recursiveSearch(BNode *node, int val)
    {
        if (this->isEmpty)
        {
            return false;
        }
        if (node->val == val)
        {
            return true;
        }
        if (node->val > val)
        {
            return recursiveSearch(node->LHS, val);
        }
        else
        {
            return recursiveSearch(node->RHS, val);
        }
        return false;
    }

    bool search(int val)
    {
        return recursiveSearch(this->root, val);
    }
};

class AVL_Tree
{
public:
    ANode *root;
    bool isEmpty = true;

public:
    AVL_Tree(ANode *root)
    {
        this->root = root;
        this->isEmpty = false;
    }



    bool isBalanced(ANode * p){
        int bf = p->LHS->height - p->RHS->height;

        return ((-1<=bf)&&(1>=bf));
    }


    ANode * rotateRight(ANode *pivot)
    {
        ANode *x = pivot->LHS;
        ANode *T2 = pivot->RHS;

        x->RHS = pivot;

        pivot->LHS = T2;

        pivot->height = max(pivot->LHS->height, pivot->RHS->height+1);

        x->height = max(x->LHS->height, x->RHS->height);

        return x;
    }

    ANode * rotateLeft(ANode * pivot){
        ANode * x = pivot->RHS;
        ANode * T2 = pivot->LHS;

        x->LHS = pivot;
        pivot->RHS = T2;
        pivot->height = max(pivot->LHS->height, pivot->RHS->height+1);
        x->height = max(x->LHS->height, x->RHS->height+1);


        return x;
    }

    int getBalanceFactor(int l, int r){
        if(l==NULL && r==NULL){
            return 0;
        }else if(l==NULL){
            return -r;
        }else if(r==NULL){
            return l;
        }
        return l - r;
    }

    ANode * insertNode(ANode * n, int val){
        if (n==NULL){

            return new ANode(val);
        }   
        if(val<n->val){
            n->LHS = this->insertNode(n->LHS, val);
        }else if(val>n->val){

            n->RHS = this->insertNode(n->RHS, val);
        }else{
            return n;
        }

        int a = n->LHS==NULL?0:n->LHS->height;
        int b = n->RHS==NULL?0:n->RHS->height;
        n->height = 1+ max(a, b);

        int balanceFactor = this->getBalanceFactor(a, b);
        cout<<endl<<"BALANCE FACTOR: "<<balanceFactor<<endl;
        if(balanceFactor>1)
        {
            if(val<n->LHS->val){
                return rotateRight(n);
            }else if (val>n->LHS->val){
                n->LHS = rotateLeft(n->LHS);
                return rotateRight(n);
            }
        }

        if(balanceFactor<-1){
            if(val>n->RHS->val){
                return rotateLeft(n);
            }else if(val<n->RHS->val){
                n->RHS = rotateRight(n->RHS);
                return rotateLeft(n);
            }
        }

        return n;
    }

    void printNode(int depth, ANode* n)
    {
        string s = "";
        for (int i = 0; i <= depth; i++)
        {
            s += "    ";
        }

        int a = n->LHS==NULL?0:n->LHS->height;
        int b = n->RHS==NULL?0:n->RHS->height;
        cout << s << n->val<<"("<<this->getBalanceFactor(a,b)<<")" << endl;
    }

    void recursiveDisplay(ANode *node, int depth)
    {

        if (this->isEmpty == false)
        {

            ANode *L = node->LHS;
            ANode *R = node->RHS;

            if (R != NULL)
            {
                recursiveDisplay(R, depth + 1);
            }

            this->printNode(depth, node);

            if (L != NULL)
            {
                recursiveDisplay(L, depth + 1);
            }
        }
    }

    void display()
    {
        this->recursiveDisplay(this->root, 0);
    }
    



};
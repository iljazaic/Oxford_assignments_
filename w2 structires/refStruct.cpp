#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <list>
/* README
 *  In this week, we'll take a look at some initial data structures.
 *  We'll contrast indexed based structures (such as arrays and vectors) with memory referenced structures such a linked lists and sequential structures such as streams.
 *
 *  There is a random number generator function below which is useful for populating your structures with test data.
 *  And below you'll also find the exercise function declarations and class declarations for Link and LinkedList (so they can be defined later).
 *
 */

using namespace std;

#include <random>

int getRandomNumber()
{
    // from C++11 - more reliable than the older C-style srand() function:
    random_device rd;                                   // obtain a random seed from the hardware
    mt19937 eng(rd());                                  // Standard Mersenne Twister engine seeded with rd()
    uniform_int_distribution<int> distribution(1, 100); // distribution from 1 to 100

    int randomNumber = distribution(eng); // generate random number

    return randomNumber;
}
class Link
{

public:
    int data;
    Link *next = NULL;
    Link() {} // default constructor
    Link(int data)
    {
        this->data = data; // non-default constructor
        // assign local 'data' to this Link's data.
    }
    void print()
    {
        cout
             << this->data;
        // print out the value of this Link's data
    }
};

void exercise2()
{
    cout << "\nExercise 2: Link objects" << endl;

    Link *l = new Link(4);
    l->print();
}

/*
 * Exercise 3:
 * Now complete the LinkedList class below, implementing the prepend (add to the head of the list), find and display functions.
 * Test these functions work by adding five Link instances to an instance (object) of the LinkedList.
 *
 * Extension 1: Write an append function (add to the tail of the list).
 * Extension 2: Also overload the prepend and append functions to allow integer data values to be passed in
 *              and then 'wrapped' in a Link instance before being added to the Linked List.
 * Extension 3: Write the delete function that will delete a given node 'by-value'.
 *              Test this by deleting the start of the list, mid-list and end of the list.
 */

class LinkedList
{
private:
    Link *head = NULL;
    bool empty = true;
    // declare a pointer to the head of the linked list here.
public:
    LinkedList()
    {
        this->head = new Link(0);
        this->empty = true;
        // assign 0 to the head of the list by default here
    }
    void display()
    {
        if (!this->empty)
        {
            Link *c = this->head;
            while (c != NULL)
            {
                c->print();
                cout << "->";
                c = c->next;
            }
        }
        // traverse the list here by looking each 'next' pointer of a Link instance.
    }
    void prepend(Link *newLink)
    {
        // add a new link instance to the beginning of the list.

        if (this->empty == true)
        {
            this->head->data = newLink->data;
            this->empty = false;
            return;
        }

        Link *c = this->head;
        newLink->next = c;
        this->head = newLink;

    }
    void append(Link *newLink)
    {

        if (this->empty)
        {
            this->head->data = newLink->data;
            this->empty = false;
            return;
        }
        Link *c = this->head;
        while (c->next != NULL)
        {
            c = c->next;
        }
        c->next = newLink;
        // add a new link instance to the tail of the list.
    }
    Link *find(int valToFind)
    {
        Link *c = this->head;
        while (c != NULL)
        {
            if (c->data == valToFind)
            {
                return c;
            }
        }
        // traverse the list and match the 'valToFind'
        // with the data attribute in a Link instance.
        // remember to return the pointer to the link that was found, or a null pointer if not found.
    }
    Link *remove(int valToDelete)
    {

        Link *c = this->head;
        Link *prev = NULL;
        while (c != NULL)
        {
            if (c->data == valToDelete)
            {

                if (prev == NULL)
                {
                    this->head = this->head->next;
                    return c;
                }
                else
                {
                    prev->next = c->next;
                }
                if (c->next == NULL)
                {
                    prev->next = NULL;
                    return c;
                }
            }
        }
        prev = c;
        c = c->next;

        // first 'find' the Link instance to delete
        // make sure the Link before the 'one to delete' points to the 'next' of the 'one to delete'.
        // return the pointer to the link that was deleted, or null pointer if not deleted.
    }
    bool isEmpty()
    {
        if (this->head == NULL)
        {
            return true;
        }
        return false;
        // return true if the LinkedList is empty or false if it contains at least one Link instance.
    }
};

class Link2
{
public:
    Link2 *next = NULL;
    Link2 *prev = NULL;
    int data;

    Link2(int val)
    {
        this->data = val;
    }
    void print()
    {
        cout << this->data;
    }
};

class LinkedList2
{
private:
    Link2 *head = NULL;
    Link2 *tail = NULL;
    bool empty = true;

public:
    LinkedList2()
    {
        this->head = new Link2(0);
        // assign 0 to the head of the list by default here
    }
    void display()
    {
        if (!this->empty)
        {
            Link2 *c = this->head;
            while (c != NULL)
            {
                c->print();
                cout << "->";
                c = c->next;
            }
        }

        // traverse the list here by looking each 'next' pointer of a Link instance.
    }
    void prepend(Link2 *newLink)
    {
        // add a new link instance to the beginning of the list.

        if (this->empty == true)
        {
            this->head->data = newLink->data;
            this->empty = false;
            return;
        }

        Link2 *c = this->head;
        newLink->next = c;
        c->prev = newLink;
        this->head = newLink;
    }
    void append(Link2 *newLink)
    {
        if (this->empty == true)
        {
            this->head->data = newLink->data;
            this->empty = false;
            return;
        }
        if (this->tail == NULL)
        {
            this->tail = newLink;
            this->head->next = this->tail;
            this->tail->prev = this->head;
            return;
        }

        this->tail->next = newLink;
        this->tail->next->prev = this->tail;
        this->tail = newLink;
        // add a new link instance to the tail of the list.
    }
    Link2 *find(int valToFind)
    {
        Link2 *c = this->head;
        while (c != NULL)
        {
            if (c->data == valToFind)
            {
                cout << "exists";
                return c;
            }
            c = c->next;
        }

        cout << "doesnt exist";
        return nullptr;
        // traverse the list and match the 'valToFind'
        // with the data attribute in a Link instance.
        // remember to return the pointer to the link that was found, or a null pointer if not found.
    }

    Link2 *traverseBothWays(int valToFind)
    {

        if (this->empty == false && this->tail != NULL)
        {
            Link2 *l1 = this->head;
            Link2 *l2 = this->tail;

            while (l1->prev != l2)
            {
                if (l1->data == valToFind)
                {
                    return l1;
                }
                if (l2->data == valToFind)
                {
                    return l2;
                }
                if (l2 == l1)
                {
                    return nullptr;
                }
                l1 = l1->next;
                l2 = l2->prev;
            }
        }
        if (this->tail == NULL)
        {
            if (this->head->data == valToFind)
            {
                return this->head;
            }
        }
        return nullptr;
    }

    Link2 *remove(int valToDelete)
    {

        if (this->empty == false)
        {
            Link2 *l = this->traverseBothWays(valToDelete);

            if (l != nullptr)
            {

                if (l == this->head)
                {
                    this->empty = true;
                    this->head->next->prev = NULL;
                    this->head = NULL;
                    return l;
                }

                if (l == this->tail)
                {
                    this->tail->prev->next= NULL;
                    this->tail = this->tail->prev;
                    return l;
                }

                l->prev->next = l->next;
                return l;
            }
        }
        return nullptr;

        // first 'find' the Link instance to delete
        // make sure the Link before the 'one to delete' points to the 'next' of the 'one to delete'.
        // return the pointer to the link that was deleted, or null pointer if not deleted.
    }
    bool isEmpty()
    {
        if (this->head == NULL)
        {
            return true;
        }
        return false;
        // return true if the LinkedList is empty or false if it contains at least one Link instance.
    }
};

class LinkedList;
class Link;




void exercise1()
{
    cout << "\nExercise 1: Arrays and Vectors" << endl;
    int total;
    int *arr = (int *)malloc(sizeof(int) * 50);
    for (int i = 0; i < 50; i++)
    {
        arr[i] = getRandomNumber();
        total += arr[i];
        if (i > 44)
        {
            cout << arr[i]<<" ";
        }
    }
    cout << "total of 50: " << total << " average of 50: " << (total / 50);
    cout<<endl;
    array<int, 50> ar;
    for (int i = 0; i < 50; i++)
    {
        ar[i] = getRandomNumber();
        total += ar[i];
        if (i > 44)
        {
            cout << ar[i]<<" ";
        }
    }

    for (int i : ar)
    {
        cout << i<<" ";
    }

    cout << "total of 50: " << total << " average of 50: " << (total / 50);
    cout<<endl;

    vector<int> a(50, 0);
    for (int i : a)
    {
        i = getRandomNumber();
        cout << i << " ";
    }
    cout << "total of 50: " << total << " average of 50: " << (total / 50);
    cout<<endl;
}

void exercise3()
{
    cout << "\nExercise 3: Linked List operations" << endl;
    LinkedList *ll = new LinkedList();
    ll->append(new Link(5));
    ll->append(new Link(444));
    ll->append(new Link(12));
    ll->prepend(new Link(1));
    ll->prepend(new Link(7));

    ll->display();
}

void exercise4()
{
    cout << "\nExercise 4: Doubly Linked List " << endl;

    LinkedList2 *l = new LinkedList2();

    l->append(new Link2(4));
    l->append(new Link2(626));
    l->prepend(new Link2(14));
    l->remove(626);

    l->display();
}
void exercise5()
{

    cout << "Exercise 5: STL List vs Linked List" << endl;



    list<int> stlList;
    list<int>::iterator it = stlList.begin();         
    stlList.insert(it, 1);
    stlList.insert(it, 4);
    stlList.insert(it,99);
    stlList.insert(it, 15);
    stlList.insert(it,67);

    for (it=stlList.begin(); it != stlList.end(); ++it){
        cout << ' ' << *it;
    }

    cout<<endl;


    list<int>::iterator n = find(stlList.begin(), stlList.end(), 4);
    if(n!=stlList.end()){
        cout<<*n;
    }

}

int main()
{
    cout << "C++ DS&A Arrays, Vectors and Lists\n"
         << endl;

    exercise1();
    cout<<endl;
    exercise2();
    cout<<endl;
    exercise3();
    cout<<endl;
    exercise4();
    cout<<endl;
    exercise5();
    getchar();
    return 0;
}




/*
 * Exercise 1: Vectors vs arrays
 * Create a primitive array of 50 integers. Populate the array with 50 randomly generated values (between the range of 1 to 100).
 * Rather than printing each of the 50 integers, print either the last five values or the total and average of the 50 random values.
 *
 * Extension 1: Now replicate this with the STL array. Remember to uncomment the 'include array' above.
 * Extension 2: Now replicate this with an STL vector. Likewise, remember to uncomment the 'include vector' statement above.
 * Extension 3: Use an iterator to traverse the vector.
 * Question: Is it possible apply an iterator to the STL array too? If so, are there any advantages to applying an iterator here?
 */



/*
 * Exercise 2:
 * Complete the Link class implementation below, replacing the comments with C++ code.
 * then in the exercise2() function underneath, create three link instances with integer data.
 * print this data to the screen via each Link's print function to check that the instances have been created correctly.
 */

/*
 * Exercise 4:
 * Now amend your LinkedList class and your Link class to behave as a 'doubly-linked list'.
 * You're advised to add a 'tail' pointer to the LinkedList class (if not already), and a 'previous' pointer into your Link class.
 * Amend the prepend/append (insert) methods to also manage 'previous'. Likewise the delete method.
 *
 * Extension: Consider if you can amend your find function to traverse the list
 *            both forwards and backwards simultaneously, from the head and tail of the list respectivly.
 */

/* Exercise 5: STL List vs Linked List
 *
 * By uncommenting and using the 'include list' statement above, implement an STL list.
 * Add five separate integer values by using the 'insert' method.
 * You may also need to specify whether you are 'inserting' at the 'begin' or the 'end of the list.
 *
 * Extension 1: Use an iterator to traverse through the STL list.
 * Extension 2: Use the 'find' method from the 'algorithm' class on your STL list.
 */


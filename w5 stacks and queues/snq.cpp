#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <limits>

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

/* Function to generate a phone number at random by calling the getRandomNumber generator */
/*
long getPhoneNumber(){
    string phoneNum = "447"; // using UK area code +44 and typically they start with 07
    for (int i = 0; i < 9; i++){
        phoneNum += std::to_string(getRandomNumber(0,9)); //convert the returned int to a str so it can be appended
    }
    return std::stol(phoneNum); //finally convert the str to a long to return as a number
}
*/

// below are the class and exercise function declarations

class Stack;       // Exercise 1
class LinkedStack; // Exercise 2
class Queue;       // Exercise 3
class LinkedQueue; // Exercise 4
void STLStack();   // Exercise 5
void STLQueue();   // Exercise 5

/*
 * Exercise 1: Create a Stack class that uses an Array
 * Complete the Stack class below, which has functionality to 'peek', 'pop', and 'push' data.
 * The push function should add new data to the top of the stack
 * The pop function should remove data from the top of the stack
 * The peek function should return the top of the stack (but not delete)
 *
 * We'll start by representing the stack as an integer array.
 * In main above, populate the stack with random integer values.
 *
 * Extension 1: Either create a new class or amend the Stack class to use a vector rather than an array.
 * Extension 2: Either create a new class or amend the Stack class to be a template class, which can create the stack
 *              of a data type specfied when the template class is instantiated.
 *
 */

class Stack
{
private:
    const int MAX_SIZE = 30;
    int *ELEMENTS = (int *)malloc(MAX_SIZE * sizeof(int));

    int topIndex = MAX_SIZE - 1;

public:
    Stack(int size)
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            ELEMENTS[i] = NULL;
        }
    }

    bool isEmpty()
    {
        return ELEMENTS[MAX_SIZE - 1] == NULL;
    }

    bool isFull()
    {
        return ELEMENTS[0] != NULL;
    }

    void push(int item)
    {
        if (isFull())
        {
            cout << endl
                 << "error pushing to a full stack" << endl;
            return;
        }
        if (isEmpty())
        {
            ELEMENTS[MAX_SIZE - 1] = item;
        }
        else
        {
            ELEMENTS[topIndex - 1] = item;
            topIndex--;
        }
    }

    int pop()
    {

        if (isEmpty())
        {
            cout << endl
                 << "error popping from empty stack" << endl;
            return -1;
        }
        ELEMENTS[topIndex] = NULL;
        topIndex++;
        return 0;
    }

    int peek()
    {

        if (isEmpty())
        {
            cout << endl
                 << "error peeking empty stack" << endl;

            return numeric_limits<int>::min(); // i guess returning -2147483647 would indicate an error make it someone else's issue
        }

        return ELEMENTS[topIndex];
    }
};

/*
 * Exercise 2: Create a Stack that uses a Linked List
 * Now complete the 'LinkedStack' class below, using similiar logic to the 'Stack' class above.
 * However, this time, the pointers to an object of a class will be stacked (pushed) on top of previously added pointers.
 * Code this to be a template class which store objects to pointers of any class.
 *
 * Extension: Function calls and user actions are often stacked on top of each other, often for the purposes of going back/undoing actions.
 *            Furthermore, We'll see that the Depth-First Search algorithm stacks nodes on top of each other (and Breadth-First Search algorithm uses queues).
 *            For now, simulate a scenario which requires items to be stacked on top of each other. You could add pointers to either functions or objects to this LinkedStack template you've created.
 */

// Make sure you have a Node/Link class defined
// so that pointers to objects of this class can be added to the LinkedStack

class Node
{
public:
    int val;
    Node *next;
    Node *prev;
    Node(int val)
    {
        this->val = val;
        this->next = NULL;
    }
};

class LinkedStack
{
private:
    int max_size = 10;
    Node *head = NULL; // treat head as top of stack and prepends

public:
    LinkedStack(int size)
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
                 << "error popping from empty stack" << endl;
            return;
        }
        Node *oldHead = this->head;
        if (oldHead->next != NULL)
        {
            Node *newHead = this->head->next;
            this->head = newHead;
        }
        else
        {
            this->head = NULL;
        }
        delete[] oldHead;

        return;
    }
    ~LinkedStack()
    {
        while (!isEmpty())
        {
            this->pop();
        }
        delete[] this;
    }

    void push(int value) // basically a prepend?
    {

        Node *newNode = new Node(value);
        newNode->next = this->head;
        this->head = newNode;
        return;
    }

    int peek()
    {
        if (this->isEmpty())
        {
            cout << endl
                 << "error peeking empty stack" << endl;
            return INT64_MAX;
        }
        return this->head->val;
    }
};

/*
 * Exercise 3: Create a Queue that uses an Array
 * Using an integer array, complete the class outline below to be able to 'enqueue' and 'dequeue' integer values.
 * The enqueue function should add data to the 'rear' of the queue.
 * The dequeue function should remove data to the 'front' of the queue.
 *
 * Extension 1: Add front and rear 'pointers' so fixed size arrays can be treated as 'circular queue'.
 * Extension 2: Add code to the 'enqueue' function so items are sorted via 'priority'.
 */

#include <iostream>
#include <stdexcept>
#include <limits>

class Queue {
private:
    static const int MAX_SIZE = 30;
    int* ELEMENTS;
    int frontIndex;
    int rearIndex;
    int currentSize;

public:
    Queue() : ELEMENTS(new int[MAX_SIZE]), frontIndex(0), rearIndex(-1), currentSize(0) {}

    ~Queue() {
        delete[] ELEMENTS;
    }

    int length() const {
        return currentSize;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    bool isFull() const {
        return currentSize == MAX_SIZE;
    }

    void enqueue(int value) {
        if (isFull()) {
            throw std::runtime_error("Error: Trying to add to a full queue");
        }
        rearIndex = (rearIndex + 1) % MAX_SIZE;
        ELEMENTS[rearIndex] = value;
        currentSize++;
    }

    int dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Error: Dequeueing from an empty queue");
        }
        int value = ELEMENTS[frontIndex];
        frontIndex = (frontIndex + 1) % MAX_SIZE;
        currentSize--;
        return value;
    }

    int peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Error: Peeking at an empty queue");
        }
        return ELEMENTS[frontIndex];
    }
};

class LinkedQueue
{
private:
    Node *front;
    Node *back;

public:
    LinkedQueue()
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
            front = new Node(value);
        }
        else
        {
            Node *newNode = new Node(value);
            if (back == NULL)
            { // back doesnt exist
                this->front->prev = newNode;
                newNode->next = this->front;
            }
            else
            { // back exists
                this->back->prev = newNode;
                newNode->next = this->back;
            }
            this->back = newNode;
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

    ~LinkedQueue()
    {

        while (!this->isEmpty())
        {
            Node *k = this->front;
            this->dequeue();
            delete[] k;
        }

        delete[] this;
    }
};

/*
 * Exercise 5: STL Stack and Queue
 * Making use of the #include <stack> and #include <queue> commands above,
 * create instances of the STL stack and queue and push/pop data to/from them.
 *
 * Question: Can you identify any differences between STL's Stack and Queue and your classes?
 */

void STLStack()
{
    stack<int> stack;

    stack.push(3);
    stack.push(123);
    stack.push(3);
    stack.push(13);
    stack.push(199);
    stack.pop();
    cout << stack.top();
    return;
}

void STLQueue()
{
    queue<int> q;
    q.push(3);
    q.push(123);
    q.push(3);
    q.push(13);
    q.push(199);
    q.pop();
    cout << q.front();
    return;
}

int main()
{

    cout << endl
         << "ex 2 checking linked stack:" << endl;

    LinkedStack *stack = new LinkedStack(20);

    stack->push(3);
    stack->push(123);
    stack->push(3);

    stack->pop();
    cout << stack->peek(); // expected output = 22
    getchar();

    cout << "ex 3 checking array-based queue:" << endl;
    Queue *aq = new Queue();
    for (int i = 0; i < 20; i++)
    {
        aq->enqueue(52 - i);
    }
    for (int i = 0; i < 5; i++)
    {
        int a = aq->dequeue();
    }
    for (int i = 0; i < 6; i++)
    {
        aq->enqueue(52 - i);
    }
    cout << aq->peek(); // expected output i think is 48?
    getchar();

    cout << "ex 4 checking linked queue:" << endl;
    LinkedQueue *q = new LinkedQueue();

    q->enqueue(10);
    q->enqueue(15);
    q->enqueue(33);
    q->dequeue();
    q->dequeue();
    cout << q->peek(); // expected output = 33
    getchar();

    // Ex 5 - STL Stack and Queue

    cout << "\nExercise 5: STL Stack Example" << endl;

    STLStack();

    cout << "\nExercise 5: STL Queue Example" << endl;
    STLQueue();

    return 0;
}
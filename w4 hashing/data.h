#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <vector>

#include <ctime>
#include <unistd.h>


using namespace std;

int hash_(long key, int tableSize)
{
    int hash = key % tableSize;

    return hash;
}

// EX2

int hash_(const string &key, int tableSize)
{
    long long hash_val = 0;
    const int p = 53;
    const int m = 1e9 + 9;
    const int n = key.length();

    long long pow = 1;

    for (char c : key)
    {
        hash_val = (hash_val + c * pow) % m;
        pow = (pow * p) % m;


    }
    cout<<key<<endl<<hash_val<<endl;
    return hash_val % tableSize;
}



string randomeString(const int len) {//function by Ates Goral from stackOverflow (https://stackoverflow.com/users/23501/ates-goral)
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}


class Contact
{
public:
    string name;
    long phoneNum;
    Contact *next;
    Contact() {}
    Contact(string name, long phoneNum)
    {
        this->name = name;
        this->phoneNum = phoneNum;
    }
};

class LinkedList
{
public:
    Contact *head;
    Contact *tail;

    LinkedList()
    {
        this->head = new Contact("$heading element$", -1);
    }

    void append(Contact *newContact)
    {
        if (this->head->phoneNum == -1)
        {
            this->head = newContact;
        }
        else
        {
            this->tail->next = newContact;
        }
        this->tail = newContact;
    }

    bool isEmpty()
    {
        return (this->head->phoneNum == -1);
    }

    void display()
    {
        if (this->isEmpty() == true)
        {
            cout << "EMPTY";
        }
        else
        {
            Contact *subject = this->head;
            cout << "STARTLIST->";
            while(1){
                cout <<"(Name: "<< (subject->name) << "; Number: " << subject->phoneNum << ")->";
                if (subject!=this->tail){
                    subject = subject->next;

                }else{
                    break;
                }
            }
            cout << "ENDLIST";
        }
    }
    void prepend(Contact *newContact)
    {
        if (this->head->phoneNum == -1)
        {
            this->head = newContact;
        }
        newContact->next = this->head;
        this->head = newContact;
    }

    void remove(string name)
    { // untested but works in theory??
        Contact *prev;
        Contact *subject = this->head;

        while (subject != this->tail)
        {
            if (subject->name == name)
            {
                if (subject == this->head)
                {
                    this->head = subject->next;
                    return;
                }
                else
                {
                    prev->next = subject->next;
                    return;
                }
            }
            prev = subject;
            subject = subject->next;
        }
    }
    Contact *find(string name, long number)
    {
        Contact *subject = this->head;
        while (subject != this->tail)
        {
            if (subject->name == name || subject->phoneNum == number)
            {
                return subject;
            }
            subject = subject->next;
        }
    }
};

class HashTable
{
public:
    LinkedList **hashTable;
    int size = 30;

    HashTable()
    {
        this->hashTable = new LinkedList *[size];
        for (int i = 0; i < size; i++)
        {
            hashTable[i] = new LinkedList();
        }
    }
    HashTable(int size)
    {
        this->size = size;
        this->hashTable = new LinkedList *[size];

        for (int i = 0; i < size; i++)
        {
            hashTable[i] = new LinkedList();
        }
    }
    void insertContact(Contact *NC)
    {
        string sKey = NC->name;
        int index = hash_(sKey, this->size);
        hashTable[index]->append(NC);
    }
    void removeContact(string name)
    {
        int index = hash_(name, this->size);
    }//not done sorry

    void displayTable()
    {
        for (int i = 0; i < size; i++)
        {
            cout << endl
                 << "[" << i << "] : ";
            this->hashTable[i]->display();
        }
    }
};

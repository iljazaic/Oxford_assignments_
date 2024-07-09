#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include "data.h"
#include <cassert>

#include <ctime>
#include <unistd.h>

#include <chrono>

using namespace std;
using namespace chrono;
#include <random>

/* Modified */
int getRandomNumber(int lower, int upper)
{
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> distribution(lower, upper);

    int randomNumber = distribution(eng);

    return randomNumber;
}

long getPhoneNumber()
{
    string phoneNum = "";
    for (int i = 0; i < 9; i++)
    {
        phoneNum += to_string(getRandomNumber(0, 9));
    }
    return stol(phoneNum);
}

string getRandomString(int n ){
    string s = "";

    for (int i = 0; i < 9; i++)
    {
        s += char(getRandomNumber(48, 122));
    }
    return s;
}





int linearProbing(long *table, int index, int size);
int quadraticProbing();
int primeProbing();


//EX 5

void unorderedMap()
{
    cout << "\nExercise 5: STL Unordered Map" << endl;

    unordered_map<string, unsigned long long> map;

    map["user1"] = getPhoneNumber();
    map["user2"] = getPhoneNumber();
    map["user3s"] = getPhoneNumber();

    for (const auto& pair : map) {
        cout << pair.first << ": " << pair.second << endl;
    }
    if (map.find("user2") != map.end()) {
        cout << "user2 is in the map" << endl;
    }
    map.erase("user2");
    cout << "Size after removal: " << map.size() << endl;
    for (const auto& pair : map) {
        cout << pair.first << ": " << pair.second << endl;
    }

}



int main()
{
    
    cout << "C++ DS&A Hashing\n"
         << endl;
    //EX 1
    const static int TABLE_SIZE = 30;
    long *hashTable = (long *)malloc(TABLE_SIZE * sizeof(long));

    cout << "Exercise 1: Hash Function for integer keys" << endl;

    long key = getPhoneNumber();

    int index = hash_(key, TABLE_SIZE);
    hashTable[index] = key;
    cout << "The hash of key " << key << " is " << index << " which stores the value " << hashTable[hash_(key, TABLE_SIZE)] << endl;

    // Ex 2
    cout << "\nExercise 2: Overloaded Hash Function for string keys" << endl;
    string sKey = "user1";
    key = getPhoneNumber();
    index = hash_(sKey, TABLE_SIZE);
    hashTable[index] = key;

    cout << "stringKey is " << sKey << " and the hash is " << index << " and the value is " << hashTable[hash_(sKey, TABLE_SIZE)];

    cout << "\nExercise 3: Collisions - Open Addressing " << endl;

    string sKey2 = "user2";

    key = getPhoneNumber();
    index = hash_(sKey2, TABLE_SIZE);

    hashTable[linearProbing(hashTable, index, TABLE_SIZE)] = key;


    //EX 3 - probing methods implemented below

    //EX 4
    cout<<"excercise 4 - closed chaining into a linked list"<<endl;
    Contact* c1 = new Contact("Ilja", 12345678);
    Contact* c2 = new Contact("Ilja", 87654321);

    Contact* c3 = new Contact("Jeff", getPhoneNumber());
    Contact* c4 = new Contact("Jeff", getPhoneNumber());

    Contact* c5 = new Contact("2itn92", getPhoneNumber());
    Contact* c6 = new Contact("2itn92", getPhoneNumber());


    Contact* c7 = new Contact("asdlkhvhalvrf", getPhoneNumber());
    Contact* c8 = new Contact("2itn92", getPhoneNumber());

    HashTable* table = new HashTable(30);

    auto start = high_resolution_clock::now();

    table->insertContact(c1);
    table->insertContact(c2);

    table->insertContact(c3);
    table->insertContact(c4);


    table->insertContact(c5);
    table->insertContact(c6);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    auto start2 = high_resolution_clock::now();
    table->displayTable();
    auto stop2 = high_resolution_clock::now();
    cout <<endl<<"time it took to assign 7 elements: "<< duration.count()/1e6 << "s"<< endl;
    
    cout<<"time it took to display the hash table: "<< (duration_cast<microseconds>(stop2 - start2).count()/1e6) << "s"<< endl;

    HashTable* hash2 = new HashTable();


    for(int i = 0; i<50; i++){
        string a = getRandomString(15);
        long num = getPhoneNumber();
        hash2->insertContact(new Contact(a, num));

    }


    hash2->displayTable(); 


    //EX 5


    unorderedMap();
    getchar();
    return 0;
}



//EX 3
int linearProbing(long *table, int index, int TableLength)
{
    for (int i = index; i < TableLength - index; i++)
    {
        if (table[i] == 0)
        {
            return i;
        }
    }
    for (int i = 0; i < index; i++)
    {
        if (table[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

int quadraticProbing(long *table, int index, int tableLength)
{
    if (table[index] != 0)
    {
        for (int i = 1; i <= tableLength; i++)
        {
            index += i * i;
            if (index >= tableLength)
            {
                index = (index - 1) - tableLength;
            }
            if (table[index] == 0)
            {
                return index;
            }
        }
        return -1;
    }
    return index;
}

int primeProbing(long *table, int index, int tableLength)
{
    int prime = 7;
    if (table[index] != 0)
    {
        for (int i = 1; i <= tableLength; i++)
        {
            index += prime * i;
            if (index >= tableLength)
            {
                index = (index - 1) - tableLength;
            }
            if (table[index] == 0)
            {
                return index;
            }
        }
    }
}




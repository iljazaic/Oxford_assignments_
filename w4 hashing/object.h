#ifndef object_h
    #define object_h

#include <iostream>




using namespace std;



class GameObject{
    public:
        int id;
        std::string name;
        GameObject(int id, string name){
            this->id=id;
            this->name=name;
        }
};



#endif
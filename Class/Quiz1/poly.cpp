//Classes, Inheritance, and Polymorphism in C++
#include<iostream>

using namespace std;

class Fruit
{
    public : 
            virtual void print(){cout<<"Fruit"<<endl;}
};

class Orange : public Fruit{
    public: 
            //need virtual keyword to override
            void print() 
            { 
                cout<<"orange"<<endl;
            }
};

class Mandarin : public Orange{
    public: 
            //need virtual keyword to override
           void print() 
            { 
                cout<<"mandarin"<<endl;
            }
};


int main()
{
    Mandarin * a = new Mandarin();
    Fruit *b = new Orange();
    Orange *c = new Mandarin();
    
    a->print();
    b->print();
    c->print();
    return 0;
}
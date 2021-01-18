//Classes, Inheritance, and Polymorphism in C++
#include<iostream>

using namespace std;

class Base
{
    public : 
            virtual void iam();
};

void Base::iam()
{
    cout<<"base"<<endl;
}

class One : public Base{
    public: 
            //need virtual keyword to override
            virtual void iam() 
            { 
                cout<<"class One"<<endl;
            }
            void iam2()
            {
                Base::iam();
            }
};

class Two : public Base{
    public: 
            //need virtual keyword to override
            virtual void iam() 
            { 
                cout<<"class Two"<<endl;
            }
            void iam2()
            {
                Base::iam();
            }
};


int main()
{
    Base b;
    cout<<"Calling b.iam(): "; b.iam();
    cout<<endl;

    One o;
    cout<<"Calling o.iam(): "; o.iam();
    cout<<"Calling o.iam2(): "; o.iam2();
    cout<<endl;

    Two t;
    cout<<"Calling t.iam(): "; t.iam();
    cout<<"Calling t.iam2(): "; t.iam2();
    cout<<endl;

    //declaring pointers to address of objects
    Base *o1Ptr = &o;
    Base *t1Ptr = &t;

    //calling iam() through pointer
    o1Ptr->iam();
    t1Ptr->iam();
    
    return 0;
}
#include <iostream>
using namespace std;

class IOBuffer {
    public:
        virtual void Print() {
            cout <<"IOBuffer"<<endl;
        }
        virtual int Read (istream &) = 0;
};

class VariableLengthBuffer : public IOBuffer {
    public:
        void Print() {
            cout<<"VariableLengthBuffer"<<endl;
        }
        int Read (istream &) {
            return 0;
        }
};

class DelimFieldBuffer : public VariableLengthBuffer {
    public:
        void Print() {
            cout<<"DelimFieldBuffer"<<endl;
        }
        int Pack (const void*, int size = -1);
};

int main() {
    IOBuffer *i = new VariableLengthBuffer();
    i -> Print(); //polymorphism
    
    VariableLengthBuffer *v = new DelimFieldBuffer();
    v-> Print();
    
    return 0;
}
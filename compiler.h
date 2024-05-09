#include <iostream>
#include <string>
#include <stack>
#include <cassert>

using namespace std;

class BFMCompiler {
    int ssz = 0;

    void prologue(int sz=3000, ostream &os=cout);
    void alloc_cell(ostream &os=cout);
    void dealloc_cell(ostream &os=cout);
    void increment(ostream &os=cout);
    void decrement(ostream &os=cout);
    void loop_begin(int cn, ostream &os=cout); //char number of the LBRACK
    void loop_end(int cn, ostream &os=cout);
    void stack_pp(ostream &os=cout);
    void stack_sw(ostream &os=cout);
    void stack_me(ostream &os=cout);
    
    public:
    void translate(istream &is=cin, ostream &os=cout);
    BFMCompiler(int sssz=3000) {
        ssz = sssz;
    }
};
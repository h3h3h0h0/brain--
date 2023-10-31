#pragma once
#include <vector>

using namespace std;

class Cell {
    const int presize = 30000; //prealloc size
    //value stored within cell itself
    char value;
    //cells considered to be "inside" current cell
    vector<Cell*> mem;
    //parent cell pointer for efficiency
    //nullptr if at top level
    Cell* parent;
    int at;
    char getValue(); //of self
    void setValue(char v); //of self
    void _allocate(); //these should only be called by the outer container! being outside ensures the pointer is set to the start
    void _deallocate();
    public:
        Cell(Cell* p, bool palloc=false);
        ~Cell();
        void allocate(); //alloc/dealloc of pointed cell (not self), does nothing if no cell
        void deallocate();
        Cell *enter(); //you are now able to access the cells in mem, and are currently at the first element
        Cell *exit(); //exit to the previous level
        Cell &operator++(); //increment pointed cell (not self)
        Cell &operator--(); //decrement pointed cell (not self)
        //these are PREFIX operators!
        void operator++(int); //shift right
        void operator--(int); //shift left
        //do note that the postfix operators DO NOT have return types!
        char get();
        void set(char c);
        void reset();
        int getSize();
};

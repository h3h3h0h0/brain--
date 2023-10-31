#pragma once
#include <vector>

using namespace std;

class Cell {
    //value stored within cell itself
    char value;
    //cells considered to be "inside" current cell
    vector<Cell*> mem;
    //parent cell pointer for efficiency
    //nullptr if at top level
    Cell* parent;
    public:
        Cell(Cell* p, char v=0);
        ~Cell();
        char getValue();
        void setValue(char v);
        void allocate();
        void deallocate();
};

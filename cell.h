#include <vector>

using namespace std;

class Cell {
    static const int presize = 3000; //prealloc size
    //value stored within cell itself
    char value = 0;
    //cells considered to be "inside" current cell
    vector<Cell*> mem;
    //parent cell pointer for efficiency
    //nullptr if at top level
    Cell* parent;
    int at = -1;
    char getValue(); //of self
    void setValue(char v); //of self
    void _allocate(); //these should only be called by the outer container! being outside ensures the pointer is set to the start
    void _deallocate();
    public:
        Cell(Cell* p, bool palloc=false);
        Cell(const Cell &other) = delete; //disabled copy ctor, use clone() instead
        Cell(Cell &&other); //move ctor is still working tho
        ~Cell();
        Cell *clone(Cell *nparent=nullptr); //make an exact copy (other than the "root" parent), copy ctor isn't used here because copying the parent is rather tricky
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
        void set(char v);
        void reset();
        int getSize();
};

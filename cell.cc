#include "cell.h"

Cell::Cell(Cell* p, bool palloc): parent{p} { //at is initialized to -1 to signify that the internal register is empty
    if(palloc) { //the "outer dummy" which is initialized to 30k
        for(int i = 0; i < presize; i++) {
            _allocate();
        }
    }
} 

Cell::Cell(Cell &&other): value{other.value}, parent{other.parent}, at{other.at} {
    other.parent = nullptr;
    for(int i = 0; i < other.mem.size(); i++) {
        mem.push_back(other.mem[i]); //directly move the branch pointers to self, do not recursive copy
    }
    while(!other.mem.empty()) {
        other.mem.pop_back(); //we move all the pointers away from other, so it should be empty by the end
    }
}

Cell::~Cell() {
    while (!mem.empty()) {
        delete mem.back();
        mem.pop_back();
    }
}

Cell *Cell::clone(Cell *nparent) {
    Cell *temp = new Cell(nparent);
    temp->value = this->value;
    //reset all the pointers to the leftmost position
    if(this->at != -1) temp->at = 0; //if nonempty, the leftmost is at 0, if empty, it's at -1 anyway
    for(int i = 0; i < this->mem.size(); i++) {
        temp->mem.push_back(mem[i]->clone(temp)); //clone the memory as well, making sure the parents link to temp instead of this
    }
    return temp;
}

char Cell::getValue() {
    return value;
}

void Cell::setValue(char v) {
    value = v;
}

void Cell::_allocate() {
    mem.push_back(new Cell(this));
    if(at == -1) at = 0;
}

void Cell::_deallocate() {
    if(mem.empty()) return;
    delete mem.back();
    mem.pop_back();
    if(mem.empty()) at = -1;
}

void Cell::allocate() {
    if(at == -1) return;
    mem[at]->_allocate();
}

void Cell::deallocate() {
    if(at == -1) return;
    mem[at]->_deallocate();
}

Cell *Cell::enter() {
    if(at == -1) return nullptr;
    if(mem[at]->getSize() == 0) return nullptr; //there's nothing there!
    mem[at]->reset();
    return mem[at];
}

Cell *Cell::exit() {
    reset();
    return parent;
}

Cell &Cell::operator++() {
    if(at == -1) return *this; //do nothing if there is no cell to point to
    mem[at]->setValue(mem[at]->getValue()+1);
    return *this;
}

Cell &Cell::operator--() {
    if(at == -1) return *this; //do nothing if there is no cell to point to
    mem[at]->setValue(mem[at]->getValue()-1);
    return *this;
}

void Cell::operator++(int) {
    if(at == -1) return;
    at++;
    if(at == mem.size()) at = 0;
}

void Cell::operator--(int) {
    if(at == -1) return;
    at--;
    if(at == -1) at = mem.size()-1;
}

char Cell::get() {
    if(at == -1) return 0; //if there is nothing there, return 0 (should not happen in regular operation)
    return mem[at]->getValue();
}

void Cell::reset() {
    if(at == -1) return;
    at = 0;
}

void Cell::set(char v) {
    if(at == -1) return;
    mem[at]->setValue(v);
}

int Cell::getSize() {
    return mem.size();
}
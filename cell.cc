#include "cell.h"

Cell::Cell(Cell* p, char v=0): parent{p}, value{v} {}

Cell::~Cell() {
    while (!mem.empty()) {
        delete mem.back();
        mem.pop_back();
    }
}

char Cell::getValue() {
    return value;
}

void Cell::setValue(char v) {
    value = v;
}

void Cell::allocate() {
    mem.push_back(new Cell(this));
}

void Cell::deallocate() {
    delete mem.back();
    mem.pop_back();
}

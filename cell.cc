#pragma once
#include "cell.h"

Cell::Cell(Cell* p, char v=0): parent{p}, value{v}, at{-1} {} //at is initialized to -1 to signify that the internal register is empty

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

void Cell::_allocate() {
    mem.push_back(new Cell(this));
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

int Cell::getSize() {
    return mem.size();
}
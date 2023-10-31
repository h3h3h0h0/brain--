#pragma once
#include "interpreter.h"
#include <iostream>

using namespace std;

void _run(istream &in, ostream &out, string prog, bool debug) {
    Cell *root = new Cell(nullptr); //the root is a "dummy", not accessible to the user but ensures the while thing works consistently
    root->allocate(); //prepare the starting cell
    Cell *cur = root; //this is the actual memory pointer, root will be kept to ensure all memory is freed no matter where the pointer ends up
    //main loop
    for(int i = 0; i < prog.size(); i++) {
        switch(prog[i]) {
            case '.':
                char c = cur->get();
                out<<c;
            break;
            case ',':
                char c;
                in>>c;
                cur->set(c);
            break;
            case '<':
                *cur--;
            break;
            case '>':
                *cur++;
            break;
            case '+':
                ++(*cur);
            break;
            case '-':
                --(*cur);
            break;
            case '@':
                cur->allocate();
            break;
            case '#':
                cur->deallocate();
            break;
            case '?':
                Cell *temp = cur->enter();
                if(temp) cur = temp;
            break;
            case '!':
                Cell *temp = cur->exit();
                if(temp) cur = temp;
            break;
            default: //print to STDERR
                if(debug) cerr<<"INVALID OPERATOR: "<<prog[i]<<endl;
        }
    }
}

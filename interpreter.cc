#pragma once
#include "interpreter.h"

using namespace std;

void BFMInterpreter::_run(istream &in, ostream &out, string prog, bool debug) {
    out<<"RUNNING...\n\n\n";
    //start prep
    Cell *root = new Cell(nullptr, true); //the root is a "dummy", not accessible to the user but ensures the while thing works consistently
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
    running = false;
    out<<"\n\n\nFINISHED\n";
}

BFMInterpreter::BFMInterpreter() {
    running = false;
}

BFMInterpreter::~BFMInterpreter() {
    if(running) pthread_cancel(thr);
}
void BFMInterpreter::load(string prog) {
    program = prog;
}
void BFMInterpreter::loadFile(string fn) {
    ifstream f(fn);
    stringstream buffer;
    buffer<<f.rdbuf();
    program = buffer.str();
}
void BFMInterpreter::run(istream &in, ostream &out, bool debug=false) {
    running = true;
    thread t = thread(_run, in, out, program, debug);
    thr = t.native_handle();
    t.detach();
}
void BFMInterpreter::stop() {
    if(running) {
        pthread_cancel(thr);
        running = false;
    }
}

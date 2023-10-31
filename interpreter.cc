#include "interpreter.h"

using namespace std;

void BFMInterpreter::load(string prog) {
    program = prog;
}
void BFMInterpreter::loadFile(string fn) {
    ifstream f(fn);
    stringstream buffer;
    buffer<<f.rdbuf();
    program = buffer.str();
}

void BFMInterpreter::run(istream &in, ostream &out, bool debug) {
    out<<"RUNNING...\n----------\n";
    //start prep
    Cell *root = new Cell(nullptr, true); //the root is a "dummy", not accessible to the user but ensures the while thing works consistently
    Cell *cur = root; //this is the actual memory pointer, root will be kept to ensure all memory is freed no matter where the pointer ends up
    stack<int> loops;
    //main loop
    for(int i = 0; i < program.size(); i++) {
        switch(program[i]) {
            case '.': {
                out<<cur->get();
            } break;
            case ',': {
                char c;
                in>>c;
                cur->set(c);
            } break;
            case '<': {
                (*(cur))--;
            } break;
            case '>': {
                (*(cur))++;
            } break;
            case '+': {
                ++(*(cur));
            } break;
            case '-': {
                --(*(cur));
            } break;
            case '[': {
                loops.push(i);
            } break;
            case ']': {
                int temp = loops.top();
                loops.pop();
                if(cur->get() != 0) i = temp-1;
            } break;
            case '@': {
                cur->allocate();
            } break;
            case '#': {
                cur->deallocate();
            } break;
            case '?': {
                Cell *temp = cur->enter();
                if(temp) cur = temp;
            } break;
            case '!': {
                Cell *temp = cur->exit();
                if(temp) cur = temp;
            } break;
            default: //print to STDERR
                if(debug) cerr<<"INVALID OPERATOR: "<<program[i]<<endl;
        }
    }
    delete root;
    out<<"\n--------\nFINISHED\n";
}

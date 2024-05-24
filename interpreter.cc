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

Cell *BFMInterpreter::run(istream &in, ostream &out, bool debug, bool memdump, Cell *loadfrom) {
    out<<"RUNNING...\n----------\n";
    //start prep
    Cell *root = nullptr;
    stack<int> pstack;
    int lpstack = 0;
    if(!loadfrom) {
        root = new Cell(nullptr, true); //the root is a "dummy", not accessible to the user but ensures the while thing works consistently
    } else {
        root = loadfrom->clone(); //if a pointer is given to load something, it is cloned and loaded in (very useful for debugging, you can load an exact memory configuration)
    }
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
                // logic for if loop does not execute at all
                if(cur->get() == 0) {
                    int ocount = 1;
                    while(program[i] != ']' || ocount != 0) {
                        i++;
                        if(program[i] == '[') ocount++;
                        else if(program[i] == ']') ocount--;
                    }
                    break;
                }
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
            case ';': {
                if(pstack.empty() || pstack.top() != cur->get()) { //unequal or DNE means push
                    lpstack++;
                    pstack.push(cur->get());
                } else {
                    lpstack--;
                    pstack.pop();
                }
            } break;
            case ':': {
                if(pstack.empty()) { //empty means zero out the contents of the current cell
                    cur->set(0);
                } else {
                    int temp = pstack.top();
                    pstack.pop();
                    pstack.push(cur->get());
                    cur->set(temp);
                }
            } break;
            case '|': {
                cur->set(lpstack);
            } break;
            default: //print to STDERR
                if(debug) cerr<<"INVALID OPERATOR: "<<program[i]<<endl;
        }
    }
    Cell *dump = root->clone();
    delete root;
    out<<"\n----------\nFINISHED\n";
    if(memdump) {
        out<<"MEMORY DUMP RETURNED!"<<endl;
        return dump;
    } else {
        out<<"MEMORY CLEARED!"<<endl;
        delete dump;
        return nullptr;
    }
}

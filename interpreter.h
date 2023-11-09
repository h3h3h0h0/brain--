#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "cell.h"

using namespace std;

class BFMInterpreter {
    string program = "";
    public:
        BFMInterpreter() = default;
        ~BFMInterpreter() = default; 
        void load(string prog); //load from string
        void loadFile(string fn);
        Cell *run(istream &inp, ostream &outp, bool debug=false, bool memdump=false, Cell *loadfrom=nullptr); //debug: print debug messages into STDERR
                                                                                                              //memdump: return a copy of internal memory at program end (nullptr otherwise)
                                                                                                              //loadfrom: if nonempty, loads memory to starting state
};
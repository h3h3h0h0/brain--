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
        void run(istream &inp, ostream &outp, bool debug=false);
};
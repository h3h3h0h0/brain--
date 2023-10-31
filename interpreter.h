#pragma once
#include <istream>
#include <ostream>
#include <thread>
#include <queue>
#include "cell.h"

using namespace std;

class BFMInterpreter {
    string program;
    void _run(istream in, ostream out, string prog); //the public run method calls this, which will be threaded
    public:
        BFMInterpreter();
        ~BFMInterpreter();
        void load(string prog);
        void loadFile(string fn);
        void run(istream in, ostream out);
        void stop();
};
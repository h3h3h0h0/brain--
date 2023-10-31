#pragma once
#include <istream>
#include <ostream>
#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include "cell.h"

using namespace std;

class BFMInterpreter {
    string program = "";
    pthread_t thr;
    atomic<bool> running = false;
    void _run(istream &in, ostream &out, string prog, bool debug); //the public run method calls this, which will be threaded
    public:
        BFMInterpreter() = default;
        ~BFMInterpreter(); //terminates all the threads
        void load(string prog);
        void loadFile(string fn);
        void run(istream &in, ostream &out, bool debug=false);
        void stop(); //stops currently running thread
};
#pragma once
#include <istream>
#include <ostream>
#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include <atomic>
#include "cell.h"

using namespace std;

class BFMInterpreter {
    string program = "";
    pthread_t thr;
    std::atomic<std::bool> running(0);
    void _run(istream &in, ostream &out, string prog, bool debug); //the public run method calls this, which will be threaded
    public:
        BFMInterpreter();
        ~BFMInterpreter(); //calls stop before the program ends
        void load(string prog); //load from string
        void loadFile(string fn);
        void run(istream &in, ostream &out, bool debug=false);
        void stop(); //stops currently running thread
};
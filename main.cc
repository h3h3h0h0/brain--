#include <iostream>
#include "interpreter.h"

using namespace std;

//example
int main() {
    BFMInterpreter b{};
    //regular hello world program
    b.load(">++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<++.------------.>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-]<+.");
    b.run(cin, cout);
    //testing code for alloc/dealloc (prints "BAA")
    b.load("@@?>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++@??!.<?+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!?.!##?+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.@?++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    Cell *mdump = b.run(cin, cout, false, true, nullptr);
    //testing code for memdump and memload (prints "BAA")
    b.loadFile("test.bfm");
    b.run(cin, cout, false, false, mdump);
    delete mdump;
    return 0;
}

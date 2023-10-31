#include <iostream>
#include "interpreter.h"

using namespace std;

//example
int main() {
    BFMInterpreter b;
    b.load(">++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<++.------------.>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-]<+.");
    b.run(cin, cout);
    return 0;
}

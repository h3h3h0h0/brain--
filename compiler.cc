#include <compiler.h>

void BFMCompiler::prologue(int sz, ostream &os) {
    //transfer passed memory location to $11, zero out $1 as there are no freed cells yet
    os<<"add $11, $1, $0"<<endl;
    os<<"add $1, $0, $0"<<endl;
    //constants and initializations for temporary variables
    os<<"lis $4"<<endl;
    os<<".word 20"<<endl;
    os<<"lis $5"<<endl;
    os<<".word 1"<<endl;
    os<<"lis $6"<<endl;
    os<<".word 0x100"<<endl;
    os<<"lis $21"<<endl;
    os<<".word 0xffff0004"<<endl;
    os<<"lis $22"<<endl;
    os<<".word 0xffff000c"<<endl;
    os<<"add $12, $0, $0"<<endl; //zero out the "previous" scratch value for now (will link in a loop later)
    //allocate sz amount of cells, set the pointer to beginning
    os<<"add $2, $11, $0"<<endl;
    os<<"lis $3"<<endl;
    os<<".word "<<sz<<endl;
    os<<"alsz:"<<endl;
    os<<"sw $0, 0($11)"<<endl; //zero out contents
    os<<"sw $11, 4($11)"<<endl; //set above and below to self
    os<<"sw $11, 8($11)"<<endl;
    os<<"add $13, $11, $4"<<endl; //this is the next address we will allocate
    os<<"sw $12, 12($11)"<<endl; //set left and right
    os<<"sw $13, 16($11)"<<endl;
    os<<"add $12, $11, $0"<<endl; //update "previous" address
    os<<"add $11, $11, $4"<<endl; //update unused address pointer
    os<<"sub $3, $3, $5"<<endl; //decrement counter
    os<<"bne $3, $0, alsz"<<endl;
    //link start and end cells of starting memory (for the loop)
    os<<"sw $12, 12($1)"<<endl; //set rightmost cell to be left of leftmost cell
    os<<"sw $1, 16($12)"<<endl; //set leftmost cell to be right of rightmost cell
}
void alloc_cell(ostream &os) {
    //allocate the new cell (address in $13)
    os<<"beq $1, $0, 3"<<endl;
    os<<"add $13, $1, $0"<<endl;
    os<<"lw $1, 16($1)"<<endl; //new head of freed list
    os<<"beq $0, $0, 2"<<endl; //skip re-setting $13 and $11 in the case of freed memory being available
    os<<"add $13, $11, $0"<<endl;
    os<<"add $11, $11, $4"<<endl;
    //link the new cell
    os<<"lw $3, 8($2)"<<endl; //load the down pointer of the current cell
    os<<"bne $3, $2, 4"<<endl; //the next few lines deal with completely empty cells (no subcells)
    os<<"sw $13, 8($2)"<<endl; //link to bottom
    os<<"sw $13, 12($13)"<<endl; //link new cell left to itself
    os<<"sw $13, 16($13)"<<endl; //link new cell right to itself
    os<<"beq $0, $0, 5"<<endl; //next few lines deal with adding to already populated cells
    os<<"lw $12, 12($3)"<<endl; //load the rightmost current element (inside the pointed cell) to link
    os<<"sw $13, 16($12)"<<endl; //link right from rightmost element
    os<<"sw $12, 12($13)"<<endl; //link left from new element
    os<<"sw $13, 12($3)"<<endl; //link left from leftmost element
    os<<"sw $3, 16($13)"<<endl; //link right from new element
    //things done by both branches   
    os<<"sw $0, 0($13)"<<endl; //zero out data of new cell
    os<<"sw $2, 4($13)"<<endl; //link top of added cell to current cell
    os<<"sw $13, 8($13)"<<endl; //set bottom of added cell to self
}
void dealloc_cell(ostream &os) {
    os<<"lw $3, 8($2)"<<endl; //load the down pointer of the current cell
    os<<"beq $3, $2, 14"<<endl; //if there is nothing to deallocate, skip everything
    os<<"lw $12, 16($3)"<<endl; //load right pointer of below cell
    os<<"bne $3, $12, 2"<<endl; //next few lines deal with when there is only one cell
    os<<"sw $2, 8($2)"<<endl; //sever our our bottom connection (set to self)
    os<<"beq $0, $0, 4"<<endl; //next few lines deal with when there is more than one
    os<<"lw $12, 12($3)"<<endl; //$12 to last (to be deleted) element
    os<<"lw $13, 12($12)"<<endl; //$13 to second last element
    os<<"sw $3, 16($13)"<<endl; //link right from SL element to first element
    os<<"sw $13, 12($3)"<<endl; //link left from first element to SL element
    //things done by both
    os<<"sw $0, 0($12)"<<endl; //zero out data and up/down from deleted cell
    os<<"sw $0, 4($12)"<<endl;
    os<<"sw $0, 8($12)"<<endl;
    os<<"sw $0, 12($12)"<<endl; //zero out left pointer
    os<<"sw $1, 16($12)"<<endl; //link to freed list 
    os<<"add $1, $12, $0"<<endl; //make head of freed list
}
void increment(ostream &os) {
    os<<"lw $3, 0($2)"<<endl; //get value
    os<<"add $3, $3, $5"<<endl; //add
    os<<"divu $3, $6"<<endl; //byte values, so mod 256
    os<<"mfhi $3"<<endl;
    os<<"sw $3, 0($2)"<<endl; //set value
}
void decrement(ostream &os) {
    os<<"lw $3, 0($2)"<<endl; //get value
    os<<"sub $3, $3, $5"<<endl; //sub
    os<<"divu $3, $6"<<endl; //byte values, so mod 256
    os<<"mfhi $3"<<endl;
    os<<"sw $3, 0($2)"<<endl; //set value
}
void loop_begin(int cn, ostream &os) {
    string lbn = "lb"+cn;
    string len = "le"+cn;
    os<<lbn<<":"<<endl;
    os<<"lw $3, 0($2)"<<endl;
    os<<"beq $3, $0, "<<len<<endl;
}
void loop_end(int cn, ostream &os) {
    string lbn = "lb"+cn;
    string len = "le"+cn;
    os<<"bne $3, $0, "<<lbn<<endl;
    os<<len<<":"<<endl;
}

void BFMCompiler::translate(istream &is, ostream &os) {
    char c = '.';
    int cnt = 0;
    stack<int> lstack;
    prologue(ssz, os);
    while(is>>c) {
        switch(c) {
            case '[':
                loop_begin(cnt, os);
                lstack.push(cnt); //push where our loop started so we may create the proper label
            break;
            case ']':
                assert(!lstack.empty());
                int pcnt = lstack.top(); //get the line where the corresponding LBRACK is
                lstack.pop();
                loop_end(pcnt, os);
            break;
            case '.':
                os<<"lw $3, 0($2)"<<endl;
                os<<"sw $3, 0($22)"<<endl;
            break;
            case ',':
                os<<"lw $3, 0($21)"<<endl;
                os<<"sw $3, 0($2)"<<endl;
            break;
            case '+':
                increment(os);
            break;
            case '-':
                decrement(os);
            break;
            case '@':
                alloc_cell(os);
            break;
            case '#':
                dealloc_cell(os);
            break;
            case '>':
                os<<"lw $2, 16($2)"<<endl;
            break;
            case '<':
                os<<"lw $2, 12($2)"<<endl;
            break;
            case '?':
                os<<"lw $2, 8($2)"<<endl;
            break;
            case '!':
                os<<"lw $2, 4($2)"<<endl;
            break;
            default:
        }
        cnt++;
    }
}
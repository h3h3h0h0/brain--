# brain--
Brainfuck with a recursive tree data structure.
# About
One of the most frustrating things I encountered during my CS courses was recursive structures. While they can be very useful, they're also a pain to debug. With that in mind, I set out to create a superset of an already frustrating-by-design language that incorporates this concept. Just like in programming in other languages, you don't HAVE to use the recursive data structure, but you are strongly encouraged to in some situations.

# Features
- Any program which is coded in the normal language will run correctly, barring any memory overflow issues (that is, any programs with only the operators <>+-[].,)
- The main memory starts out with 3000 cells (made using a "dummy" wrapper cell)
- Each cell now has the ability to allocate additional cells inside it, with the samy byte of memory
- This is recursive: cells allocated within other cells will have the same ability to allocate cells inside them

# MIPS Compilation
Memory:
- Memory cells are 5 words long: Data, Above, Below, Left, Right in one word each
- A bit inefficient with space, but we still theoretically can support several million cells.
- The memory is managed by a modified Freelist.
  - Since it is allocated always by cell, there is no need for fitting.
  - Memory will be split into 3 categories: "in use", "freed", and "unused", with allocation being preferentially from the freed category
    - This ensures that the memory footprint is as small as possible for every program
    - Separate pointers will be maintained for each category ($1, $2, $11)
    - A pointer of 0 signifies that there is no available memory there in $1
- List of relevant registers (modified from WLP4 compiler as featured in CS241):
  - $0: always 0 (mips enforced)
  - $1, $2: pointer to first free and current cell: program assumes $1 is passed for startup to begin allocation, and assumes that at the start this is a continuous section of free memory
  - $3: result/scratch register
  - $4: stores the value 20 (for memory allocation, 5 4-byte words)
  - $5: stores the value 1 (for increment and decrement)
  - $6: stores the value 256 (0x100) for enforcing the byte-sized cells rule
  - $11: pointer to the leftmost point in "unused" heap memory, used only if all previous freed memory is gone
  - $12, $13: scratch registers used for memory operations
  - $21, $22: input, output addresses

Update 1.1:
- The interpreter can now dump and load its internal memory. This is useful for debugging programs (though your access would start at the top level in the leftmost position, instead of where you left off).

Update 1.2:
- Added compiler class
  
Todo:
- Add stack operations
- Add unconditional jumps
  
# Syntax
@: allocate an additional byte to the end of the current cell

#: deallocate the last byte from the current cell (if available)

?: "inwards" operator, placing the pointer on the first element inside the current cell (if available)

!: "outwards" operator, placing the pointer on the encapsulating cell (if available)

+-: increment and decrement, behaves as normal

<>: shift cells, this will "loop around", that is using < on the first element or > on the last element will put you at the other end of the list

,.: I/O operators, behaves normally

# What's in this repo?
An interpreter for brain-- written in C++ (due to Stockholm Syndrome from CS246).
(in development) A compiler into MIPS.

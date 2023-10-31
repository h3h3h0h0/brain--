# brain--
Brainfuck with a recursive tree data structure.
# About
One of the most frustrating things I encountered during my CS courses was recursive structures. While they can be very useful, they're also a pain to debug. With that in mind, I set out to create a superset of an already frustrating-by-design language that incorporates this concept. Just like in programming in other languages, you don't HAVE to use the recursive data structure, but you are strongly encouraged to in some situations.
# Features
- Any program which is coded in the normal language will run correctly (that is, any programs with only the operators <>+-[].,)
- The main memory starts out with 30000 bytes as usual
- Each cell now has the ability to allocate additional cells inside it, with the samy byte of memory
- This is recursive: cells allocated within other cells will have the same ability to allocate cells inside them
# Syntax
@: allocate an additional byte to the end of the current cell

#: deallocate the last byte from the current cell (if available)

?: "inwards" operator, placing the pointer on the first element inside the current cell (if available)

!: "outwards" operator, placing the pointer on the encapsulating cell (if available)

+-: increment and decrement, behaves as normal

<>: shift cells, this will "loop around", that is using < on the first element or > on the last element will put you at the other end of the list

,.: I/O operators, behaves normally

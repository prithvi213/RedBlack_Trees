## Programming Assignment 8
In this programming assignment, I used the Dictionary ADT to implement Red-Black Trees. It has 
the same operations as a Dictionary, except that the tree is always near balanced after every
insertion and deletion operation. It is also able to ensure that the red and black node
properties are maintained after every insertion and deletion. This makes insertions and 
deletions much more efficient, as well as accessing particular nodes in the tree.

## Files
Dictionary.h <br />
Dictionary.cpp <br />
DictionaryTest.cpp <br />
Order.cpp <br />
Makefile <br />
README.md

## Building
To build 'Order' program: make/make Order <br />
To build 'DictionaryTest' program: make/make DictionaryTest <br />

## Runnning
To run 'Order' program: Order <infile> <outfile> <br />
To run 'DictionaryTest' program: DictionaryTest <br />

## Cleaning
To clean: make clean

## Memory Checking
To check memory for 'Order' program: make OrderCheck <br />
To check memory for 'DictionaryTest' program: make DictionaryCheck

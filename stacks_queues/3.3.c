/*
Imagine a (literal) stack of plates. If the stack gets too high, it might topple. There- fore, in real life, we would likely start a new stack when the previous stack exceeds some threshold. Implement a data structure SetOfStacks that mimics this. SetOf- Stacks should be composed of several stacks, and should create a new stack once the previous one exceeds capacity. SetOfStacks.push() and SetOfStacks.pop() should behave identically to a single stack (that is, pop() should return the same values as it would if there were just a single stack).
FOLLOW UP
Implement a function popAt(int index) which performs a pop operation on a specific sub-stack.
*/

/*
  need a way to keep track of which stack is current
  need functions to malloc and realloc new stacks
  need a dynamic array of sizes
*/

#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

typedef struct Node node;

struct SetOfStacks {
  node **stacks;
  int numStacks;
  int maxSize;   // max size of a stack
  int *currTop; // current top for each stack (needed if a popAt function is to be implemented)
};

typedef struct SetOfStacks sos;

sos *initSOS(int size) {
  sos *Sos;
  Sos = malloc(sizeof(Sos));
  Sos -> numStacks = 1;
  Sos -> maxSize = size;
  Sos -> currTop = malloc(sizeof(int)); // allocate space for Sos -> numStacks == 1 int
  Sos -> currTop[0] = 0;
  Sos -> stacks = malloc(sizeof(node *)); // allocate space for Sos -> numStacks == 1 int
  Sos -> stacks[0] = malloc(sizeof(node));  // allocate space for first top of stack (there should only be one)
  return Sos;
}

void increaseStacks(sos *Sos) {
}

void freeStack(node *head) {
  node *tmp;
  while(head != NULL) {
    tmp = head;
    head = head -> next;
    free(tmp);
  }
}

void freeSos(sos *Sos) {
  int i;
  // free each stack
  for(i = 0; i < Sos -> numStacks; i++) {
    freeStack(Sos -> stacks[i]);
  }
  free(Sos -> currTop);
  free(Sos);
}

void push(sos *Sos, int value) {

}

int pop(sos *Sos) {

}

int peek(sos *Sos) {

}

int popAt(sos *Sos) {

}

int main() {

}

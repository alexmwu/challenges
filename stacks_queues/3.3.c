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
#include <stdio.h>

struct Node {
  int data;
  struct Node *next;
};

typedef struct Node node;

struct SetOfStacks {
  node **stacks;
  int numStacks;
  int maxSize;   // max size of a stack
  int currStack;
  int *currSizes; // current top for each stack (needed if a popAt function is to be implemented)
};

typedef struct SetOfStacks sos;

sos *initSOS(int size) {
  sos *Sos;
  Sos = malloc(sizeof(Sos));
  Sos -> numStacks = 1;
  Sos -> maxSize = size;
  Sos -> currSizes = malloc(sizeof(int)); // allocate space for 1 (Sos -> numStacks) int
  Sos -> currSizes[0] = 0;
  Sos -> stacks = malloc(sizeof(node *)); // allocate space for 1 (Sos -> numStacks) node pointer
  Sos -> stacks[0] = NULL;  // don't allocate space for first top of stack; this should be handled by push
  Sos -> currStack = 0;
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
  free(Sos -> currSizes);
  free(Sos);
}

void printSos(sos *Sos) {
  int i;
  for(i = Sos -> numStacks - 1; i <= 0; i--) {
    printf("~~~~~\n");
    node *tmp = Sos -> stacks[i];
    while(tmp != NULL) {
      printf("%d\n", tmp -> data);
      tmp = tmp -> next;
    }
    printf("~~~~~\n\n");
  }
}

void push(sos *Sos, int value) {
  if(Sos -> currSizes[Sos -> currStack] >= Sos -> maxSize) {
    node **moreStacks = Sos -> stacks;
    Sos -> stacks =
  }
  else {
    node *tmp = malloc(sizeof(node));   // allocate space for new stack item
    tmp -> data = value;
    tmp -> next = Sos -> stacks[Sos -> currStack];
    Sos -> stacks[Sos -> currStack] = tmp;
    Sos -> currSizes[Sos -> currStack]++;
  }
}

int pop(sos *Sos) {
  int popped = Sos -> stacks[Sos -> currStack] -> data;
  node *tmp = Sos -> stacks[Sos -> currStack] -> next;
  Sos -> stacks
  Sos -> 
  return;
}

int peek(sos *Sos) {

}

int popAt(sos *Sos) {

}


int main() {
  sos *Sos = initSos(3);  // initialize SetOfStacks with size of 3
  int i;

  // test regular SetOfStacks
  for(i = 0; i < 20; i++) {
    push(Sos, i);
  }
  printf("Max size: %d", Sos -> maxSize);
  printSos(Sos);
  while(Sos -> stacks[0] != NULL) {
    pop(Sos);
  }
  printSos(Sos);


  // test sos with popAt


  freeSos(Sos);
}

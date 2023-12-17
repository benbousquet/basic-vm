#include <stdio.h>
#include <stdlib.h>

typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  HLT
} InstructionSet;

const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
  HLT
};

int* pstack;
int pstack_size = 0;

int ip = 0;

int fetch() {
  return program[ip];
}

void eval(int instruction) {
  int res;
  switch(instruction){
    case PSH:
      pstack_size++;
      pstack = (int*)realloc(pstack, (pstack_size) * sizeof(int));
      pstack[pstack_size - 1] = program[ip];
      ip++;
      break;
    case ADD:
      res = pstack[pstack_size - 1] + pstack[pstack_size - 2];
      pstack_size--;
      pstack = (int*)realloc(pstack, (pstack_size) * sizeof(int));
      pstack[pstack_size - 1] = res;
      break;
    case POP:
      printf("DEBUG: %d", pstack[pstack_size - 1]);
      pstack_size--;
      pstack = (int*)realloc(pstack, (pstack_size) * sizeof(int));
      break;
    case HLT:
      break;
    default:
      break;
  }

}

int main() {
  pstack = (int*)calloc(pstack_size, sizeof(int));
  int curr = fetch();
  ip++;
  while(curr != HLT) {
    eval(curr);
    curr = fetch();
    ip++;
  }
  return 0;
}
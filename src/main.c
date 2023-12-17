#include <stdio.h>
#include <stdlib.h>

typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  GET,
  MOV,
  PRN,
  GOT,
  HLT
} InstructionSet;

typedef enum {
  A, B, C, REG_COUNT
} Registers;

int registers[REG_COUNT];

const int program[] = {
  PSH, 5,
  PSH, 6,
  SET, B, 8,
  GET, B,
  POP,
  // GOT, 8,
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

void addStack(int val) {
  pstack_size++;
  pstack = (int*)realloc(pstack, (pstack_size) * sizeof(int));
  pstack[pstack_size - 1] = val;
}

int popStack() {
  int top = pstack[pstack_size - 1];
  pstack_size--;
  pstack = (int*)realloc(pstack, (pstack_size) * sizeof(int));
  return top;
}

void eval(int instruction) {
  int res;
  switch(instruction){
    case PSH:
      addStack(program[ip]);
      ip++;
      break;
    case ADD:
      res = popStack() + popStack();
      addStack(res);
      break;
    case POP:
      printf("DEBUG: %d\n", popStack());
      break;
    case SET:
      registers[program[ip]] = program[ip + 1];
      ip += 2;
      break;
    case GET:
      addStack(registers[program[ip]]);
      ip++;
      break;
    // case GOT: broken rn ;(
    //   ip = program[ip + 1] - 1;
    //   break;
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
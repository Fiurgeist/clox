#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

// TODO: remove global var and explicitly take a VM pointer and pass it around
VM vm;

static void resetStack() {
  vm.stackTop = vm.stack;
}

void initVM() {
  resetStack();
}

void freeVM() {
}

static void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

static Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(operator) \
    do { \
      double b = pop(); \
      double a = pop(); \
      push(a operator b); \
    } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value* slot = vm.stack; slot < vm.stackTop; ++slot) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
    switch (instruction = READ_BYTE())
    {
    case OP_CONSTANT:
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    case OP_ADD:      BINARY_OP(+); break;
    case OP_SUBTRACT: BINARY_OP(-); break;
    case OP_MULTIPLY: BINARY_OP(*); break;
    case OP_DIVIDE:   BINARY_OP(/); break;
    case OP_NEGATE:   push(-pop()); break;
    case OP_RETURN:
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    default:
      return INTERPRET_COMPILE_ERROR;
    }
  }
#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}
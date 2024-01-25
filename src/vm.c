#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

// TODO: remove global var and explicitly take a VM pointer and pass it around
VM vm;

void initVM() {
}

void freeVM() {
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
    switch (instruction = READ_BYTE())
    {
    case OP_CONSTANT:
      Value constant = READ_CONSTANT();
      printValue(constant);
      printf("\n");
      break;
    case OP_RETURN:
      return INTERPRET_OK;
    default:
      return INTERPRET_COMPILE_ERROR;
    }
  }
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}
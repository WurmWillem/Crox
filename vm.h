#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#define STACK_MAX 256

typedef struct {
    Chunk *chunk;
    uint8_t *ip;
    Value stack[STACK_MAX];
    Value *stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM();
void freeVM();

void stackPush(Value value);
Value stackPop();

InterpretResult interpret(const char *source);

#endif

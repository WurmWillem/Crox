#include "vm.h"
#include "chunk.h"
#include "debug.h"
#include "value.h"
#include <stdio.h>

VM vm;

static void resetStack() { vm.stackTop = vm.stack; }

void initVM() { resetStack(); }
void freeVM() {}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

#define BINARY_OP(op)                                                          \
    do {                                                                       \
        double b = stackPop();                                                 \
        double a = stackPop();                                                 \
        stackPush(a op b);                                                     \
    } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
        case OP_RETURN: {
            printValue(stackPop());
            printf("\n");
            return INTERPRET_OK;
        }

        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            stackPush(constant);
            break;
        }

        case OP_NEGATE: {
            stackPush(-stackPop());
            break;
        }

        case OP_ADD:
            BINARY_OP(+);
            break;
        case OP_SUB:
            BINARY_OP(-);
            break;
        case OP_MULT:
            BINARY_OP(*);
            break;
        case OP_DIV:
            BINARY_OP(/);
            break;
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(const char *source) {
    compile(source);
    return INTERPRET_OK;
}

void stackPush(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}
Value stackPop() {
    vm.stackTop--;
    return *vm.stackTop;
}

#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_RETURN,
  OP_NEGATE,
  OP_ADD,
  OP_SUB,
  OP_MULT,
  OP_DIV
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t *code;
  ValueArray constants;
  int *lines;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int lines);
int addConstant(Chunk *chunk, Value value);
void freeChunk(Chunk *chunk);

#endif

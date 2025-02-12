#ifndef clox_scanner_h
#define clox_scanner_h

void initScanner(const char* source);

typedef struct {
  const char* start;
  const char* current;
  int line;
} Scanner;

#endif

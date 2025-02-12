a.out: main.c *.h *.c
	gcc -g -O2 -std=c99 -pedantic -Wall -Wno-unused-result *.c -lm

run: a.out
	./a.out

clean:
	rm a.out
	rm *.o

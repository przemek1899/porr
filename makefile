prog: main.o matGen.o
	gcc main.o matGen.o -lgsl -lgslcblas -lm -o prog

main.o: main.c
	gcc -c main.c -o main.o

matGen.o: matrixGenerator.c
	gcc -c -O3 -msse3 -ffast-math -ftree-vectorizer-verbose=10 matrixGenerator.c -o matGen.o
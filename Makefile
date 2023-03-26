main: main.c sumplete.o
	gcc main.c -o sumplete sumplete.o -lm -O3 -g3
sumplete.o: sumplete.c
	gcc -c sumplete.c -O3 -g3

main: main.cpp sumplete.o
	g++ main.cpp -o sumplete sumplete.o -g3 -O3 -march=native
sumplete.o: sumplete.cpp
	g++ -c sumplete.cpp -g3 -O3 -march=native
clean:
	rm sumplete sumplete.o

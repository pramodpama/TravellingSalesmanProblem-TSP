all: main.o genetic.o
	g++ -g -o TSP main.o genetic.o

main.o: main.cpp
	g++ -g -c main.cpp

genetic.o: genetic.cpp genetic.h
	g++ -g -c genetic.cpp

clean:
	rm *.o TSP 
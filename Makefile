all: main.cpp genetic.cpp bst.cpp
	g++ -g -o TSP main.cpp genetic.cpp bst.cpp

clean:
	rm TSP 
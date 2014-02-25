graph: graph.o
	gcc -Wall -o graph graph.o 

graph.o: graph.c 
	gcc -Wall -c graph.c

test: graph
	./graph read.dat

clean:
	rm -f graph.o 

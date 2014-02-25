graph: graph.o
	gcc -Wall -o graph graph.o -lm 

graph.o: graph.c 
	gcc -Wall -c graph.c -lm

test: graph
	./graph read.dat

clean:
	rm -f core* graph.o 
